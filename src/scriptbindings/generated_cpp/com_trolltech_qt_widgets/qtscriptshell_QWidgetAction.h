#ifndef QTSCRIPTSHELL_QWIDGETACTION_H
#define QTSCRIPTSHELL_QWIDGETACTION_H

#include <qwidgetaction.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QWidgetAction : public QWidgetAction
{
public:
    QtScriptShell_QWidgetAction(QObject*  parent);
    ~QtScriptShell_QWidgetAction();

    void childEvent(QChildEvent*  event);
    QWidget*  createWidget(QWidget*  parent);
    void customEvent(QEvent*  event);
    void deleteWidget(QWidget*  widget);
    bool  event(QEvent*  arg__1);
    bool  eventFilter(QObject*  arg__1, QEvent*  arg__2);
    void timerEvent(QTimerEvent*  event);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QWIDGETACTION_H
