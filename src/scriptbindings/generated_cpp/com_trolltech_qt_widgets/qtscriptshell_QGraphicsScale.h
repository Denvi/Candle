#ifndef QTSCRIPTSHELL_QGRAPHICSSCALE_H
#define QTSCRIPTSHELL_QGRAPHICSSCALE_H

#include <qgraphicstransform.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QGraphicsScale : public QGraphicsScale
{
public:
    QtScriptShell_QGraphicsScale(QObject*  parent = 0);
    ~QtScriptShell_QGraphicsScale();

    void applyTo(QMatrix4x4*  matrix) const;
    void childEvent(QChildEvent*  event);
    void customEvent(QEvent*  event);
    bool  event(QEvent*  event);
    bool  eventFilter(QObject*  watched, QEvent*  event);
    void timerEvent(QTimerEvent*  event);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QGRAPHICSSCALE_H
