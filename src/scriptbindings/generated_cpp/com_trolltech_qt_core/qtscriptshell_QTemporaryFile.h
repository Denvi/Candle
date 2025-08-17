#ifndef QTSCRIPTSHELL_QTEMPORARYFILE_H
#define QTSCRIPTSHELL_QTEMPORARYFILE_H

#include <qtemporaryfile.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QTemporaryFile : public QTemporaryFile
{
public:
    QtScriptShell_QTemporaryFile();
    QtScriptShell_QTemporaryFile(QObject*  parent);
    QtScriptShell_QTemporaryFile(const QString&  templateName);
    QtScriptShell_QTemporaryFile(const QString&  templateName, QObject*  parent);
    ~QtScriptShell_QTemporaryFile();

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
    bool  open(QIODevice::OpenMode  flags);
    QFileDevice::Permissions  permissions() const;
    qint64  pos() const;
    qint64  readData(char*  data, qint64  maxlen);
    qint64  readLineData(char*  data, qint64  maxlen);
    bool  reset();
    bool  resize(qint64  sz);
    bool  seek(qint64  offset);
    bool  setPermissions(QFileDevice::Permissions  permissionSpec);
    qint64  size() const;
    void timerEvent(QTimerEvent*  event);
    bool  waitForBytesWritten(int  msecs);
    bool  waitForReadyRead(int  msecs);
    qint64  writeData(const char*  data, qint64  len);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QTEMPORARYFILE_H
