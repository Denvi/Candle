#ifndef QTSCRIPTSHELL_QTCPSOCKET_H
#define QTSCRIPTSHELL_QTCPSOCKET_H

#include <qtcpsocket.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QTcpSocket : public QTcpSocket
{
public:
    QtScriptShell_QTcpSocket(QObject*  parent = 0);
    ~QtScriptShell_QTcpSocket();

    bool  atEnd() const;
    qint64  bytesAvailable() const;
    qint64  bytesToWrite() const;
    bool  canReadLine() const;
    void childEvent(QChildEvent*  event);
    void close();
    void connectToHost(const QHostAddress&  address, unsigned short  port, QIODevice::OpenMode  mode);
    void connectToHost(const QString&  hostName, unsigned short  port, QIODevice::OpenMode  mode, QAbstractSocket::NetworkLayerProtocol  protocol);
    void customEvent(QEvent*  event);
    void disconnectFromHost();
    bool  event(QEvent*  event);
    bool  eventFilter(QObject*  watched, QEvent*  event);
    bool  isSequential() const;
    bool  open(QIODevice::OpenMode  mode);
    qint64  pos() const;
    qint64  readData(char*  data, qint64  maxlen);
    qint64  readLineData(char*  data, qint64  maxlen);
    bool  reset();
    void resume();
    bool  seek(qint64  pos);
    void setReadBufferSize(qint64  size);
    void setSocketOption(QAbstractSocket::SocketOption  option, const QVariant&  value);
    qint64  size() const;
    QVariant  socketOption(QAbstractSocket::SocketOption  option);
    void timerEvent(QTimerEvent*  event);
    bool  waitForBytesWritten(int  msecs);
    bool  waitForConnected(int  msecs);
    bool  waitForDisconnected(int  msecs);
    bool  waitForReadyRead(int  msecs);
    qint64  writeData(const char*  data, qint64  len);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QTCPSOCKET_H
