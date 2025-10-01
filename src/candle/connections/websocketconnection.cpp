#include "websocketconnection.h"
#include <QAbstractSocket>

WebSocketConnection::WebSocketConnection(QObject *parent) : Connection(parent)
{
    m_binaryMode = false;

    QObject::connect(&m_ws, &QWebSocket::binaryMessageReceived, this, &WebSocketConnection::onBinaryMessage,
        Qt::QueuedConnection);
    QObject::connect(&m_ws, &QWebSocket::textMessageReceived, this, &WebSocketConnection::onTextMessage,
        Qt::QueuedConnection);
    QObject::connect(&m_ws, QOverload<QAbstractSocket::SocketError>::of(&QWebSocket::error), this,
        &WebSocketConnection::onError);
    QObject::connect(&m_ws, &QWebSocket::connected, this, &Connection::connected);
    QObject::connect(&m_ws, &QWebSocket::disconnected, this, &Connection::disconnected);
}

WebSocketConnection::WebSocketConnection(const QString &url, bool binary, QObject *parent) : WebSocketConnection(parent)
{
    m_url = url;
    m_binaryMode = binary;
}

void WebSocketConnection::connect()
{
    if (m_ws.state() == QAbstractSocket::ConnectedState)
        m_ws.close();

    m_ws.open(QUrl(m_url));
}

void WebSocketConnection::disconnect()
{
    m_ws.close();
}

bool WebSocketConnection::isConnected() const
{
    return m_ws.state() == QAbstractSocket::ConnectedState;
}

void WebSocketConnection::send(const QByteArray &data)
{
    m_ws.sendBinaryMessage(data);
}

void WebSocketConnection::send(const QString &data)
{
    m_ws.sendTextMessage(data + "\n");
}

void WebSocketConnection::send(const char *data)
{
    m_ws.sendBinaryMessage(data);
}

void WebSocketConnection::setUrl(const QString &address)
{
    m_url = address;
}

QString WebSocketConnection::url() const
{
    return m_url;
}

void WebSocketConnection::setBinaryMode(bool binaryMode)
{
    m_binaryMode = binaryMode;
}

bool WebSocketConnection::binaryMode() const
{
    return m_binaryMode;
}

void WebSocketConnection::onBinaryMessage(const QByteArray &message)
{
    if (m_binaryMode)
        processMessage(message);
}

void WebSocketConnection::onTextMessage(const QString &message)
{
    if (!m_binaryMode)
        processMessage(message);
}

void WebSocketConnection::onError(QAbstractSocket::SocketError error)
{
    emit errorOccurred(QString::number(error) + ": " + m_ws.errorString());
}

void WebSocketConnection::processMessage(const QString &message, const QString &delimeter)
{
    static QString buffer;

    buffer += message;

    auto f = 0;
    auto d = -1;

    while ((d = buffer.indexOf(delimeter, f)) != -1)
    {
        auto line = buffer.mid(f, d - f).trimmed();
        if (!line.isEmpty())
            emit dataReceived(line);

        f = d + delimeter.length();
    }

    buffer = buffer.mid(f);
}