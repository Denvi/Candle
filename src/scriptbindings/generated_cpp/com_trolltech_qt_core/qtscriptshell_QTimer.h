#ifndef QTSCRIPTSHELL_QTIMER_H
#define QTSCRIPTSHELL_QTIMER_H

#include <qtimer.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QTimer : public QTimer
{
public:
    QtScriptShell_QTimer(QObject*  parent = 0);
    ~QtScriptShell_QTimer();

    void childEvent(QChildEvent*  event);
    void customEvent(QEvent*  event);
    bool  event(QEvent*  event);
    bool  eventFilter(QObject*  watched, QEvent*  event);
    void timerEvent(QTimerEvent*  arg__1);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QTIMER_H
