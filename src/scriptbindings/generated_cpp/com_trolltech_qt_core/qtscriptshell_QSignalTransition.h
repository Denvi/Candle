#ifndef QTSCRIPTSHELL_QSIGNALTRANSITION_H
#define QTSCRIPTSHELL_QSIGNALTRANSITION_H

#include <qsignaltransition.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QSignalTransition : public QSignalTransition
{
public:
    QtScriptShell_QSignalTransition(QState*  sourceState = 0);
    QtScriptShell_QSignalTransition(const QObject*  sender, const char*  signal, QState*  sourceState = 0);
    ~QtScriptShell_QSignalTransition();

    void childEvent(QChildEvent*  event);
    void customEvent(QEvent*  event);
    bool  event(QEvent*  e);
    bool  eventFilter(QObject*  watched, QEvent*  event);
    bool  eventTest(QEvent*  event);
    void onTransition(QEvent*  event);
    void timerEvent(QTimerEvent*  event);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QSIGNALTRANSITION_H
