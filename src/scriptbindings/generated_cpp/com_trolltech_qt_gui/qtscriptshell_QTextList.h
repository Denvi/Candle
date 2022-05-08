#ifndef QTSCRIPTSHELL_QTEXTLIST_H
#define QTSCRIPTSHELL_QTEXTLIST_H

#include <qtextlist.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QTextList : public QTextList
{
public:
    QtScriptShell_QTextList(QTextDocument*  doc);
    ~QtScriptShell_QTextList();

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

#endif // QTSCRIPTSHELL_QTEXTLIST_H
