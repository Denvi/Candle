#pragma once

#include "connection.h"
#include <QTcpSocket>

class TelnetConnection : public Connection
{
    Q_OBJECT

public:
    explicit TelnetConnection(QObject *parent = nullptr);
    TelnetConnection(const QString &address, const int port, QObject *parent = nullptr);

    void connect() override;
    void disconnect() override;
    bool isConnected() const override;

    void send(const QByteArray &data) override;
    void send(const QString &data) override;
    void send(const char *data) override;

    void setAddress(const QString &address);
    QString address() const;

    void setPort(const int port);
    int port() const;

private slots:
    void onReadyRead();
    void onError(QAbstractSocket::SocketError error);

private:
    QTcpSocket m_socket;
    QString m_address;
    int m_port;
};