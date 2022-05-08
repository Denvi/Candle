#ifndef QTSCRIPTSHELL_QUNDOGROUP_H
#define QTSCRIPTSHELL_QUNDOGROUP_H

#include <qundogroup.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QUndoGroup : public QUndoGroup
{
public:
    QtScriptShell_QUndoGroup(QObject*  parent = 0);
    ~QtScriptShell_QUndoGroup();

    void childEvent(QChildEvent*  event);
    void customEvent(QEvent*  event);
    bool  event(QEvent*  event);
    bool  eventFilter(QObject*  watched, QEvent*  event);
    void timerEvent(QTimerEvent*  event);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QUNDOGROUP_H
