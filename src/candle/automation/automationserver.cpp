// This file is a part of "Candle" application.

#include "automationserver.h"
#include "automationtools.h"

#include "../frmmain.h"

#include "versionconfig.h"

#include <QHostAddress>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QUuid>
#include <QPointer>
#include <QDebug>

static const char *const kProtocolVersions[] = { "2025-06-18", "2025-03-26", "2024-11-05" };
static const char *const kCurrentProtocolVersion = "2025-06-18";

AutomationServer::AutomationServer(frmMain *mainWindow, quint16 port, bool allowMotion,
    QObject *parent) :
    QObject(parent),
    m_main(mainWindow),
    m_server(this),
    m_callInFlight(false)
{
    m_tools = new AutomationTools(mainWindow, allowMotion, this);
    m_server.setMaxPendingConnections(16);
    m_port = port;
}

bool AutomationServer::start()
{
    if (!m_server.listen(QHostAddress::LocalHost, m_port)) {
        qWarning() << "Candle MCP: cannot listen on 127.0.0.1:" << m_port
            << m_server.errorString();
        return false;
    }

    qInfo() << "Candle MCP server listening on http://127.0.0.1:" << m_port << "/mcp";
    connect(&m_server, &QTcpServer::newConnection, this, &AutomationServer::onNewConnection);
    return true;
}

quint16 AutomationServer::port() const
{
    return m_server.serverPort();
}

QByteArray AutomationServer::reason(int code)
{
    switch (code) {
    case 200: return "OK";
    case 202: return "Accepted";
    case 204: return "No Content";
    case 400: return "Bad Request";
    case 404: return "Not Found";
    case 405: return "Method Not Allowed";
    default: return "Internal Server Error";
    }
}

QHash<QByteArray, QByteArray> AutomationServer::parseHeaders(const QByteArray &head)
{
    QHash<QByteArray, QByteArray> headers;
    foreach (const QByteArray &line, head.split('\n').mid(1)) {
        int colon = line.indexOf(':');
        if (colon > 0)
            headers.insert(line.left(colon).trimmed().toLower(), line.mid(colon + 1).trimmed());
    }
    return headers;
}

void AutomationServer::onNewConnection()
{
    while (QTcpSocket *socket = m_server.nextPendingConnection()) {
        m_buffers.insert(socket, QByteArray());

        connect(socket, &QTcpSocket::readyRead, this, [this, socket]() {
            onReadyRead(socket);
        });
        connect(socket, &QTcpSocket::disconnected, this, [this, socket]() {
            m_buffers.remove(socket);
            socket->deleteLater();
        });
    }
}

void AutomationServer::onReadyRead(QTcpSocket *socket)
{
    QByteArray &buffer = m_buffers[socket];
    buffer.append(socket->readAll());

    if (buffer.size() > 2 * 1024 * 1024) { // runaway client
        m_buffers.remove(socket);
        socket->abort();
        socket->deleteLater();
        return;
    }

    int headerEnd = buffer.indexOf("\r\n\r\n");
    if (headerEnd < 0)
        return;

    QByteArray head = buffer.left(headerEnd);
    QByteArray body = buffer.mid(headerEnd + 4);

    int contentLength = parseHeaders(head).value("content-length", "0").toInt();
    if (body.size() < contentLength)
        return;

    m_buffers.remove(socket);
    handleRequest(socket, head, body.left(contentLength));
}

void AutomationServer::handleRequest(QTcpSocket *socket, const QByteArray &head, const QByteArray &body)
{
    QList<QByteArray> lines = head.split('\n');
    QList<QByteArray> requestLine = lines.first().trimmed().split(' ');
    if (requestLine.size() < 2) {
        respond(socket, 400, "text/plain", "Bad request line");
        return;
    }

    const QByteArray method = requestLine.at(0);
    const QByteArray path = requestLine.at(1);

    if (method == "OPTIONS") { // CORS preflight
        respond(socket, 204, "text/plain", QByteArray());
        return;
    }

    if (method == "GET" && (path == "/" || path == "/health")) {
        QJsonObject info;
        info["app"] = APP_NAME;
        info["version"] = APP_VERSION;
        info["mcp"] = QString("http://127.0.0.1:%1/mcp").arg(port());
        respond(socket, 200, "application/json",
            QJsonDocument(info).toJson(QJsonDocument::Compact));
        return;
    }

    if (path == "/mcp") {
        if (method == "POST") {
            QJsonParseError error;
            QJsonDocument doc = QJsonDocument::fromJson(body, &error);
            if (error.error != QJsonParseError::NoError || !doc.isObject()) {
                respond(socket, 400, "application/json",
                    "{\"jsonrpc\":\"2.0\",\"id\":null,\"error\":{\"code\":-32700,\"message\":\"Parse error\"}}");
                return;
            }
            handleRpc(socket, doc.object());
            return;
        }
        if (method == "DELETE") { // session teardown; stateless server accepts it silently
            respond(socket, 200, "application/json", "{}");
            return;
        }
        // GET would request the SSE stream; this server is request/response only.
        respond(socket, 405, "text/plain", "SSE stream not supported; use POST");
        return;
    }

    respond(socket, 404, "text/plain", "Not found");
}

void AutomationServer::handleRpc(QTcpSocket *socket, const QJsonObject &message)
{
    const QString method = message.value("method").toString();
    const QJsonValue id = message.value("id");
    const bool notification = !message.contains("id");

    if (method == "initialize") {
        m_sessionId = QUuid::createUuid().toByteArray(QUuid::WithoutBraces);

        QString requested = message.value("params").toObject().value("protocolVersion").toString();
        QString version = kCurrentProtocolVersion;
        for (size_t i = 0; i < sizeof(kProtocolVersions) / sizeof(*kProtocolVersions); i++)
            if (requested == kProtocolVersions[i]) version = kProtocolVersions[i];

        QJsonObject capabilities;
        capabilities["tools"] = QJsonObject();

        QJsonObject serverInfo;
        serverInfo["name"] = QLatin1String("candle");
        serverInfo["title"] = QLatin1String(APP_NAME);
        serverInfo["version"] = APP_VERSION;

        QJsonObject result;
        result["protocolVersion"] = version;
        result["capabilities"] = capabilities;
        result["serverInfo"] = serverInfo;

        QJsonObject response;
        response["jsonrpc"] = QLatin1String("2.0");
        response["id"] = id;
        response["result"] = result;
        respondJson(socket, response);
        return;
    }

    if (method.startsWith("notifications/")) {
        respond(socket, notification ? 202 : 200, "application/json",
            notification ? QByteArray() : QByteArray("{}"));
        return;
    }

    if (method == "ping") {
        if (notification) {
            respond(socket, 202, "application/json", QByteArray());
            return;
        }
        QJsonObject response;
        response["jsonrpc"] = QLatin1String("2.0");
        response["id"] = id;
        response["result"] = QJsonObject();
        respondJson(socket, response);
        return;
    }

    if (method == "tools/list") {
        if (notification) {
            respond(socket, 202, "application/json", QByteArray());
            return;
        }
        QJsonObject result;
        result["tools"] = m_tools->toolList();

        QJsonObject response;
        response["jsonrpc"] = QLatin1String("2.0");
        response["id"] = id;
        response["result"] = result;
        respondJson(socket, response);
        return;
    }

    if (method == "tools/call") {
        if (notification) {
            respond(socket, 202, "application/json", QByteArray());
            return;
        }
        handleToolCall(socket, id, message.value("params").toObject());
        return;
    }

    if (notification) {
        respond(socket, 202, "application/json", QByteArray());
        return;
    }
    respondRpcError(socket, id, -32601, "Method not found: " + method);
}

void AutomationServer::handleToolCall(QTcpSocket *socket, const QJsonValue &id, const QJsonObject &params)
{
    if (m_callInFlight) {
        respondRpcError(socket, id, -32000, "Another tool call is in progress; retry.");
        return;
    }

    const QString name = params.value("name").toString();
    const QJsonObject args = params.value("arguments").toObject();

    QPointer<QTcpSocket> guard(socket);
    m_callInFlight = true;

    m_tools->call(name, args, [this, guard, id](const QJsonArray &content, bool isError) {
        m_callInFlight = false;

        if (!guard) // client hung up while the tool was running
            return;

        QJsonObject result;
        result["content"] = content;
        result["isError"] = isError;

        QJsonObject response;
        response["jsonrpc"] = QLatin1String("2.0");
        response["id"] = id;
        response["result"] = result;
        respondJson(guard, response);
    });
}

void AutomationServer::respond(QTcpSocket *socket, int code, const QByteArray &contentType,
    const QByteArray &body)
{
    QByteArray response;
    response += "HTTP/1.1 " + QByteArray::number(code) + " " + reason(code) + "\r\n";
    response += "Content-Type: " + contentType + "\r\n";
    response += "Content-Length: " + QByteArray::number(body.size()) + "\r\n";
    response += "Connection: close\r\n";
    response += "Access-Control-Allow-Origin: *\r\n";
    response += "Access-Control-Allow-Headers: Content-Type, Mcp-Session-Id, MCP-Protocol-Version\r\n";
    response += "Access-Control-Expose-Headers: Mcp-Session-Id\r\n";
    if (!m_sessionId.isEmpty())
        response += "Mcp-Session-Id: " + m_sessionId + "\r\n";
    response += "\r\n";
    response += body;

    socket->write(response);
    socket->flush();
    socket->disconnectFromHost();
}

void AutomationServer::respondJson(QTcpSocket *socket, const QJsonObject &message)
{
    respond(socket, 200, "application/json", QJsonDocument(message).toJson(QJsonDocument::Compact));
}

void AutomationServer::respondRpcError(QTcpSocket *socket, const QJsonValue &id, int code,
    const QString &message)
{
    QJsonObject error;
    error["code"] = code;
    error["message"] = message;

    QJsonObject response;
    response["jsonrpc"] = QLatin1String("2.0");
    response["id"] = id;
    response["error"] = error;

    respondJson(socket, response);
}
