#ifndef QTSCRIPTSHELL_QPROCESS_H
#define QTSCRIPTSHELL_QPROCESS_H

#include <qprocess.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QProcess : public QProcess
{
public:
    QtScriptShell_QProcess(QObject*  parent = 0);
    ~QtScriptShell_QProcess();

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
    bool  open(QIODevice::OpenMode  mode = ReadWrite);
    qint64  pos() const;
    qint64  readData(char*  data, qint64  maxlen);
    qint64  readLineData(char*  data, qint64  maxlen);
    bool  reset();
    bool  seek(qint64  pos);
    void setupChildProcess();
    qint64  size() const;
    void timerEvent(QTimerEvent*  event);
    bool  waitForBytesWritten(int  msecs = 30000);
    bool  waitForReadyRead(int  msecs = 30000);
    qint64  writeData(const char*  data, qint64  len);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QPROCESS_H
