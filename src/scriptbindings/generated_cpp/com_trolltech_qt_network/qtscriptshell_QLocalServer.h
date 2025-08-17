#ifndef QTSCRIPTSHELL_QLOCALSERVER_H
#define QTSCRIPTSHELL_QLOCALSERVER_H

#include <qlocalserver.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QLocalServer : public QLocalServer
{
public:
    QtScriptShell_QLocalServer(QObject*  parent = 0);
    ~QtScriptShell_QLocalServer();

    void childEvent(QChildEvent*  event);
    void customEvent(QEvent*  event);
    bool  event(QEvent*  event);
    bool  eventFilter(QObject*  watched, QEvent*  event);
    bool  hasPendingConnections() const;
    void incomingConnection(quintptr  socketDescriptor);
    QLocalSocket*  nextPendingConnection();
    void timerEvent(QTimerEvent*  event);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QLOCALSERVER_H
