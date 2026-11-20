// This file is a part of "Candle" application.

// Minimal MCP (Model Context Protocol) server over the Streamable HTTP
// transport: JSON-RPC 2.0 served at POST /mcp on 127.0.0.1 only.
// Enabled by the --mcp command line flag; see main.cpp.

#ifndef AUTOMATIONSERVER_H
#define AUTOMATIONSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QHash>
#include <QJsonObject>
#include <QJsonValue>

class frmMain;
class AutomationTools;

class AutomationServer : public QObject
{
    Q_OBJECT

public:
    explicit AutomationServer(frmMain *mainWindow, quint16 port, bool allowMotion,
        QObject *parent = nullptr);

    bool start();
    quint16 port() const;

private slots:
    void onNewConnection();

private:
    void onReadyRead(QTcpSocket *socket);
    void handleRequest(QTcpSocket *socket, const QByteArray &head, const QByteArray &body);
    void handleRpc(QTcpSocket *socket, const QJsonObject &message);
    void handleToolCall(QTcpSocket *socket, const QJsonValue &id, const QJsonObject &params);

    void respond(QTcpSocket *socket, int code, const QByteArray &contentType,
        const QByteArray &body);
    void respondJson(QTcpSocket *socket, const QJsonObject &message);
    void respondRpcError(QTcpSocket *socket, const QJsonValue &id, int code, const QString &message);

    static QByteArray reason(int code);
    static QHash<QByteArray, QByteArray> parseHeaders(const QByteArray &head);

    frmMain *m_main;
    QTcpServer m_server;
    AutomationTools *m_tools;
    QHash<QTcpSocket*, QByteArray> m_buffers;
    QByteArray m_sessionId;
    quint16 m_port;
    bool m_callInFlight;
};

#endif // AUTOMATIONSERVER_H
