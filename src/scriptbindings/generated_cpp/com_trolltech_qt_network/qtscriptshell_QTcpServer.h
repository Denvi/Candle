#ifndef QTSCRIPTSHELL_QTCPSERVER_H
#define QTSCRIPTSHELL_QTCPSERVER_H

#include <qtcpserver.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QTcpServer : public QTcpServer
{
public:
    QtScriptShell_QTcpServer(QObject*  parent = 0);
    ~QtScriptShell_QTcpServer();

    void childEvent(QChildEvent*  event);
    void customEvent(QEvent*  event);
    bool  event(QEvent*  event);
    bool  eventFilter(QObject*  watched, QEvent*  event);
    bool  hasPendingConnections() const;
    QTcpSocket*  nextPendingConnection();
    void timerEvent(QTimerEvent*  event);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QTCPSERVER_H
