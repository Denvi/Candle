#ifndef QTSCRIPTSHELL_QNETWORKCOOKIEJAR_H
#define QTSCRIPTSHELL_QNETWORKCOOKIEJAR_H

#include <qnetworkcookiejar.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QNetworkCookieJar : public QNetworkCookieJar
{
public:
    QtScriptShell_QNetworkCookieJar(QObject*  parent = 0);
    ~QtScriptShell_QNetworkCookieJar();

    void childEvent(QChildEvent*  event);
    QList<QNetworkCookie >  cookiesForUrl(const QUrl&  url) const;
    void customEvent(QEvent*  event);
    bool  deleteCookie(const QNetworkCookie&  cookie);
    bool  event(QEvent*  event);
    bool  eventFilter(QObject*  watched, QEvent*  event);
    bool  insertCookie(const QNetworkCookie&  cookie);
    bool  setCookiesFromUrl(const QList<QNetworkCookie >&  cookieList, const QUrl&  url);
    void timerEvent(QTimerEvent*  event);
    bool  updateCookie(const QNetworkCookie&  cookie);
    bool  validateCookie(const QNetworkCookie&  cookie, const QUrl&  url) const;

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QNETWORKCOOKIEJAR_H
