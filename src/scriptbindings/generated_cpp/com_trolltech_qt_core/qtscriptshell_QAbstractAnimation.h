#ifndef QTSCRIPTSHELL_QABSTRACTANIMATION_H
#define QTSCRIPTSHELL_QABSTRACTANIMATION_H

#include <qabstractanimation.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QAbstractAnimation : public QAbstractAnimation
{
public:
    QtScriptShell_QAbstractAnimation(QObject*  parent = 0);
    ~QtScriptShell_QAbstractAnimation();

    void childEvent(QChildEvent*  event);
    void customEvent(QEvent*  event);
    int  duration() const;
    bool  event(QEvent*  event);
    bool  eventFilter(QObject*  watched, QEvent*  event);
    void timerEvent(QTimerEvent*  event);
    void updateCurrentTime(int  currentTime);
    void updateDirection(QAbstractAnimation::Direction  direction);
    void updateState(QAbstractAnimation::State  newState, QAbstractAnimation::State  oldState);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QABSTRACTANIMATION_H
