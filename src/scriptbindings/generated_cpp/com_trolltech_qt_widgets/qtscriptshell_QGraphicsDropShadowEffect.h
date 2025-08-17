#ifndef QTSCRIPTSHELL_QGRAPHICSDROPSHADOWEFFECT_H
#define QTSCRIPTSHELL_QGRAPHICSDROPSHADOWEFFECT_H

#include <qgraphicseffect.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QGraphicsDropShadowEffect : public QGraphicsDropShadowEffect
{
public:
    QtScriptShell_QGraphicsDropShadowEffect(QObject*  parent = 0);
    ~QtScriptShell_QGraphicsDropShadowEffect();

    QRectF  boundingRectFor(const QRectF&  rect) const;
    void childEvent(QChildEvent*  event);
    void customEvent(QEvent*  event);
    void draw(QPainter*  painter);
    bool  event(QEvent*  event);
    bool  eventFilter(QObject*  watched, QEvent*  event);
    void sourceChanged(QGraphicsEffect::ChangeFlags  flags);
    void timerEvent(QTimerEvent*  event);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QGRAPHICSDROPSHADOWEFFECT_H
