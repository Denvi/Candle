#ifndef QTSCRIPTSHELL_QCOREAPPLICATION_H
#define QTSCRIPTSHELL_QCOREAPPLICATION_H

#include <qcoreapplication.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QCoreApplication : public QCoreApplication
{
public:
    QtScriptShell_QCoreApplication(int&  argc, char**  argv, int  arg__3 = ApplicationFlags);
    ~QtScriptShell_QCoreApplication();

    void childEvent(QChildEvent*  event);
    void customEvent(QEvent*  event);
    bool  event(QEvent*  arg__1);
    bool  eventFilter(QObject*  watched, QEvent*  event);
    bool  notify(QObject*  arg__1, QEvent*  arg__2);
    void timerEvent(QTimerEvent*  event);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QCOREAPPLICATION_H
