#ifndef QTSCRIPTSHELL_QPICTUREFORMATPLUGIN_H
#define QTSCRIPTSHELL_QPICTUREFORMATPLUGIN_H

#include <qpictureformatplugin.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QPictureFormatPlugin : public QPictureFormatPlugin
{
public:
    QtScriptShell_QPictureFormatPlugin(QObject*  parent = 0);
    ~QtScriptShell_QPictureFormatPlugin();

    void childEvent(QChildEvent*  event);
    void customEvent(QEvent*  event);
    bool  event(QEvent*  event);
    bool  eventFilter(QObject*  watched, QEvent*  event);
    bool  installIOHandler(const QString&  format);
    bool  loadPicture(const QString&  format, const QString&  filename, QPicture*  pic);
    bool  savePicture(const QString&  format, const QString&  filename, const QPicture&  pic);
    void timerEvent(QTimerEvent*  event);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QPICTUREFORMATPLUGIN_H
