#ifndef QTSCRIPTSHELL_QEVENTLOOP_H
#define QTSCRIPTSHELL_QEVENTLOOP_H

#include <qeventloop.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QEventLoop : public QEventLoop
{
public:
    QtScriptShell_QEventLoop(QObject*  parent = 0);
    ~QtScriptShell_QEventLoop();

    void childEvent(QChildEvent*  event);
    void customEvent(QEvent*  event);
    bool  event(QEvent*  event);
    bool  eventFilter(QObject*  watched, QEvent*  event);
    void timerEvent(QTimerEvent*  event);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QEVENTLOOP_H
