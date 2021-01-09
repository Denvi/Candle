#ifndef QTSCRIPTSHELL_QGESTURE_H
#define QTSCRIPTSHELL_QGESTURE_H

#include <qgesture.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QGesture : public QGesture
{
public:
    QtScriptShell_QGesture(QObject*  parent = 0);
    ~QtScriptShell_QGesture();

    void childEvent(QChildEvent*  event);
    void customEvent(QEvent*  event);
    bool  event(QEvent*  event);
    bool  eventFilter(QObject*  watched, QEvent*  event);
    void timerEvent(QTimerEvent*  event);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QGESTURE_H
