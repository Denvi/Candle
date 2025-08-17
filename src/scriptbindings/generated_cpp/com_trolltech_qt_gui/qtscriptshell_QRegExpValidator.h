#ifndef QTSCRIPTSHELL_QREGEXPVALIDATOR_H
#define QTSCRIPTSHELL_QREGEXPVALIDATOR_H

#include <qvalidator.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QRegExpValidator : public QRegExpValidator
{
public:
    QtScriptShell_QRegExpValidator(QObject*  parent = 0);
    QtScriptShell_QRegExpValidator(const QRegExp&  rx, QObject*  parent = 0);
    ~QtScriptShell_QRegExpValidator();

    void childEvent(QChildEvent*  event);
    void customEvent(QEvent*  event);
    bool  event(QEvent*  event);
    bool  eventFilter(QObject*  watched, QEvent*  event);
    void fixup(QString&  arg__1) const;
    void timerEvent(QTimerEvent*  event);
    QValidator::State  validate(QString&  input, int&  pos) const;

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QREGEXPVALIDATOR_H
