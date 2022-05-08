#ifndef QTSCRIPTSHELL_QGLSHADER_H
#define QTSCRIPTSHELL_QGLSHADER_H

#include <qglshaderprogram.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QGLShader : public QGLShader
{
public:
    QtScriptShell_QGLShader(QGLShader::ShaderType  type, QObject*  parent = 0);
    QtScriptShell_QGLShader(QGLShader::ShaderType  type, const QGLContext*  context, QObject*  parent = 0);
    ~QtScriptShell_QGLShader();

    void childEvent(QChildEvent*  event);
    void customEvent(QEvent*  event);
    bool  event(QEvent*  event);
    bool  eventFilter(QObject*  watched, QEvent*  event);
    void timerEvent(QTimerEvent*  event);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QGLSHADER_H
