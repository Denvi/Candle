#ifndef QTSCRIPTSHELL_QGRAPHICSOPACITYEFFECT_H
#define QTSCRIPTSHELL_QGRAPHICSOPACITYEFFECT_H

#include <qgraphicseffect.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QGraphicsOpacityEffect : public QGraphicsOpacityEffect
{
public:
    QtScriptShell_QGraphicsOpacityEffect(QObject*  parent = 0);
    ~QtScriptShell_QGraphicsOpacityEffect();

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

#endif // QTSCRIPTSHELL_QGRAPHICSOPACITYEFFECT_H
