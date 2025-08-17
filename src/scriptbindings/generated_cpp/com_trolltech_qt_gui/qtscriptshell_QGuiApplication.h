#ifndef QTSCRIPTSHELL_QGUIAPPLICATION_H
#define QTSCRIPTSHELL_QGUIAPPLICATION_H

#include <qguiapplication.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QGuiApplication : public QGuiApplication
{
public:
    QtScriptShell_QGuiApplication(int&  argc, char**  argv, int  arg__3 = ApplicationFlags);
    ~QtScriptShell_QGuiApplication();

    void childEvent(QChildEvent*  event);
    void customEvent(QEvent*  event);
    bool  event(QEvent*  arg__1);
    bool  eventFilter(QObject*  watched, QEvent*  event);
    bool  notify(QObject*  arg__1, QEvent*  arg__2);
    void timerEvent(QTimerEvent*  event);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QGUIAPPLICATION_H
