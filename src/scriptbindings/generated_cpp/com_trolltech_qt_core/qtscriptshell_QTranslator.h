#ifndef QTSCRIPTSHELL_QTRANSLATOR_H
#define QTSCRIPTSHELL_QTRANSLATOR_H

#include <qtranslator.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QTranslator : public QTranslator
{
public:
    QtScriptShell_QTranslator(QObject*  parent = 0);
    ~QtScriptShell_QTranslator();

    void childEvent(QChildEvent*  event);
    void customEvent(QEvent*  event);
    bool  event(QEvent*  event);
    bool  eventFilter(QObject*  watched, QEvent*  event);
    bool  isEmpty() const;
    void timerEvent(QTimerEvent*  event);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QTRANSLATOR_H
