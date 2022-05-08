#ifndef QTSCRIPTSHELL_QABSTRACTTRANSITION_H
#define QTSCRIPTSHELL_QABSTRACTTRANSITION_H

#include <qabstracttransition.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QAbstractTransition : public QAbstractTransition
{
public:
    QtScriptShell_QAbstractTransition(QState*  sourceState = 0);
    ~QtScriptShell_QAbstractTransition();

    void childEvent(QChildEvent*  event);
    void customEvent(QEvent*  event);
    bool  event(QEvent*  e);
    bool  eventFilter(QObject*  watched, QEvent*  event);
    bool  eventTest(QEvent*  event);
    void onTransition(QEvent*  event);
    void timerEvent(QTimerEvent*  event);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QABSTRACTTRANSITION_H
