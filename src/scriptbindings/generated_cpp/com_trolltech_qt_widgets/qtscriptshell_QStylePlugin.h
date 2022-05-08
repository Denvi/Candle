#ifndef QTSCRIPTSHELL_QSTYLEPLUGIN_H
#define QTSCRIPTSHELL_QSTYLEPLUGIN_H

#include <qstyleplugin.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QStylePlugin : public QStylePlugin
{
public:
    QtScriptShell_QStylePlugin(QObject*  parent = 0);
    ~QtScriptShell_QStylePlugin();

    void childEvent(QChildEvent*  event);
    QStyle*  create(const QString&  key);
    void customEvent(QEvent*  event);
    bool  event(QEvent*  event);
    bool  eventFilter(QObject*  watched, QEvent*  event);
    void timerEvent(QTimerEvent*  event);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QSTYLEPLUGIN_H
