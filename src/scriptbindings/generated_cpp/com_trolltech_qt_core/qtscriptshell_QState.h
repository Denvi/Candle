#ifndef QTSCRIPTSHELL_QSTATE_H
#define QTSCRIPTSHELL_QSTATE_H

#include <qstate.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QState : public QState
{
public:
    QtScriptShell_QState(QState*  parent = 0);
    QtScriptShell_QState(QState::ChildMode  childMode, QState*  parent = 0);
    ~QtScriptShell_QState();

    void childEvent(QChildEvent*  event);
    void customEvent(QEvent*  event);
    bool  event(QEvent*  e);
    bool  eventFilter(QObject*  watched, QEvent*  event);
    void onEntry(QEvent*  event);
    void onExit(QEvent*  event);
    void timerEvent(QTimerEvent*  event);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QSTATE_H
