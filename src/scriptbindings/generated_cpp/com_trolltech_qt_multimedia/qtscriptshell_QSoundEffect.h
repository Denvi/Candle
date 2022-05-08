#ifndef QTSCRIPTSHELL_QSOUNDEFFECT_H
#define QTSCRIPTSHELL_QSOUNDEFFECT_H

#include <qsoundeffect.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QSoundEffect : public QSoundEffect
{
public:
    QtScriptShell_QSoundEffect(QObject*  parent = 0);
    ~QtScriptShell_QSoundEffect();

    void childEvent(QChildEvent*  event);
    void customEvent(QEvent*  event);
    bool  event(QEvent*  event);
    bool  eventFilter(QObject*  watched, QEvent*  event);
    void timerEvent(QTimerEvent*  event);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QSOUNDEFFECT_H
