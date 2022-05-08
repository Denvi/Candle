#ifndef QTSCRIPTSHELL_QGRAPHICSCOLORIZEEFFECT_H
#define QTSCRIPTSHELL_QGRAPHICSCOLORIZEEFFECT_H

#include <qgraphicseffect.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QGraphicsColorizeEffect : public QGraphicsColorizeEffect
{
public:
    QtScriptShell_QGraphicsColorizeEffect(QObject*  parent = 0);
    ~QtScriptShell_QGraphicsColorizeEffect();

    QRectF  boundingRectFor(const QRectF&  sourceRect) const;
    void childEvent(QChildEvent*  event);
    void customEvent(QEvent*  event);
    void draw(QPainter*  painter);
    bool  event(QEvent*  event);
    bool  eventFilter(QObject*  watched, QEvent*  event);
    void sourceChanged(QGraphicsEffect::ChangeFlags  flags);
    void timerEvent(QTimerEvent*  event);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QGRAPHICSCOLORIZEEFFECT_H
