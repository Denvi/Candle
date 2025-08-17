#ifndef QTSCRIPTSHELL_QSYNTAXHIGHLIGHTER_H
#define QTSCRIPTSHELL_QSYNTAXHIGHLIGHTER_H

#include <qsyntaxhighlighter.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QSyntaxHighlighter : public QSyntaxHighlighter
{
public:
    QtScriptShell_QSyntaxHighlighter(QObject*  parent);
    QtScriptShell_QSyntaxHighlighter(QTextDocument*  parent);
    ~QtScriptShell_QSyntaxHighlighter();

    void childEvent(QChildEvent*  event);
    void customEvent(QEvent*  event);
    bool  event(QEvent*  event);
    bool  eventFilter(QObject*  watched, QEvent*  event);
    void highlightBlock(const QString&  text);
    void timerEvent(QTimerEvent*  event);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QSYNTAXHIGHLIGHTER_H
