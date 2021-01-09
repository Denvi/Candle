#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qabstractsocket.h>
#include <QVariant>
#include <qabstractsocket.h>
#include <qauthenticator.h>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qhostaddress.h>
#include <qlist.h>
#include <qnetworkproxy.h>
#include <qobject.h>

#include "qtscriptshell_QAbstractSocket.h"

static const char * const qtscript_QAbstractSocket_function_names[] = {
    "QAbstractSocket"
    // static
    // prototype
    , "abort"
    , "connectToHost"
    , "disconnectFromHost"
    , "error"
    , "flush"
    , "isValid"
    , "localAddress"
    , "localPort"
    , "peerAddress"
    , "peerName"
    , "peerPort"
    , "proxy"
    , "readBufferSize"
    , "resume"
    , "setProxy"
    , "setReadBufferSize"
    , "setSocketOption"
    , "socketOption"
    , "socketType"
    , "state"
    , "waitForConnected"
    , "waitForDisconnected"
    , "toString"
};

static const char * const qtscript_QAbstractSocket_function_signatures[] = {
    "SocketType socketType, QObject parent"
    // static
    // prototype
    , ""
    , "QHostAddress address, unsigned short port, OpenMode mode\nString hostName, unsigned short port, OpenMode mode, NetworkLayerProtocol protocol"
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , "QNetworkProxy networkProxy"
    , "qint64 size"
    , "SocketOption option, Object value"
    , "SocketOption option"
    , ""
    , ""
    , "int msecs"
    , "int msecs"
""
};

static const int qtscript_QAbstractSocket_function_lengths[] = {
    2
    // static
    // prototype
    , 0
    , 4
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 1
    , 1
    , 2
    , 1
    , 0
    , 0
    , 1
    , 1
    , 0
};

static QScriptValue qtscript_QAbstractSocket_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QAbstractSocket::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QAbstractSocket*)
Q_DECLARE_METATYPE(QtScriptShell_QAbstractSocket*)
Q_DECLARE_METATYPE(QAbstractSocket::PauseMode)
Q_DECLARE_METATYPE(QAbstractSocket::SocketType)
Q_DECLARE_METATYPE(QHostAddress)
Q_DECLARE_METATYPE(QFlags<QIODevice::OpenModeFlag>)
Q_DECLARE_METATYPE(QAbstractSocket::NetworkLayerProtocol)
Q_DECLARE_METATYPE(QAbstractSocket::SocketOption)
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
// QAbstractSocket::PauseMode
//

static const QAbstractSocket::PauseMode qtscript_QAbstractSocket_PauseMode_values[] = {
    QAbstractSocket::PauseNever
    , QAbstractSocket::PauseOnSslErrors
};

static const char * const qtscript_QAbstractSocket_PauseMode_keys[] = {
    "PauseNever"
    , "PauseOnSslErrors"
};

static QString qtscript_QAbstractSocket_PauseMode_toStringHelper(QAbstractSocket::PauseMode value)
{
    if ((value >= QAbstractSocket::PauseNever) && (value <= QAbstractSocket::PauseOnSslErrors))
        return qtscript_QAbstractSocket_PauseMode_keys[static_cast<int>(value)-static_cast<int>(QAbstractSocket::PauseNever)];
    return QString();
}

static QScriptValue qtscript_QAbstractSocket_PauseMode_toScriptValue(QScriptEngine *engine, const QAbstractSocket::PauseMode &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QAbstractSocket"));
    return clazz.property(qtscript_QAbstractSocket_PauseMode_toStringHelper(value));
}

static void qtscript_QAbstractSocket_PauseMode_fromScriptValue(const QScriptValue &value, QAbstractSocket::PauseMode &out)
{
    out = qvariant_cast<QAbstractSocket::PauseMode>(value.toVariant());
}

static QScriptValue qtscript_construct_QAbstractSocket_PauseMode(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QAbstractSocket::PauseNever) && (arg <= QAbstractSocket::PauseOnSslErrors))
        return qScriptValueFromValue(engine,  static_cast<QAbstractSocket::PauseMode>(arg));
    return context->throwError(QString::fromLatin1("PauseMode(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QAbstractSocket_PauseMode_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QAbstractSocket::PauseMode value = qscriptvalue_cast<QAbstractSocket::PauseMode>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QAbstractSocket_PauseMode_toString(QScriptContext *context, QScriptEngine *engine)
{
    QAbstractSocket::PauseMode value = qscriptvalue_cast<QAbstractSocket::PauseMode>(context->thisObject());
    return QScriptValue(engine, qtscript_QAbstractSocket_PauseMode_toStringHelper(value));
}

static QScriptValue qtscript_create_QAbstractSocket_PauseMode_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QAbstractSocket_PauseMode,
        qtscript_QAbstractSocket_PauseMode_valueOf, qtscript_QAbstractSocket_PauseMode_toString);
    qScriptRegisterMetaType<QAbstractSocket::PauseMode>(engine, qtscript_QAbstractSocket_PauseMode_toScriptValue,
        qtscript_QAbstractSocket_PauseMode_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 2; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QAbstractSocket_PauseMode_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QAbstractSocket_PauseMode_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QAbstractSocket::SocketType
//

static const QAbstractSocket::SocketType qtscript_QAbstractSocket_SocketType_values[] = {
    QAbstractSocket::UnknownSocketType
    , QAbstractSocket::TcpSocket
    , QAbstractSocket::UdpSocket
};

static const char * const qtscript_QAbstractSocket_SocketType_keys[] = {
    "UnknownSocketType"
    , "TcpSocket"
    , "UdpSocket"
};

static QString qtscript_QAbstractSocket_SocketType_toStringHelper(QAbstractSocket::SocketType value)
{
    if ((value >= QAbstractSocket::UnknownSocketType) && (value <= QAbstractSocket::UdpSocket))
        return qtscript_QAbstractSocket_SocketType_keys[static_cast<int>(value)-static_cast<int>(QAbstractSocket::UnknownSocketType)];
    return QString();
}

static QScriptValue qtscript_QAbstractSocket_SocketType_toScriptValue(QScriptEngine *engine, const QAbstractSocket::SocketType &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QAbstractSocket"));
    return clazz.property(qtscript_QAbstractSocket_SocketType_toStringHelper(value));
}

static void qtscript_QAbstractSocket_SocketType_fromScriptValue(const QScriptValue &value, QAbstractSocket::SocketType &out)
{
    out = qvariant_cast<QAbstractSocket::SocketType>(value.toVariant());
}

static QScriptValue qtscript_construct_QAbstractSocket_SocketType(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QAbstractSocket::UnknownSocketType) && (arg <= QAbstractSocket::UdpSocket))
        return qScriptValueFromValue(engine,  static_cast<QAbstractSocket::SocketType>(arg));
    return context->throwError(QString::fromLatin1("SocketType(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QAbstractSocket_SocketType_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QAbstractSocket::SocketType value = qscriptvalue_cast<QAbstractSocket::SocketType>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QAbstractSocket_SocketType_toString(QScriptContext *context, QScriptEngine *engine)
{
    QAbstractSocket::SocketType value = qscriptvalue_cast<QAbstractSocket::SocketType>(context->thisObject());
    return QScriptValue(engine, qtscript_QAbstractSocket_SocketType_toStringHelper(value));
}

static QScriptValue qtscript_create_QAbstractSocket_SocketType_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QAbstractSocket_SocketType,
        qtscript_QAbstractSocket_SocketType_valueOf, qtscript_QAbstractSocket_SocketType_toString);
    qScriptRegisterMetaType<QAbstractSocket::SocketType>(engine, qtscript_QAbstractSocket_SocketType_toScriptValue,
        qtscript_QAbstractSocket_SocketType_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 3; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QAbstractSocket_SocketType_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QAbstractSocket_SocketType_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QAbstractSocket
//

static QScriptValue qtscript_QAbstractSocket_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 22;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QAbstractSocket* _q_self = qscriptvalue_cast<QAbstractSocket*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QAbstractSocket.%0(): this object is not a QAbstractSocket")
            .arg(qtscript_QAbstractSocket_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        _q_self->abort();
        return context->engine()->undefinedValue();
    }
    break;

    case 1:
    if (context->argumentCount() == 2) {
        if ((qMetaTypeId<QHostAddress>() == context->argument(0).toVariant().userType())
            && context->argument(1).isNumber()) {
            QHostAddress _q_arg0 = qscriptvalue_cast<QHostAddress>(context->argument(0));
            unsigned short _q_arg1 = qscriptvalue_cast<unsigned short>(context->argument(1));
            _q_self->connectToHost(_q_arg0, _q_arg1);
            return context->engine()->undefinedValue();
        } else if (context->argument(0).isString()
            && context->argument(1).isNumber()) {
            QString _q_arg0 = context->argument(0).toString();
            unsigned short _q_arg1 = qscriptvalue_cast<unsigned short>(context->argument(1));
            _q_self->connectToHost(_q_arg0, _q_arg1);
            return context->engine()->undefinedValue();
        }
    }
    if (context->argumentCount() == 3) {
        if ((qMetaTypeId<QHostAddress>() == context->argument(0).toVariant().userType())
            && context->argument(1).isNumber()
            && (qMetaTypeId<QFlags<QIODevice::OpenModeFlag> >() == context->argument(2).toVariant().userType())) {
            QHostAddress _q_arg0 = qscriptvalue_cast<QHostAddress>(context->argument(0));
            unsigned short _q_arg1 = qscriptvalue_cast<unsigned short>(context->argument(1));
            QFlags<QIODevice::OpenModeFlag> _q_arg2 = qscriptvalue_cast<QFlags<QIODevice::OpenModeFlag> >(context->argument(2));
            _q_self->connectToHost(_q_arg0, _q_arg1, _q_arg2);
            return context->engine()->undefinedValue();
        } else if (context->argument(0).isString()
            && context->argument(1).isNumber()
            && (qMetaTypeId<QFlags<QIODevice::OpenModeFlag> >() == context->argument(2).toVariant().userType())) {
            QString _q_arg0 = context->argument(0).toString();
            unsigned short _q_arg1 = qscriptvalue_cast<unsigned short>(context->argument(1));
            QFlags<QIODevice::OpenModeFlag> _q_arg2 = qscriptvalue_cast<QFlags<QIODevice::OpenModeFlag> >(context->argument(2));
            _q_self->connectToHost(_q_arg0, _q_arg1, _q_arg2);
            return context->engine()->undefinedValue();
        }
    }
    if (context->argumentCount() == 4) {
        QString _q_arg0 = context->argument(0).toString();
        unsigned short _q_arg1 = qscriptvalue_cast<unsigned short>(context->argument(1));
        QFlags<QIODevice::OpenModeFlag> _q_arg2 = qscriptvalue_cast<QFlags<QIODevice::OpenModeFlag> >(context->argument(2));
        QAbstractSocket::NetworkLayerProtocol _q_arg3 = qscriptvalue_cast<QAbstractSocket::NetworkLayerProtocol>(context->argument(3));
        _q_self->connectToHost(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return context->engine()->undefinedValue();
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        _q_self->disconnectFromHost();
        return context->engine()->undefinedValue();
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        QAbstractSocket::SocketError _q_result = _q_self->error();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->flush();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isValid();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 0) {
        QHostAddress _q_result = _q_self->localAddress();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 0) {
        unsigned short _q_result = _q_self->localPort();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 0) {
        QHostAddress _q_result = _q_self->peerAddress();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->peerName();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 10:
    if (context->argumentCount() == 0) {
        unsigned short _q_result = _q_self->peerPort();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 11:
    if (context->argumentCount() == 0) {
        QNetworkProxy _q_result = _q_self->proxy();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 12:
    if (context->argumentCount() == 0) {
        qint64 _q_result = _q_self->readBufferSize();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 13:
    if (context->argumentCount() == 0) {
        _q_self->resume();
        return context->engine()->undefinedValue();
    }
    break;

    case 14:
    if (context->argumentCount() == 1) {
        QNetworkProxy _q_arg0 = qscriptvalue_cast<QNetworkProxy>(context->argument(0));
        _q_self->setProxy(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 15:
    if (context->argumentCount() == 1) {
        qint64 _q_arg0 = qscriptvalue_cast<qint64>(context->argument(0));
        _q_self->setReadBufferSize(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 16:
    if (context->argumentCount() == 2) {
        QAbstractSocket::SocketOption _q_arg0 = qscriptvalue_cast<QAbstractSocket::SocketOption>(context->argument(0));
        QVariant _q_arg1 = context->argument(1).toVariant();
        _q_self->setSocketOption(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 17:
    if (context->argumentCount() == 1) {
        QAbstractSocket::SocketOption _q_arg0 = qscriptvalue_cast<QAbstractSocket::SocketOption>(context->argument(0));
        QVariant _q_result = _q_self->socketOption(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 18:
    if (context->argumentCount() == 0) {
        QAbstractSocket::SocketType _q_result = _q_self->socketType();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 19:
    if (context->argumentCount() == 0) {
        QAbstractSocket::SocketState _q_result = _q_self->state();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 20:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->waitForConnected();
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        bool _q_result = _q_self->waitForConnected(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 21:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->waitForDisconnected();
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        bool _q_result = _q_self->waitForDisconnected(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 22: {
    QString result = QString::fromLatin1("QAbstractSocket");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QAbstractSocket_throw_ambiguity_error_helper(context,
        qtscript_QAbstractSocket_function_names[_id+1],
        qtscript_QAbstractSocket_function_signatures[_id+1]);
}

static QScriptValue qtscript_QAbstractSocket_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QAbstractSocket(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 2) {
        QAbstractSocket::SocketType _q_arg0 = qscriptvalue_cast<QAbstractSocket::SocketType>(context->argument(0));
        QObject* _q_arg1 = context->argument(1).toQObject();
        QtScriptShell_QAbstractSocket* _q_cpp_result = new QtScriptShell_QAbstractSocket(_q_arg0, _q_arg1);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QAbstractSocket*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QAbstractSocket_throw_ambiguity_error_helper(context,
        qtscript_QAbstractSocket_function_names[_id],
        qtscript_QAbstractSocket_function_signatures[_id]);
}

static QScriptValue qtscript_QAbstractSocket_toScriptValue(QScriptEngine *engine, QAbstractSocket* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QAbstractSocket_fromScriptValue(const QScriptValue &value, QAbstractSocket* &out)
{
    out = qobject_cast<QAbstractSocket*>(value.toQObject());
}

QScriptValue qtscript_create_QAbstractSocket_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QAbstractSocket*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QAbstractSocket*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QIODevice*>()));
    for (int i = 0; i < 23; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QAbstractSocket_prototype_call, qtscript_QAbstractSocket_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QAbstractSocket_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QAbstractSocket*>(engine, qtscript_QAbstractSocket_toScriptValue, 
        qtscript_QAbstractSocket_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QAbstractSocket_static_call, proto, qtscript_QAbstractSocket_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("PauseMode"),
        qtscript_create_QAbstractSocket_PauseMode_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("SocketType"),
        qtscript_create_QAbstractSocket_SocketType_class(engine, ctor));
    return ctor;
}
