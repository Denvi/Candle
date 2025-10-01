#include "serialportconnection.h"

SerialPortConnection::SerialPortConnection(QObject *parent) : Connection(parent)
{
    m_serialPort.setDataBits(QSerialPort::Data8);
    m_serialPort.setParity(QSerialPort::NoParity);
    m_serialPort.setStopBits(QSerialPort::OneStop);
    m_serialPort.setFlowControl(QSerialPort::NoFlowControl);

    QObject::connect(&m_serialPort, &QSerialPort::readyRead, this, &SerialPortConnection::onReadyRead, Qt::QueuedConnection);
    QObject::connect(&m_serialPort, QOverload<QSerialPort::SerialPortError>::of(&QSerialPort::error), this,
        &SerialPortConnection::onError);
}

SerialPortConnection::SerialPortConnection(const QString &portName, const int baudRate, QObject *parent)
    : SerialPortConnection(parent)
{
    m_serialPort.setPortName(portName);
    m_serialPort.setBaudRate(baudRate);
}

void SerialPortConnection::connect()
{ 
    if (!m_serialPort.isOpen() && m_serialPort.open(QIODevice::ReadWrite))
    {
        m_serialPort.setDataTerminalReady(true);

        emit connected();
    }
}

void SerialPortConnection::disconnect()
{
    if (m_serialPort.isOpen())
    {
        m_serialPort.close();

        emit disconnected();
    }
}

bool SerialPortConnection::isConnected() const
{
    return m_serialPort.isOpen();
}

void SerialPortConnection::send(const QByteArray &data)
{
    m_serialPort.write(data);
}

void SerialPortConnection::send(const QString &data)
{
    m_serialPort.write((data + "\r").toLatin1());
}

void SerialPortConnection::send(const char *data)
{
    m_serialPort.write(data);
}

void SerialPortConnection::setPortName(const QString &portName)
{
    m_serialPort.setPortName(portName);
}

QString SerialPortConnection::portName() const
{
    return m_serialPort.portName();
}

void SerialPortConnection::setBaudRate(const int baudRate)
{
    m_serialPort.setBaudRate(baudRate);
}

int SerialPortConnection::baudRate() const
{
    return m_serialPort.baudRate();
}

void SerialPortConnection::onReadyRead()
{
    while (m_serialPort.canReadLine())
    {
        emit dataReceived(m_serialPort.readLine().trimmed());
    }
}

void SerialPortConnection::onError(QSerialPort::SerialPortError error)
{
    if (error != QSerialPort::NoError)
        emit errorOccurred(QString::number(error) + ": " + m_serialPort.errorString());
}