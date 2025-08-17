#ifndef QTSCRIPTSHELL_QSETTINGS_H
#define QTSCRIPTSHELL_QSETTINGS_H

#include <qsettings.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QSettings : public QSettings
{
public:
    QtScriptShell_QSettings(QObject*  parent = 0);
    QtScriptShell_QSettings(QSettings::Format  format, QSettings::Scope  scope, const QString&  organization, const QString&  application = QString(), QObject*  parent = 0);
    QtScriptShell_QSettings(QSettings::Scope  scope, const QString&  organization, const QString&  application = QString(), QObject*  parent = 0);
    QtScriptShell_QSettings(const QString&  fileName, QSettings::Format  format, QObject*  parent = 0);
    QtScriptShell_QSettings(const QString&  organization, const QString&  application = QString(), QObject*  parent = 0);
    ~QtScriptShell_QSettings();

    void childEvent(QChildEvent*  event);
    void customEvent(QEvent*  event);
    bool  event(QEvent*  event);
    bool  eventFilter(QObject*  watched, QEvent*  event);
    void timerEvent(QTimerEvent*  event);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QSETTINGS_H
