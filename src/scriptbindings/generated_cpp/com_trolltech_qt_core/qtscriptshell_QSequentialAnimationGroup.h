#ifndef QTSCRIPTSHELL_QSEQUENTIALANIMATIONGROUP_H
#define QTSCRIPTSHELL_QSEQUENTIALANIMATIONGROUP_H

#include <qsequentialanimationgroup.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QSequentialAnimationGroup : public QSequentialAnimationGroup
{
public:
    QtScriptShell_QSequentialAnimationGroup(QObject*  parent = 0);
    ~QtScriptShell_QSequentialAnimationGroup();

    void childEvent(QChildEvent*  event);
    void customEvent(QEvent*  event);
    int  duration() const;
    bool  event(QEvent*  event);
    bool  eventFilter(QObject*  watched, QEvent*  event);
    void timerEvent(QTimerEvent*  event);
    void updateCurrentTime(int  arg__1);
    void updateDirection(QAbstractAnimation::Direction  direction);
    void updateState(QAbstractAnimation::State  newState, QAbstractAnimation::State  oldState);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QSEQUENTIALANIMATIONGROUP_H
