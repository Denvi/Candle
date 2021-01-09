#ifndef QTSCRIPTSHELL_QAPPLICATION_H
#define QTSCRIPTSHELL_QAPPLICATION_H

#include <qapplication.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QApplication : public QApplication
{
public:
    QtScriptShell_QApplication(int&  argc, char**  argv, int  arg__3 = ApplicationFlags);
    ~QtScriptShell_QApplication();

    void childEvent(QChildEvent*  event);
    void customEvent(QEvent*  event);
    bool  event(QEvent*  arg__1);
    bool  eventFilter(QObject*  watched, QEvent*  event);
    bool  notify(QObject*  arg__1, QEvent*  arg__2);
    void timerEvent(QTimerEvent*  event);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QAPPLICATION_H
