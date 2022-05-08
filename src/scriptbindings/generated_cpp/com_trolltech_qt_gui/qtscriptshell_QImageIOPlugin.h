#ifndef QTSCRIPTSHELL_QIMAGEIOPLUGIN_H
#define QTSCRIPTSHELL_QIMAGEIOPLUGIN_H

#include <qimageiohandler.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QImageIOPlugin : public QImageIOPlugin
{
public:
    QtScriptShell_QImageIOPlugin(QObject*  parent = 0);
    ~QtScriptShell_QImageIOPlugin();

    QImageIOPlugin::Capabilities  capabilities(QIODevice*  device, const QByteArray&  format) const;
    void childEvent(QChildEvent*  event);
    QImageIOHandler*  create(QIODevice*  device, const QByteArray&  format = QByteArray()) const;
    void customEvent(QEvent*  event);
    bool  event(QEvent*  event);
    bool  eventFilter(QObject*  watched, QEvent*  event);
    void timerEvent(QTimerEvent*  event);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QIMAGEIOPLUGIN_H
