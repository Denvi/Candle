#ifndef CONNECTION_H
#define CONNECTION_H

#include <QtSerialPort/QSerialPort>

class Connection : public QObject
{
    Q_OBJECT;
public:
    Connection();
    ~Connection();
    bool openConnection();
    void setPortName(QString);
    void setBaudRate(int);
    void sendByteArray(QByteArray);
    bool isConnected();
    void sendLine(QString);
    void closeConnection();
private:
    QSerialPort m_serialPort;
    void setupSerialPort();

private slots:
    void onSerialPortReadyRead();
    void onSerialPortError(QSerialPort::SerialPortError);

signals:
    void lineReceived(QString line);
    void error(QString text);
};
#endif // CONNECTION_H
