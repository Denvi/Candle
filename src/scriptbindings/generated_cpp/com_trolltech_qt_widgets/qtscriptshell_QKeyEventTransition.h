#ifndef QTSCRIPTSHELL_QKEYEVENTTRANSITION_H
#define QTSCRIPTSHELL_QKEYEVENTTRANSITION_H

#include <qkeyeventtransition.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QKeyEventTransition : public QKeyEventTransition
{
public:
    QtScriptShell_QKeyEventTransition(QObject*  object, QEvent::Type  type, int  key, QState*  sourceState = 0);
    QtScriptShell_QKeyEventTransition(QState*  sourceState = 0);
    ~QtScriptShell_QKeyEventTransition();

    void childEvent(QChildEvent*  event);
    void customEvent(QEvent*  event);
    bool  event(QEvent*  e);
    bool  eventFilter(QObject*  watched, QEvent*  event);
    bool  eventTest(QEvent*  event);
    void onTransition(QEvent*  event);
    void timerEvent(QTimerEvent*  event);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QKEYEVENTTRANSITION_H
