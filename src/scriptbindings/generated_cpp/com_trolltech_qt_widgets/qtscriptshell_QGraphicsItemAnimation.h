#ifndef QTSCRIPTSHELL_QGRAPHICSITEMANIMATION_H
#define QTSCRIPTSHELL_QGRAPHICSITEMANIMATION_H

#include <qgraphicsitemanimation.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QGraphicsItemAnimation : public QGraphicsItemAnimation
{
public:
    QtScriptShell_QGraphicsItemAnimation(QObject*  parent = 0);
    ~QtScriptShell_QGraphicsItemAnimation();

    void afterAnimationStep(qreal  step);
    void beforeAnimationStep(qreal  step);
    void childEvent(QChildEvent*  event);
    void customEvent(QEvent*  event);
    bool  event(QEvent*  event);
    bool  eventFilter(QObject*  watched, QEvent*  event);
    void timerEvent(QTimerEvent*  event);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QGRAPHICSITEMANIMATION_H
