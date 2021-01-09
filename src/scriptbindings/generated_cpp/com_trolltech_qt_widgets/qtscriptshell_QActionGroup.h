#ifndef QTSCRIPTSHELL_QACTIONGROUP_H
#define QTSCRIPTSHELL_QACTIONGROUP_H

#include <qactiongroup.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QActionGroup : public QActionGroup
{
public:
    QtScriptShell_QActionGroup(QObject*  parent);
    ~QtScriptShell_QActionGroup();

    void childEvent(QChildEvent*  event);
    void customEvent(QEvent*  event);
    bool  event(QEvent*  event);
    bool  eventFilter(QObject*  watched, QEvent*  event);
    void timerEvent(QTimerEvent*  event);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QACTIONGROUP_H
