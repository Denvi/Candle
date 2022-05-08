#ifndef QTSCRIPTSHELL_QDOUBLEVALIDATOR_H
#define QTSCRIPTSHELL_QDOUBLEVALIDATOR_H

#include <qvalidator.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QDoubleValidator : public QDoubleValidator
{
public:
    QtScriptShell_QDoubleValidator(QObject*  parent = 0);
    QtScriptShell_QDoubleValidator(double  bottom, double  top, int  decimals, QObject*  parent = 0);
    ~QtScriptShell_QDoubleValidator();

    void childEvent(QChildEvent*  event);
    void customEvent(QEvent*  event);
    bool  event(QEvent*  event);
    bool  eventFilter(QObject*  watched, QEvent*  event);
    void fixup(QString&  arg__1) const;
    void setRange(double  bottom, double  top, int  decimals = 0);
    void timerEvent(QTimerEvent*  event);
    QValidator::State  validate(QString&  arg__1, int&  arg__2) const;

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QDOUBLEVALIDATOR_H
