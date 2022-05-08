#ifndef QTSCRIPTSHELL_QCOMPLETER_H
#define QTSCRIPTSHELL_QCOMPLETER_H

#include <qcompleter.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QCompleter : public QCompleter
{
public:
    QtScriptShell_QCompleter(QAbstractItemModel*  model, QObject*  parent = 0);
    QtScriptShell_QCompleter(QObject*  parent = 0);
    QtScriptShell_QCompleter(const QStringList&  completions, QObject*  parent = 0);
    ~QtScriptShell_QCompleter();

    void childEvent(QChildEvent*  event);
    void customEvent(QEvent*  event);
    bool  event(QEvent*  arg__1);
    bool  eventFilter(QObject*  o, QEvent*  e);
    QString  pathFromIndex(const QModelIndex&  index) const;
    QStringList  splitPath(const QString&  path) const;
    void timerEvent(QTimerEvent*  event);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QCOMPLETER_H
