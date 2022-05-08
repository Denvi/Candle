#ifndef QTSCRIPTSHELL_QTEXTOBJECT_H
#define QTSCRIPTSHELL_QTEXTOBJECT_H

#include <qtextobject.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QTextObject : public QTextObject
{
public:
    QtScriptShell_QTextObject(QTextDocument*  doc);
    ~QtScriptShell_QTextObject();

    void childEvent(QChildEvent*  event);
    void customEvent(QEvent*  event);
    bool  event(QEvent*  event);
    bool  eventFilter(QObject*  watched, QEvent*  event);
    void timerEvent(QTimerEvent*  event);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QTEXTOBJECT_H
