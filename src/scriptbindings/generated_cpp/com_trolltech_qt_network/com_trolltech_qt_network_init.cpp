#include <QtScript/QScriptValue>
#include <QtScript/QScriptEngine>

QScriptValue qtscript_create_QHostInfo_class(QScriptEngine *engine);
QScriptValue qtscript_create_QNetworkAddressEntry_class(QScriptEngine *engine);
QScriptValue qtscript_create_QHostAddress_class(QScriptEngine *engine);
QScriptValue qtscript_create_QSsl_class(QScriptEngine *engine);
QScriptValue qtscript_create_QNetworkRequest_class(QScriptEngine *engine);
QScriptValue qtscript_create_QNetworkProxy_class(QScriptEngine *engine);
QScriptValue qtscript_create_QNetworkCacheMetaData_class(QScriptEngine *engine);
QScriptValue qtscript_create_QNetworkProxyFactory_class(QScriptEngine *engine);
QScriptValue qtscript_create_QIPv6Address_class(QScriptEngine *engine);
QScriptValue qtscript_create_QNetworkProxyQuery_class(QScriptEngine *engine);
QScriptValue qtscript_create_QNetworkCookie_class(QScriptEngine *engine);
QScriptValue qtscript_create_QAuthenticator_class(QScriptEngine *engine);
QScriptValue qtscript_create_QNetworkInterface_class(QScriptEngine *engine);
QScriptValue qtscript_create_QAbstractNetworkCache_class(QScriptEngine *engine);
QScriptValue qtscript_create_QNetworkAccessManager_class(QScriptEngine *engine);
QScriptValue qtscript_create_QTcpServer_class(QScriptEngine *engine);
QScriptValue qtscript_create_QNetworkCookieJar_class(QScriptEngine *engine);
QScriptValue qtscript_create_QLocalServer_class(QScriptEngine *engine);
QScriptValue qtscript_create_QNetworkDiskCache_class(QScriptEngine *engine);
QScriptValue qtscript_create_QAbstractSocket_class(QScriptEngine *engine);
QScriptValue qtscript_create_QNetworkReply_class(QScriptEngine *engine);
QScriptValue qtscript_create_QLocalSocket_class(QScriptEngine *engine);
QScriptValue qtscript_create_QTcpSocket_class(QScriptEngine *engine);
QScriptValue qtscript_create_QUdpSocket_class(QScriptEngine *engine);

static const char * const qtscript_com_trolltech_qt_network_class_names[] = {
    "QHostInfo"
    , "QNetworkAddressEntry"
    , "QHostAddress"
    , "QSsl"
    , "QNetworkRequest"
    , "QNetworkProxy"
    , "QNetworkCacheMetaData"
    , "QNetworkProxyFactory"
    , "QIPv6Address"
    , "QNetworkProxyQuery"
    , "QNetworkCookie"
    , "QAuthenticator"
    , "QNetworkInterface"
    , "QAbstractNetworkCache"
    , "QNetworkAccessManager"
    , "QTcpServer"
    , "QNetworkCookieJar"
    , "QLocalServer"
    , "QNetworkDiskCache"
    , "QAbstractSocket"
    , "QNetworkReply"
    , "QLocalSocket"
    , "QTcpSocket"
    , "QUdpSocket"
};

typedef QScriptValue (*QtBindingCreator)(QScriptEngine *engine);
static const QtBindingCreator qtscript_com_trolltech_qt_network_class_functions[] = {
    qtscript_create_QHostInfo_class
    , qtscript_create_QNetworkAddressEntry_class
    , qtscript_create_QHostAddress_class
    , qtscript_create_QSsl_class
    , qtscript_create_QNetworkRequest_class
    , qtscript_create_QNetworkProxy_class
    , qtscript_create_QNetworkCacheMetaData_class
    , qtscript_create_QNetworkProxyFactory_class
    , qtscript_create_QIPv6Address_class
    , qtscript_create_QNetworkProxyQuery_class
    , qtscript_create_QNetworkCookie_class
    , qtscript_create_QAuthenticator_class
    , qtscript_create_QNetworkInterface_class
    , qtscript_create_QAbstractNetworkCache_class
    , qtscript_create_QNetworkAccessManager_class
    , qtscript_create_QTcpServer_class
    , qtscript_create_QNetworkCookieJar_class
    , qtscript_create_QLocalServer_class
    , qtscript_create_QNetworkDiskCache_class
    , qtscript_create_QAbstractSocket_class
    , qtscript_create_QNetworkReply_class
    , qtscript_create_QLocalSocket_class
    , qtscript_create_QTcpSocket_class
    , qtscript_create_QUdpSocket_class
};

void qtscript_initialize_com_trolltech_qt_network_bindings(QScriptValue &extensionObject)
{
    QScriptEngine *engine = extensionObject.engine();
    for (int i = 0; i < 24; ++i) {
        extensionObject.setProperty(qtscript_com_trolltech_qt_network_class_names[i],
            qtscript_com_trolltech_qt_network_class_functions[i](engine),
            QScriptValue::SkipInEnumeration);
    }
}
