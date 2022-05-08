#ifndef QTSCRIPTSHELL_QFINALSTATE_H
#define QTSCRIPTSHELL_QFINALSTATE_H

#include <qfinalstate.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QFinalState : public QFinalState
{
public:
    QtScriptShell_QFinalState(QState*  parent = 0);
    ~QtScriptShell_QFinalState();

    void childEvent(QChildEvent*  event);
    void customEvent(QEvent*  event);
    bool  event(QEvent*  e);
    bool  eventFilter(QObject*  watched, QEvent*  event);
    void onEntry(QEvent*  event);
    void onExit(QEvent*  event);
    void timerEvent(QTimerEvent*  event);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QFINALSTATE_H
