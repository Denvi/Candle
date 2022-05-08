#ifndef QTSCRIPTSHELL_QDRAG_H
#define QTSCRIPTSHELL_QDRAG_H

#include <qdrag.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QDrag : public QDrag
{
public:
    QtScriptShell_QDrag(QObject*  dragSource);
    ~QtScriptShell_QDrag();

    void childEvent(QChildEvent*  event);
    void customEvent(QEvent*  event);
    bool  event(QEvent*  event);
    bool  eventFilter(QObject*  watched, QEvent*  event);
    void timerEvent(QTimerEvent*  event);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QDRAG_H
