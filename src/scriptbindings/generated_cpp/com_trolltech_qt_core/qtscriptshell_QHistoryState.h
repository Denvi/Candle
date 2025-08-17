#ifndef QTSCRIPTSHELL_QHISTORYSTATE_H
#define QTSCRIPTSHELL_QHISTORYSTATE_H

#include <qhistorystate.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QHistoryState : public QHistoryState
{
public:
    QtScriptShell_QHistoryState(QHistoryState::HistoryType  type, QState*  parent = 0);
    QtScriptShell_QHistoryState(QState*  parent = 0);
    ~QtScriptShell_QHistoryState();

    void childEvent(QChildEvent*  event);
    void customEvent(QEvent*  event);
    bool  event(QEvent*  e);
    bool  eventFilter(QObject*  watched, QEvent*  event);
    void onEntry(QEvent*  event);
    void onExit(QEvent*  event);
    void timerEvent(QTimerEvent*  event);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QHISTORYSTATE_H
