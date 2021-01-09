#ifndef QTSCRIPTSHELL_QACTION_H
#define QTSCRIPTSHELL_QACTION_H

#include <qaction.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QAction : public QAction
{
public:
    QtScriptShell_QAction(QObject*  parent);
    QtScriptShell_QAction(const QIcon&  icon, const QString&  text, QObject*  parent);
    QtScriptShell_QAction(const QString&  text, QObject*  parent);
    ~QtScriptShell_QAction();

    void childEvent(QChildEvent*  event);
    void customEvent(QEvent*  event);
    bool  event(QEvent*  arg__1);
    bool  eventFilter(QObject*  watched, QEvent*  event);
    void timerEvent(QTimerEvent*  event);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QACTION_H
