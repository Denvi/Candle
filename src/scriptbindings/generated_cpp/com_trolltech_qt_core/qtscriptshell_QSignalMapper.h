#ifndef QTSCRIPTSHELL_QSIGNALMAPPER_H
#define QTSCRIPTSHELL_QSIGNALMAPPER_H

#include <qsignalmapper.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QSignalMapper : public QSignalMapper
{
public:
    QtScriptShell_QSignalMapper(QObject*  parent = 0);
    ~QtScriptShell_QSignalMapper();

    void childEvent(QChildEvent*  event);
    void customEvent(QEvent*  event);
    bool  event(QEvent*  event);
    bool  eventFilter(QObject*  watched, QEvent*  event);
    void timerEvent(QTimerEvent*  event);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QSIGNALMAPPER_H
