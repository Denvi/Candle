#ifndef QTSCRIPTSHELL_QOBJECT_H
#define QTSCRIPTSHELL_QOBJECT_H

#include <qobject.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QObject : public QObject
{
public:
    QtScriptShell_QObject(QObject*  parent = 0);
    ~QtScriptShell_QObject();

    void childEvent(QChildEvent*  event);
    void customEvent(QEvent*  event);
    bool  event(QEvent*  event);
    bool  eventFilter(QObject*  watched, QEvent*  event);
    void timerEvent(QTimerEvent*  event);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QOBJECT_H
