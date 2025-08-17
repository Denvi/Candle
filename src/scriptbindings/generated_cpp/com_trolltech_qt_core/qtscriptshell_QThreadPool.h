#ifndef QTSCRIPTSHELL_QTHREADPOOL_H
#define QTSCRIPTSHELL_QTHREADPOOL_H

#include <qthreadpool.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QThreadPool : public QThreadPool
{
public:
    QtScriptShell_QThreadPool(QObject*  parent = 0);
    ~QtScriptShell_QThreadPool();

    void childEvent(QChildEvent*  event);
    void customEvent(QEvent*  event);
    bool  event(QEvent*  event);
    bool  eventFilter(QObject*  watched, QEvent*  event);
    void timerEvent(QTimerEvent*  event);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QTHREADPOOL_H
