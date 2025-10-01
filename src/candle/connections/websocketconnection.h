#pragma once

#include "connection.h"
#include <QObject>
#include <QWebSocket>

class WebSocketConnection : public Connection
{
    Q_OBJECT

public:
    explicit WebSocketConnection(QObject *parent = nullptr);
    WebSocketConnection(const QString &url, bool binary, QObject *parent = nullptr);

    void connect() override;
    void disconnect() override;
    bool isConnected() const override;

    void send(const QByteArray &data) override;
    void send(const QString &data) override;
    void send(const char *data) override;

    void setUrl(const QString &url);
    QString url() const;

    void setBinaryMode(bool binaryMode);
    bool binaryMode() const;

private slots:
    void onBinaryMessage(const QByteArray &message);
    void onTextMessage(const QString &message);
    void onError(QAbstractSocket::SocketError error);

private:
    QWebSocket m_ws;
    QString m_url;
    bool m_binaryMode;

    void processMessage(const QString &message, const QString &delimeter = "\n");
};