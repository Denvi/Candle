#ifndef QTSCRIPTSHELL_QPANGESTURE_H
#define QTSCRIPTSHELL_QPANGESTURE_H

#include <qgesture.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QPanGesture : public QPanGesture
{
public:
    QtScriptShell_QPanGesture(QObject*  parent = 0);
    ~QtScriptShell_QPanGesture();

    void childEvent(QChildEvent*  event);
    void customEvent(QEvent*  event);
    bool  event(QEvent*  event);
    bool  eventFilter(QObject*  watched, QEvent*  event);
    void timerEvent(QTimerEvent*  event);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QPANGESTURE_H
