#ifndef QTSCRIPTSHELL_QPROPERTYANIMATION_H
#define QTSCRIPTSHELL_QPROPERTYANIMATION_H

#include <qpropertyanimation.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QPropertyAnimation : public QPropertyAnimation
{
public:
    QtScriptShell_QPropertyAnimation(QObject*  parent = 0);
    QtScriptShell_QPropertyAnimation(QObject*  target, const QByteArray&  propertyName, QObject*  parent = 0);
    ~QtScriptShell_QPropertyAnimation();

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

#endif // QTSCRIPTSHELL_QPROPERTYANIMATION_H
