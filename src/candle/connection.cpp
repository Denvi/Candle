#include "connection.h"

Connection::Connection() : QObject(nullptr) {
    setupSerialPort();

    // if (m_settings->port() != "") {
    //     m_serialPort.setPortName(m_settings->port());
    //     m_serialPort.setBaudRate(m_settings->baud());
    // }
}

Connection::~Connection()
{
    if (m_serialPort.isOpen()) m_serialPort.close();
}

bool Connection::openConnection()
{
    return m_serialPort.open(QIODevice::ReadWrite);
}

void Connection::setPortName(QString portName)
{
    m_serialPort.setPortName(portName);
}

void Connection::setBaudRate(int baudRate)
{
    m_serialPort.setBaudRate(baudRate);
}

void Connection::sendByteArray(QByteArray data)
{
    m_serialPort.write(data);
}

bool Connection::isConnected()
{
    return m_serialPort.isOpen();
}

void Connection::sendLine(QString data)
{
    m_serialPort.write((data + "\n").toLatin1());
}

void Connection::closeConnection()
{
    if (m_serialPort.isOpen()) m_serialPort.close();
}

void Connection::setupSerialPort()
{
    m_serialPort.setParity(QSerialPort::NoParity);
    m_serialPort.setDataBits(QSerialPort::Data8);
    m_serialPort.setFlowControl(QSerialPort::NoFlowControl);
    m_serialPort.setStopBits(QSerialPort::OneStop);

    // Signals/slots
    connect(&m_serialPort, SIGNAL(readyRead()), this, SLOT(onSerialPortReadyRead()), Qt::QueuedConnection);
    connect(&m_serialPort, SIGNAL(error(QSerialPort::SerialPortError)), this, SLOT(onSerialPortError(QSerialPort::SerialPortError)));
}

void Connection::onSerialPortReadyRead()
{
    while (m_serialPort.canReadLine()) {
        QString line = m_serialPort.readLine().trimmed();
        emit this->lineReceived(line);
    }
}

void Connection::onSerialPortError(QSerialPort::SerialPortError error)
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
