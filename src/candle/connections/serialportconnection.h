#pragma once

#include "connection.h"
#include <QSerialPort>

class SerialPortConnection : public Connection
{
    Q_OBJECT

public:
    explicit SerialPortConnection(QObject *parent = nullptr);
    SerialPortConnection(const QString &portName, const int baudRate, QObject *parent = nullptr);

    void connect() override;
    void disconnect() override;
    bool isConnected() const override;

    void send(const QByteArray &data) override;
    void send(const QString &data) override;
    void send(const char *data) override;

    void setPortName(const QString &portName);
    QString portName() const;

    void setBaudRate(const int baudRate);
    int baudRate() const;

private slots:
    void onReadyRead();
    void onError(QSerialPort::SerialPortError error);

private:
    QSerialPort m_serialPort;
};