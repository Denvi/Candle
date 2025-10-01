#pragma once

#include <QObject>

class Connection : public QObject
{
    Q_OBJECT

protected:
    explicit Connection(QObject *parent = nullptr) : QObject(parent) {}

public:
    virtual ~Connection() = default;

    virtual void connect() = 0;
    virtual void disconnect() = 0;
    virtual bool isConnected() const = 0;

    virtual void send(const QByteArray &data) = 0;
    virtual void send(const QString &data) = 0;
    virtual void send(const char *data) = 0;

signals:
    void dataReceived(const QString &data);
    void errorOccurred(const QString &error);
    void connected();
    void disconnected();
};