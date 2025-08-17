#include "qtscriptshell_QNetworkCookieJar.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qlist.h>
#include <qnetworkcookie.h>
#include <qnetworkcookiejar.h>
#include <qobject.h>
#include <qurl.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)

Q_DECLARE_METATYPE(QChildEvent*)
Q_DECLARE_METATYPE(QList<QNetworkCookie >)
Q_DECLARE_METATYPE(QEvent*)
Q_DECLARE_METATYPE(QTimerEvent*)

QtScriptShell_QNetworkCookieJar::QtScriptShell_QNetworkCookieJar(QObject*  parent)
    : QNetworkCookieJar(parent) {}

QtScriptShell_QNetworkCookieJar::~QtScriptShell_QNetworkCookieJar() {}

void QtScriptShell_QNetworkCookieJar::childEvent(QChildEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("childEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("childEvent") & QScriptValue::QObjectMember)) {
        QNetworkCookieJar::childEvent(event);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, event));
    }
}

QList<QNetworkCookie >  QtScriptShell_QNetworkCookieJar::cookiesForUrl(const QUrl&  url) const
{
    QScriptValue _q_function = __qtscript_self.property("cookiesForUrl");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("cookiesForUrl") & QScriptValue::QObjectMember)) {
        return QNetworkCookieJar::cookiesForUrl(url);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QList<QNetworkCookie > >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, url)));
    }
}

void QtScriptShell_QNetworkCookieJar::customEvent(QEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("customEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("customEvent") & QScriptValue::QObjectMember)) {
        QNetworkCookieJar::customEvent(event);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, event));
    }
}

bool  QtScriptShell_QNetworkCookieJar::deleteCookie(const QNetworkCookie&  cookie)
{
    QScriptValue _q_function = __qtscript_self.property("deleteCookie");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("deleteCookie") & QScriptValue::QObjectMember)) {
        return QNetworkCookieJar::deleteCookie(cookie);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, cookie)));
    }
}

bool  QtScriptShell_QNetworkCookieJar::event(QEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("event");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("event") & QScriptValue::QObjectMember)) {
        return QNetworkCookieJar::event(event);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, event)));
    }
}

bool  QtScriptShell_QNetworkCookieJar::eventFilter(QObject*  watched, QEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("eventFilter");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("eventFilter") & QScriptValue::QObjectMember)) {
        return QNetworkCookieJar::eventFilter(watched, event);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, watched)
            << qScriptValueFromValue(_q_engine, event)));
    }
}

bool  QtScriptShell_QNetworkCookieJar::insertCookie(const QNetworkCookie&  cookie)
{
    QScriptValue _q_function = __qtscript_self.property("insertCookie");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("insertCookie") & QScriptValue::QObjectMember)) {
        return QNetworkCookieJar::insertCookie(cookie);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, cookie)));
    }
}

bool  QtScriptShell_QNetworkCookieJar::setCookiesFromUrl(const QList<QNetworkCookie >&  cookieList, const QUrl&  url)
{
    QScriptValue _q_function = __qtscript_self.property("setCookiesFromUrl");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setCookiesFromUrl") & QScriptValue::QObjectMember)) {
        return QNetworkCookieJar::setCookiesFromUrl(cookieList, url);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, cookieList)
            << qScriptValueFromValue(_q_engine, url)));
    }
}

void QtScriptShell_QNetworkCookieJar::timerEvent(QTimerEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("timerEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("timerEvent") & QScriptValue::QObjectMember)) {
        QNetworkCookieJar::timerEvent(event);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, event));
    }
}

bool  QtScriptShell_QNetworkCookieJar::updateCookie(const QNetworkCookie&  cookie)
{
    QScriptValue _q_function = __qtscript_self.property("updateCookie");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("updateCookie") & QScriptValue::QObjectMember)) {
        return QNetworkCookieJar::updateCookie(cookie);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, cookie)));
    }
}

bool  QtScriptShell_QNetworkCookieJar::validateCookie(const QNetworkCookie&  cookie, const QUrl&  url) const
{
    QScriptValue _q_function = __qtscript_self.property("validateCookie");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("validateCookie") & QScriptValue::QObjectMember)) {
        return QNetworkCookieJar::validateCookie(cookie, url);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, cookie)
            << qScriptValueFromValue(_q_engine, url)));
    }
}

