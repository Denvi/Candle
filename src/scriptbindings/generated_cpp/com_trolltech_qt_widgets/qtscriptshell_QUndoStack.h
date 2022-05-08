#ifndef QTSCRIPTSHELL_QUNDOSTACK_H
#define QTSCRIPTSHELL_QUNDOSTACK_H

#include <qundostack.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QUndoStack : public QUndoStack
{
public:
    QtScriptShell_QUndoStack(QObject*  parent = 0);
    ~QtScriptShell_QUndoStack();

    void childEvent(QChildEvent*  event);
    void customEvent(QEvent*  event);
    bool  event(QEvent*  event);
    bool  eventFilter(QObject*  watched, QEvent*  event);
    void timerEvent(QTimerEvent*  event);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QUNDOSTACK_H
