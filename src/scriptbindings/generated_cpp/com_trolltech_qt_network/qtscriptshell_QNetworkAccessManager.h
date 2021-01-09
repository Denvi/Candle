#ifndef QTSCRIPTSHELL_QNETWORKACCESSMANAGER_H
#define QTSCRIPTSHELL_QNETWORKACCESSMANAGER_H

#include <qnetworkaccessmanager.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QNetworkAccessManager : public QNetworkAccessManager
{
public:
    QtScriptShell_QNetworkAccessManager(QObject*  parent = 0);
    ~QtScriptShell_QNetworkAccessManager();

    void childEvent(QChildEvent*  event);
    QNetworkReply*  createRequest(QNetworkAccessManager::Operation  op, const QNetworkRequest&  request, QIODevice*  outgoingData = 0);
    void customEvent(QEvent*  event);
    bool  event(QEvent*  event);
    bool  eventFilter(QObject*  watched, QEvent*  event);
    void timerEvent(QTimerEvent*  event);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QNETWORKACCESSMANAGER_H
