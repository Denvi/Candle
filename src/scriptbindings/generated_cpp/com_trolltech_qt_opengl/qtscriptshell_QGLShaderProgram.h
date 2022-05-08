#ifndef QTSCRIPTSHELL_QGLSHADERPROGRAM_H
#define QTSCRIPTSHELL_QGLSHADERPROGRAM_H

#include <qglshaderprogram.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QGLShaderProgram : public QGLShaderProgram
{
public:
    QtScriptShell_QGLShaderProgram(QObject*  parent = 0);
    QtScriptShell_QGLShaderProgram(const QGLContext*  context, QObject*  parent = 0);
    ~QtScriptShell_QGLShaderProgram();

    void childEvent(QChildEvent*  event);
    void customEvent(QEvent*  event);
    bool  event(QEvent*  event);
    bool  eventFilter(QObject*  watched, QEvent*  event);
    bool  link();
    void timerEvent(QTimerEvent*  event);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QGLSHADERPROGRAM_H
