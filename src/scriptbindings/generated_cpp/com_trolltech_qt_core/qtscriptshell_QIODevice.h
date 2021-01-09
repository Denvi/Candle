#ifndef QTSCRIPTSHELL_QIODEVICE_H
#define QTSCRIPTSHELL_QIODEVICE_H

#include <qiodevice.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QIODevice : public QIODevice
{
public:
    QtScriptShell_QIODevice();
    QtScriptShell_QIODevice(QObject*  parent);
    ~QtScriptShell_QIODevice();

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
    bool  open(QIODevice::OpenMode  mode);
    qint64  pos() const;
    qint64  readData(char*  data, qint64  maxlen);
    qint64  readLineData(char*  data, qint64  maxlen);
    bool  reset();
    bool  seek(qint64  pos);
    qint64  size() const;
    void timerEvent(QTimerEvent*  event);
    bool  waitForBytesWritten(int  msecs);
    bool  waitForReadyRead(int  msecs);
    qint64  writeData(const char*  data, qint64  len);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QIODEVICE_H
