#ifndef QTSCRIPTSHELL_QBUFFER_H
#define QTSCRIPTSHELL_QBUFFER_H

#include <qbuffer.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QBuffer : public QBuffer
{
public:
    QtScriptShell_QBuffer(QByteArray*  buf, QObject*  parent = 0);
    QtScriptShell_QBuffer(QObject*  parent = 0);
    ~QtScriptShell_QBuffer();

    bool  atEnd() const;
    qint64  bytesAvailable() const;
    qint64  bytesToWrite() const;
    bool  canReadLine() const;
    void childEvent(QChildEvent*  event);
    void close();
    void customEvent(QEvent*  event);
    bool  event(QEvent*  event);
    bool  eventFilter(QObject*  watched, QEvent*  event);
    bool  isSequential() const;
    bool  open(QIODevice::OpenMode  openMode);
    qint64  pos() const;
    qint64  readData(char*  data, qint64  maxlen);
    qint64  readLineData(char*  data, qint64  maxlen);
    bool  reset();
    bool  seek(qint64  off);
    qint64  size() const;
    void timerEvent(QTimerEvent*  event);
    bool  waitForBytesWritten(int  msecs);
    bool  waitForReadyRead(int  msecs);
    qint64  writeData(const char*  data, qint64  len);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QBUFFER_H
