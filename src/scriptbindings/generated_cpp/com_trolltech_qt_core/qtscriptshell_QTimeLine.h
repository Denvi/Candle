#ifndef QTSCRIPTSHELL_QTIMELINE_H
#define QTSCRIPTSHELL_QTIMELINE_H

#include <qtimeline.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QTimeLine : public QTimeLine
{
public:
    QtScriptShell_QTimeLine(int  duration = 1000, QObject*  parent = 0);
    ~QtScriptShell_QTimeLine();

    void childEvent(QChildEvent*  event);
    void customEvent(QEvent*  event);
    bool  event(QEvent*  event);
    bool  eventFilter(QObject*  watched, QEvent*  event);
    void timerEvent(QTimerEvent*  event);
    qreal  valueForTime(int  msec) const;

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QTIMELINE_H
