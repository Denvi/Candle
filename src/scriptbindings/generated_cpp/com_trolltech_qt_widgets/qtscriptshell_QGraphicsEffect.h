#ifndef QTSCRIPTSHELL_QGRAPHICSEFFECT_H
#define QTSCRIPTSHELL_QGRAPHICSEFFECT_H

#include <qgraphicseffect.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QGraphicsEffect : public QGraphicsEffect
{
public:
    QtScriptShell_QGraphicsEffect(QObject*  parent = 0);
    ~QtScriptShell_QGraphicsEffect();

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

#endif // QTSCRIPTSHELL_QGRAPHICSEFFECT_H
