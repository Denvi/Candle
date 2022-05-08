#ifndef QTSCRIPTSHELL_QSOUND_H
#define QTSCRIPTSHELL_QSOUND_H

#include <qsound.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QSound : public QSound
{
public:
    QtScriptShell_QSound(const QString&  filename, QObject*  parent = 0);
    ~QtScriptShell_QSound();

    void childEvent(QChildEvent*  event);
    void customEvent(QEvent*  event);
    bool  event(QEvent*  event);
    bool  eventFilter(QObject*  watched, QEvent*  event);
    void timerEvent(QTimerEvent*  event);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QSOUND_H
