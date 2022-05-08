#ifndef QTSCRIPTSHELL_QMOUSEEVENTTRANSITION_H
#define QTSCRIPTSHELL_QMOUSEEVENTTRANSITION_H

#include <qmouseeventtransition.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QMouseEventTransition : public QMouseEventTransition
{
public:
    QtScriptShell_QMouseEventTransition(QObject*  object, QEvent::Type  type, Qt::MouseButton  button, QState*  sourceState = 0);
    QtScriptShell_QMouseEventTransition(QState*  sourceState = 0);
    ~QtScriptShell_QMouseEventTransition();

    void childEvent(QChildEvent*  event);
    void customEvent(QEvent*  event);
    bool  event(QEvent*  e);
    bool  eventFilter(QObject*  watched, QEvent*  event);
    bool  eventTest(QEvent*  event);
    void onTransition(QEvent*  event);
    void timerEvent(QTimerEvent*  event);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QMOUSEEVENTTRANSITION_H
