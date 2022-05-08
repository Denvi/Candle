#ifndef QTSCRIPTSHELL_QBUTTONGROUP_H
#define QTSCRIPTSHELL_QBUTTONGROUP_H

#include <qbuttongroup.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QButtonGroup : public QButtonGroup
{
public:
    QtScriptShell_QButtonGroup(QObject*  parent = 0);
    ~QtScriptShell_QButtonGroup();

    void childEvent(QChildEvent*  event);
    void customEvent(QEvent*  event);
    bool  event(QEvent*  event);
    bool  eventFilter(QObject*  watched, QEvent*  event);
    void timerEvent(QTimerEvent*  event);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QBUTTONGROUP_H
