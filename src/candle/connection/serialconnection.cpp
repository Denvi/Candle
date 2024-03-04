#include "serialconnection.h"
#include <QDebug>

SerialConnection::SerialConnection(QObject *parent) : Connection(parent) {
    setupSerialPort();

    // if (m_settings->port() != "") {
    //     m_serialPort.setPortName(m_settings->port());
    //     m_serialPort.setBaudRate(m_settings->baud());
    // }
}

SerialConnection::~SerialConnection()
{
    if (m_serialPort.isOpen()) m_serialPort.close();
}

bool SerialConnection::openConnection()
{
    return m_serialPort.open(QIODevice::ReadWrite);
}

void SerialConnection::setPortName(QString portName)
{
    m_serialPort.setPortName(portName);
}

void SerialConnection::setBaudRate(int baudRate)
{
    m_serialPort.setBaudRate(baudRate);
}

void SerialConnection::sendByteArray(QByteArray data)
{
    m_serialPort.write(data);
}

bool SerialConnection::isConnected()
{
    return m_serialPort.isOpen();
}

void SerialConnection::sendLine(QString data)
{
    m_serialPort.write((data + "\n").toLatin1());
}

void SerialConnection::closeConnection()
{
    if (m_serialPort.isOpen()) m_serialPort.close();
}

void SerialConnection::setupSerialPort()
{
    m_serialPort.setParity(QSerialPort::NoParity);
    m_serialPort.setDataBits(QSerialPort::Data8);
    m_serialPort.setFlowControl(QSerialPort::NoFlowControl);
    m_serialPort.setStopBits(QSerialPort::OneStop);

    // Signals/slots
    connect(&m_serialPort, SIGNAL(readyRead()), this, SLOT(onSerialPortReadyRead()), Qt::QueuedConnection);
    connect(&m_serialPort, SIGNAL(error(QSerialPort::SerialPortError)), this, SLOT(onSerialPortError(QSerialPort::SerialPortError)));
}

void SerialConnection::onSerialPortReadyRead()
{
    while (m_serialPort.canReadLine()) {
        QString line = m_serialPort.readLine().trimmed();
        emit this->lineReceived(line);
    }
}

void SerialConnection::onSerialPortError(QSerialPort::SerialPortError error)
{
    static QSerialPort::SerialPortError previousError;

    if (error != QSerialPort::NoError && error != previousError) {
        previousError = error;
        if (m_serialPort.isOpen()) {
            m_serialPort.close();
        }
        emit this->error(tr("Serial port error ") + QString::number(error) + ": " + m_serialPort.errorString());
    }
}
