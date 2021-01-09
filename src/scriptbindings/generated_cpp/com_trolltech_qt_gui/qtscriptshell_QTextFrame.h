#ifndef QTSCRIPTSHELL_QTEXTFRAME_H
#define QTSCRIPTSHELL_QTEXTFRAME_H

#include <qtextobject.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QTextFrame : public QTextFrame
{
public:
    QtScriptShell_QTextFrame(QTextDocument*  doc);
    ~QtScriptShell_QTextFrame();

    void childEvent(QChildEvent*  event);
    void customEvent(QEvent*  event);
    bool  event(QEvent*  event);
    bool  eventFilter(QObject*  watched, QEvent*  event);
    void timerEvent(QTimerEvent*  event);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QTEXTFRAME_H
