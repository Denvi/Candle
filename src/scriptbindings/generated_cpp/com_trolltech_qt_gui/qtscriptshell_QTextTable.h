#ifndef QTSCRIPTSHELL_QTEXTTABLE_H
#define QTSCRIPTSHELL_QTEXTTABLE_H

#include <qtexttable.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QTextTable : public QTextTable
{
public:
    QtScriptShell_QTextTable(QTextDocument*  doc);
    ~QtScriptShell_QTextTable();

    void childEvent(QChildEvent*  event);
    void customEvent(QEvent*  event);
    bool  event(QEvent*  event);
    bool  eventFilter(QObject*  watched, QEvent*  event);
    void timerEvent(QTimerEvent*  event);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QTEXTTABLE_H
