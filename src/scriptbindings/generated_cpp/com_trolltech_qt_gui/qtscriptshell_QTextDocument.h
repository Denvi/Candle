#ifndef QTSCRIPTSHELL_QTEXTDOCUMENT_H
#define QTSCRIPTSHELL_QTEXTDOCUMENT_H

#include <qtextdocument.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QTextDocument : public QTextDocument
{
public:
    QtScriptShell_QTextDocument(QObject*  parent = 0);
    QtScriptShell_QTextDocument(const QString&  text, QObject*  parent = 0);
    ~QtScriptShell_QTextDocument();

    void childEvent(QChildEvent*  event);
    void clear();
    QTextObject*  createObject(const QTextFormat&  f);
    void customEvent(QEvent*  event);
    bool  event(QEvent*  event);
    bool  eventFilter(QObject*  watched, QEvent*  event);
    QVariant  loadResource(int  type, const QUrl&  name);
    void timerEvent(QTimerEvent*  event);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QTEXTDOCUMENT_H
