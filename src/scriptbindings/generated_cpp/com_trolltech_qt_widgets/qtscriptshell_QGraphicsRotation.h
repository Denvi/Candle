#ifndef QTSCRIPTSHELL_QGRAPHICSROTATION_H
#define QTSCRIPTSHELL_QGRAPHICSROTATION_H

#include <qgraphicstransform.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QGraphicsRotation : public QGraphicsRotation
{
public:
    QtScriptShell_QGraphicsRotation(QObject*  parent = 0);
    ~QtScriptShell_QGraphicsRotation();

    void applyTo(QMatrix4x4*  matrix) const;
    void childEvent(QChildEvent*  event);
    void customEvent(QEvent*  event);
    bool  event(QEvent*  event);
    bool  eventFilter(QObject*  watched, QEvent*  event);
    void timerEvent(QTimerEvent*  event);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QGRAPHICSROTATION_H
