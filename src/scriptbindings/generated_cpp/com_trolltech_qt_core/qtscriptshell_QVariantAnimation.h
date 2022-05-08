#ifndef QTSCRIPTSHELL_QVARIANTANIMATION_H
#define QTSCRIPTSHELL_QVARIANTANIMATION_H

#include <qvariantanimation.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QVariantAnimation : public QVariantAnimation
{
public:
    QtScriptShell_QVariantAnimation(QObject*  parent = 0);
    ~QtScriptShell_QVariantAnimation();

    void childEvent(QChildEvent*  event);
    void customEvent(QEvent*  event);
    int  duration() const;
    bool  event(QEvent*  event);
    bool  eventFilter(QObject*  watched, QEvent*  event);
    QVariant  interpolated(const QVariant&  from, const QVariant&  to, qreal  progress) const;
    void timerEvent(QTimerEvent*  event);
    void updateCurrentTime(int  arg__1);
    void updateCurrentValue(const QVariant&  value);
    void updateDirection(QAbstractAnimation::Direction  direction);
    void updateState(QAbstractAnimation::State  newState, QAbstractAnimation::State  oldState);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QVARIANTANIMATION_H
