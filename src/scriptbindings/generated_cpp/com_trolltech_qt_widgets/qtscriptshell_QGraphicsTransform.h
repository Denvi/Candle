#ifndef QTSCRIPTSHELL_QGRAPHICSTRANSFORM_H
#define QTSCRIPTSHELL_QGRAPHICSTRANSFORM_H

#include <qgraphicstransform.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QGraphicsTransform : public QGraphicsTransform
{
public:
    QtScriptShell_QGraphicsTransform(QObject*  parent = 0);
    ~QtScriptShell_QGraphicsTransform();

    void applyTo(QMatrix4x4*  matrix) const;
    void childEvent(QChildEvent*  event);
    void customEvent(QEvent*  event);
    bool  event(QEvent*  event);
    bool  eventFilter(QObject*  watched, QEvent*  event);
    void timerEvent(QTimerEvent*  event);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QGRAPHICSTRANSFORM_H
