#ifndef QTSCRIPTSHELL_QABSTRACTSTATE_H
#define QTSCRIPTSHELL_QABSTRACTSTATE_H

#include <qabstractstate.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QAbstractState : public QAbstractState
{
public:
    QtScriptShell_QAbstractState(QState*  parent = 0);
    ~QtScriptShell_QAbstractState();

    void childEvent(QChildEvent*  event);
    void customEvent(QEvent*  event);
    bool  event(QEvent*  e);
    bool  eventFilter(QObject*  watched, QEvent*  event);
    void onEntry(QEvent*  event);
    void onExit(QEvent*  event);
    void timerEvent(QTimerEvent*  event);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QABSTRACTSTATE_H
