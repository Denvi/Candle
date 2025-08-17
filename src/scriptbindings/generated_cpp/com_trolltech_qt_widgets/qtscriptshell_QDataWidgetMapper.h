#ifndef QTSCRIPTSHELL_QDATAWIDGETMAPPER_H
#define QTSCRIPTSHELL_QDATAWIDGETMAPPER_H

#include <qdatawidgetmapper.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QDataWidgetMapper : public QDataWidgetMapper
{
public:
    QtScriptShell_QDataWidgetMapper(QObject*  parent = 0);
    ~QtScriptShell_QDataWidgetMapper();

    void childEvent(QChildEvent*  event);
    void customEvent(QEvent*  event);
    bool  event(QEvent*  event);
    bool  eventFilter(QObject*  watched, QEvent*  event);
    void setCurrentIndex(int  index);
    void timerEvent(QTimerEvent*  event);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QDATAWIDGETMAPPER_H
