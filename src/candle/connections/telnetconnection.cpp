#include "telnetconnection.h"

TelnetConnection::TelnetConnection(QObject *parent) : Connection(parent)
{
    QObject::connect(&m_socket, &QTcpSocket::readyRead, this, &TelnetConnection::onReadyRead, Qt::QueuedConnection);
    QObject::connect(&m_socket, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::errorOccurred),
        this, &TelnetConnection::onError);
    QObject::connect(&m_socket, &QTcpSocket::connected, this, &Connection::connected);
    QObject::connect(&m_socket, &QTcpSocket::disconnected, this, &Connection::disconnected);
}

TelnetConnection::TelnetConnection(const QString &address, const int port, QObject *parent) : TelnetConnection(parent)
{
    m_address = address;
    m_port = port;
}

void TelnetConnection::connect()
{
    if (!m_socket.isOpen())
    {
        if (m_socket.state() != QAbstractSocket::UnconnectedState)
            m_socket.abort();

        m_socket.connectToHost(m_address, m_port);
    }
}

void TelnetConnection::disconnect()
{
    if (m_socket.isOpen())
    {
        m_socket.close();
    }
}

bool TelnetConnection::isConnected() const
{
    return m_socket.state() == QAbstractSocket::ConnectedState;
}

void TelnetConnection::send(const QByteArray &data)
{
    m_socket.write(data);
}

void TelnetConnection::send(const QString &data)
{
    m_socket.write((data + "\n").toLatin1());
}

void TelnetConnection::send(const char *data)
{
    m_socket.write(data);
}

void TelnetConnection::setAddress(const QString &address)
{
    m_address = address;
}

QString TelnetConnection::address() const
{
    return m_address;
}

void TelnetConnection::setPort(const int port)
{
    m_port = port;
}

int TelnetConnection::port() const
{
    return m_port;
}

void TelnetConnection::onReadyRead()
{
    while (m_socket.canReadLine())
    {
        emit dataReceived(m_socket.readLine().trimmed());
    }
}

void TelnetConnection::onError(QAbstractSocket::SocketError error)
{
    emit errorOccurred(QString::number(error) + ": " + m_socket.errorString());
}