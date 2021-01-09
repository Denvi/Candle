#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qnetworkreply.h>
#include <QVariant>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qiodevice.h>
#include <qlist.h>
#include <qnetworkaccessmanager.h>
#include <qnetworkrequest.h>
#include <qobject.h>
#include <qurl.h>

#include "qtscriptshell_QNetworkReply.h"

static const char * const qtscript_QNetworkReply_function_names[] = {
    "QNetworkReply"
    // static
    // prototype
    , "attribute"
    , "error"
    , "hasRawHeader"
    , "header"
    , "isFinished"
    , "isRunning"
    , "manager"
    , "operation"
    , "rawHeader"
    , "rawHeaderList"
    , "readBufferSize"
    , "request"
    , "setReadBufferSize"
    , "url"
    , "toString"
};

static const char * const qtscript_QNetworkReply_function_signatures[] = {
    ""
    // static
    // prototype
    , "Attribute code"
    , ""
    , "QByteArray headerName"
    , "KnownHeaders header"
    , ""
    , ""
    , ""
    , ""
    , "QByteArray headerName"
    , ""
    , ""
    , ""
    , "qint64 size"
    , ""
""
};

static const int qtscript_QNetworkReply_function_lengths[] = {
    0
    // static
    // prototype
    , 1
    , 0
    , 1
    , 1
    , 0
    , 0
    , 0
    , 0
    , 1
    , 0
    , 0
    , 0
    , 1
    , 0
    , 0
};

static QScriptValue qtscript_QNetworkReply_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QNetworkReply::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QNetworkReply*)
Q_DECLARE_METATYPE(QtScriptShell_QNetworkReply*)
Q_DECLARE_METATYPE(QNetworkRequest::Attribute)
Q_DECLARE_METATYPE(QNetworkRequest::KnownHeaders)
Q_DECLARE_METATYPE(QNetworkAccessManager*)
Q_DECLARE_METATYPE(QNetworkAccessManager::Operation)
Q_DECLARE_METATYPE(QIODevice*)

static QScriptValue qtscript_create_enum_class_helper(
    QScriptEngine *engine,
    QScriptEngine::FunctionSignature construct,
    QScriptEngine::FunctionSignature valueOf,
    QScriptEngine::FunctionSignature toString)
{
    QScriptValue proto = engine->newObject();
    proto.setProperty(QString::fromLatin1("valueOf"),
        engine->newFunction(valueOf), QScriptValue::SkipInEnumeration);
    proto.setProperty(QString::fromLatin1("toString"),
        engine->newFunction(toString), QScriptValue::SkipInEnumeration);
    return engine->newFunction(construct, proto, 1);
}

//
// QNetworkReply::NetworkError
//

static const QNetworkReply::NetworkError qtscript_QNetworkReply_NetworkError_values[] = {
    QNetworkReply::NoError
    , QNetworkReply::ConnectionRefusedError
    , QNetworkReply::RemoteHostClosedError
    , QNetworkReply::HostNotFoundError
    , QNetworkReply::TimeoutError
    , QNetworkReply::OperationCanceledError
    , QNetworkReply::SslHandshakeFailedError
    , QNetworkReply::TemporaryNetworkFailureError
    , QNetworkReply::NetworkSessionFailedError
    , QNetworkReply::BackgroundRequestNotAllowedError
    , QNetworkReply::TooManyRedirectsError
    , QNetworkReply::InsecureRedirectError
    , QNetworkReply::UnknownNetworkError
    , QNetworkReply::ProxyConnectionRefusedError
    , QNetworkReply::ProxyConnectionClosedError
    , QNetworkReply::ProxyNotFoundError
    , QNetworkReply::ProxyTimeoutError
    , QNetworkReply::ProxyAuthenticationRequiredError
    , QNetworkReply::UnknownProxyError
    , QNetworkReply::ContentAccessDenied
    , QNetworkReply::ContentOperationNotPermittedError
    , QNetworkReply::ContentNotFoundError
    , QNetworkReply::AuthenticationRequiredError
    , QNetworkReply::ContentReSendError
    , QNetworkReply::ContentConflictError
    , QNetworkReply::ContentGoneError
    , QNetworkReply::UnknownContentError
    , QNetworkReply::ProtocolUnknownError
    , QNetworkReply::ProtocolInvalidOperationError
    , QNetworkReply::ProtocolFailure
    , QNetworkReply::InternalServerError
    , QNetworkReply::OperationNotImplementedError
    , QNetworkReply::ServiceUnavailableError
    , QNetworkReply::UnknownServerError
};

static const char * const qtscript_QNetworkReply_NetworkError_keys[] = {
    "NoError"
    , "ConnectionRefusedError"
    , "RemoteHostClosedError"
    , "HostNotFoundError"
    , "TimeoutError"
    , "OperationCanceledError"
    , "SslHandshakeFailedError"
    , "TemporaryNetworkFailureError"
    , "NetworkSessionFailedError"
    , "BackgroundRequestNotAllowedError"
    , "TooManyRedirectsError"
    , "InsecureRedirectError"
    , "UnknownNetworkError"
    , "ProxyConnectionRefusedError"
    , "ProxyConnectionClosedError"
    , "ProxyNotFoundError"
    , "ProxyTimeoutError"
    , "ProxyAuthenticationRequiredError"
    , "UnknownProxyError"
    , "ContentAccessDenied"
    , "ContentOperationNotPermittedError"
    , "ContentNotFoundError"
    , "AuthenticationRequiredError"
    , "ContentReSendError"
    , "ContentConflictError"
    , "ContentGoneError"
    , "UnknownContentError"
    , "ProtocolUnknownError"
    , "ProtocolInvalidOperationError"
    , "ProtocolFailure"
    , "InternalServerError"
    , "OperationNotImplementedError"
    , "ServiceUnavailableError"
    , "UnknownServerError"
};

static QString qtscript_QNetworkReply_NetworkError_toStringHelper(QNetworkReply::NetworkError value)
{
    for (int i = 0; i < 34; ++i) {
        if (qtscript_QNetworkReply_NetworkError_values[i] == value)
            return QString::fromLatin1(qtscript_QNetworkReply_NetworkError_keys[i]);
    }
    return QString();
}

static QScriptValue qtscript_QNetworkReply_NetworkError_toScriptValue(QScriptEngine *engine, const QNetworkReply::NetworkError &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QNetworkReply"));
    return clazz.property(qtscript_QNetworkReply_NetworkError_toStringHelper(value));
}

static void qtscript_QNetworkReply_NetworkError_fromScriptValue(const QScriptValue &value, QNetworkReply::NetworkError &out)
{
    out = qvariant_cast<QNetworkReply::NetworkError>(value.toVariant());
}

static QScriptValue qtscript_construct_QNetworkReply_NetworkError(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    for (int i = 0; i < 34; ++i) {
        if (qtscript_QNetworkReply_NetworkError_values[i] == arg)
            return qScriptValueFromValue(engine,  static_cast<QNetworkReply::NetworkError>(arg));
    }
    return context->throwError(QString::fromLatin1("NetworkError(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QNetworkReply_NetworkError_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QNetworkReply::NetworkError value = qscriptvalue_cast<QNetworkReply::NetworkError>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QNetworkReply_NetworkError_toString(QScriptContext *context, QScriptEngine *engine)
{
    QNetworkReply::NetworkError value = qscriptvalue_cast<QNetworkReply::NetworkError>(context->thisObject());
    return QScriptValue(engine, qtscript_QNetworkReply_NetworkError_toStringHelper(value));
}

static QScriptValue qtscript_create_QNetworkReply_NetworkError_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QNetworkReply_NetworkError,
        qtscript_QNetworkReply_NetworkError_valueOf, qtscript_QNetworkReply_NetworkError_toString);
    qScriptRegisterMetaType<QNetworkReply::NetworkError>(engine, qtscript_QNetworkReply_NetworkError_toScriptValue,
        qtscript_QNetworkReply_NetworkError_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 34; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QNetworkReply_NetworkError_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QNetworkReply_NetworkError_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QNetworkReply
//

static QScriptValue qtscript_QNetworkReply_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 14;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QNetworkReply* _q_self = qscriptvalue_cast<QNetworkReply*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QNetworkReply.%0(): this object is not a QNetworkReply")
            .arg(qtscript_QNetworkReply_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 1) {
        QNetworkRequest::Attribute _q_arg0 = qscriptvalue_cast<QNetworkRequest::Attribute>(context->argument(0));
        QVariant _q_result = _q_self->attribute(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QNetworkReply::NetworkError _q_result = _q_self->error();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 1) {
        QByteArray _q_arg0 = qscriptvalue_cast<QByteArray>(context->argument(0));
        bool _q_result = _q_self->hasRawHeader(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 1) {
        QNetworkRequest::KnownHeaders _q_arg0 = qscriptvalue_cast<QNetworkRequest::KnownHeaders>(context->argument(0));
        QVariant _q_result = _q_self->header(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isFinished();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isRunning();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 0) {
        QNetworkAccessManager* _q_result = _q_self->manager();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 0) {
        QNetworkAccessManager::Operation _q_result = _q_self->operation();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 1) {
        QByteArray _q_arg0 = qscriptvalue_cast<QByteArray>(context->argument(0));
        QByteArray _q_result = _q_self->rawHeader(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 0) {
        QList<QByteArray > _q_result = _q_self->rawHeaderList();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 10:
    if (context->argumentCount() == 0) {
        qint64 _q_result = _q_self->readBufferSize();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 11:
    if (context->argumentCount() == 0) {
        QNetworkRequest _q_result = _q_self->request();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 12:
    if (context->argumentCount() == 1) {
        qint64 _q_arg0 = qscriptvalue_cast<qint64>(context->argument(0));
        _q_self->setReadBufferSize(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 13:
    if (context->argumentCount() == 0) {
        QUrl _q_result = _q_self->url();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 14: {
    QString result = QString::fromLatin1("QNetworkReply");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QNetworkReply_throw_ambiguity_error_helper(context,
        qtscript_QNetworkReply_function_names[_id+1],
        qtscript_QNetworkReply_function_signatures[_id+1]);
}

static QScriptValue qtscript_QNetworkReply_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    return context->throwError(QScriptContext::TypeError,
        QString::fromLatin1("QNetworkReply cannot be constructed"));
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QNetworkReply_throw_ambiguity_error_helper(context,
        qtscript_QNetworkReply_function_names[_id],
        qtscript_QNetworkReply_function_signatures[_id]);
}

static QScriptValue qtscript_QNetworkReply_toScriptValue(QScriptEngine *engine, QNetworkReply* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QNetworkReply_fromScriptValue(const QScriptValue &value, QNetworkReply* &out)
{
    out = qobject_cast<QNetworkReply*>(value.toQObject());
}

QScriptValue qtscript_create_QNetworkReply_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QNetworkReply*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QNetworkReply*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QIODevice*>()));
    for (int i = 0; i < 15; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QNetworkReply_prototype_call, qtscript_QNetworkReply_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QNetworkReply_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QNetworkReply*>(engine, qtscript_QNetworkReply_toScriptValue, 
        qtscript_QNetworkReply_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QNetworkReply_static_call, proto, qtscript_QNetworkReply_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("NetworkError"),
        qtscript_create_QNetworkReply_NetworkError_class(engine, ctor));
    return ctor;
}
