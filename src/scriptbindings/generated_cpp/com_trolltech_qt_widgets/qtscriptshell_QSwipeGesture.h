#ifndef QTSCRIPTSHELL_QSWIPEGESTURE_H
#define QTSCRIPTSHELL_QSWIPEGESTURE_H

#include <qgesture.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QSwipeGesture : public QSwipeGesture
{
public:
    QtScriptShell_QSwipeGesture(QObject*  parent = 0);
    ~QtScriptShell_QSwipeGesture();

    void childEvent(QChildEvent*  event);
    void customEvent(QEvent*  event);
    bool  event(QEvent*  event);
    bool  eventFilter(QObject*  watched, QEvent*  event);
    void timerEvent(QTimerEvent*  event);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QSWIPEGESTURE_H
