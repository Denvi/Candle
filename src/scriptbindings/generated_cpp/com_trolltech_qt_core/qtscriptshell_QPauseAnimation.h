#ifndef QTSCRIPTSHELL_QPAUSEANIMATION_H
#define QTSCRIPTSHELL_QPAUSEANIMATION_H

#include <qpauseanimation.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QPauseAnimation : public QPauseAnimation
{
public:
    QtScriptShell_QPauseAnimation(QObject*  parent = 0);
    QtScriptShell_QPauseAnimation(int  msecs, QObject*  parent = 0);
    ~QtScriptShell_QPauseAnimation();

    void childEvent(QChildEvent*  event);
    void customEvent(QEvent*  event);
    int  duration() const;
    bool  event(QEvent*  e);
    bool  eventFilter(QObject*  watched, QEvent*  event);
    void timerEvent(QTimerEvent*  event);
    void updateCurrentTime(int  arg__1);
    void updateDirection(QAbstractAnimation::Direction  direction);
    void updateState(QAbstractAnimation::State  newState, QAbstractAnimation::State  oldState);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QPAUSEANIMATION_H
