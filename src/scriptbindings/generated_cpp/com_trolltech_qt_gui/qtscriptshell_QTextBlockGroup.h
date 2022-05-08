#ifndef QTSCRIPTSHELL_QTEXTBLOCKGROUP_H
#define QTSCRIPTSHELL_QTEXTBLOCKGROUP_H

#include <qtextobject.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QTextBlockGroup : public QTextBlockGroup
{
public:
    QtScriptShell_QTextBlockGroup(QTextDocument*  doc);
    ~QtScriptShell_QTextBlockGroup();

    void blockFormatChanged(const QTextBlock&  block);
    void blockInserted(const QTextBlock&  block);
    void blockRemoved(const QTextBlock&  block);
    void childEvent(QChildEvent*  event);
    void customEvent(QEvent*  event);
    bool  event(QEvent*  event);
    bool  eventFilter(QObject*  watched, QEvent*  event);
    void timerEvent(QTimerEvent*  event);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QTEXTBLOCKGROUP_H
