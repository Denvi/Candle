#pragma once

#include "connection.h"
#include <QObject>
#include <QWebSocket>

class WebSocketConnection : public Connection
{
    Q_OBJECT

public:
    explicit WebSocketConnection(QObject *parent = nullptr);
    WebSocketConnection(const QString &url, QObject *parent = nullptr);

    void connect() override;
    void disconnect() override;
    bool isConnected() const override;

    void send(const QByteArray &data) override;
    void send(const QString &data) override;
    void send(const char *data) override;

    void setUrl(const QString &url);
    QString url() const;

private slots:
    void onBinaryMessage(const QByteArray &message);
    void onError(QAbstractSocket::SocketError error);

private:
    QWebSocket m_ws;
    QString m_url;
};