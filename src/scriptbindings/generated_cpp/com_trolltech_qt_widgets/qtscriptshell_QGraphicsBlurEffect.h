#ifndef QTSCRIPTSHELL_QGRAPHICSBLUREFFECT_H
#define QTSCRIPTSHELL_QGRAPHICSBLUREFFECT_H

#include <qgraphicseffect.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QGraphicsBlurEffect : public QGraphicsBlurEffect
{
public:
    QtScriptShell_QGraphicsBlurEffect(QObject*  parent = 0);
    ~QtScriptShell_QGraphicsBlurEffect();

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

#endif // QTSCRIPTSHELL_QGRAPHICSBLUREFFECT_H
