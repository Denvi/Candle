#ifndef QTSCRIPTSHELL_QFILESYSTEMWATCHER_H
#define QTSCRIPTSHELL_QFILESYSTEMWATCHER_H

#include <qfilesystemwatcher.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QFileSystemWatcher : public QFileSystemWatcher
{
public:
    QtScriptShell_QFileSystemWatcher(QObject*  parent = 0);
    QtScriptShell_QFileSystemWatcher(const QStringList&  paths, QObject*  parent = 0);
    ~QtScriptShell_QFileSystemWatcher();

    void childEvent(QChildEvent*  event);
    void customEvent(QEvent*  event);
    bool  event(QEvent*  event);
    bool  eventFilter(QObject*  watched, QEvent*  event);
    void timerEvent(QTimerEvent*  event);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QFILESYSTEMWATCHER_H
