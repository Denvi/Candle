#ifndef QTSCRIPTSHELL_QUILOADER_H
#define QTSCRIPTSHELL_QUILOADER_H

#include <quiloader.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QUiLoader : public QUiLoader
{
public:
    QtScriptShell_QUiLoader(QObject*  parent = 0);
    ~QtScriptShell_QUiLoader();

    void childEvent(QChildEvent*  event);
    QAction*  createAction(QObject*  parent = 0, const QString&  name = QString());
    QActionGroup*  createActionGroup(QObject*  parent = 0, const QString&  name = QString());
    QLayout*  createLayout(const QString&  className, QObject*  parent = 0, const QString&  name = QString());
    QWidget*  createWidget(const QString&  className, QWidget*  parent = 0, const QString&  name = QString());
    void customEvent(QEvent*  event);
    bool  event(QEvent*  event);
    bool  eventFilter(QObject*  watched, QEvent*  event);
    void timerEvent(QTimerEvent*  event);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QUILOADER_H
