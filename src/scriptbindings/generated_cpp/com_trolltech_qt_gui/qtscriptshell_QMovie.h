#ifndef QTSCRIPTSHELL_QMOVIE_H
#define QTSCRIPTSHELL_QMOVIE_H

#include <qmovie.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QMovie : public QMovie
{
public:
    QtScriptShell_QMovie(QIODevice*  device, const QByteArray&  format = QByteArray(), QObject*  parent = 0);
    QtScriptShell_QMovie(QObject*  parent = 0);
    QtScriptShell_QMovie(const QString&  fileName, const QByteArray&  format = QByteArray(), QObject*  parent = 0);
    ~QtScriptShell_QMovie();

    void childEvent(QChildEvent*  event);
    void customEvent(QEvent*  event);
    bool  event(QEvent*  event);
    bool  eventFilter(QObject*  watched, QEvent*  event);
    void timerEvent(QTimerEvent*  event);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QMOVIE_H
