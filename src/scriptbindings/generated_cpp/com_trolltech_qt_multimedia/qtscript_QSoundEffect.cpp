#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qsoundeffect.h>
#include <QVariant>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qlist.h>
#include <qobject.h>
#include <qsoundeffect.h>
#include <qstringlist.h>
#include <qurl.h>

#include "qtscriptshell_QSoundEffect.h"

static const char * const qtscript_QSoundEffect_function_names[] = {
    "QSoundEffect"
    // static
    , "supportedMimeTypes"
    // prototype
    , "category"
    , "isLoaded"
    , "isMuted"
    , "isPlaying"
    , "loopCount"
    , "loopsRemaining"
    , "setCategory"
    , "setLoopCount"
    , "setMuted"
    , "setSource"
    , "setVolume"
    , "source"
    , "status"
    , "volume"
    , "toString"
};

static const char * const qtscript_QSoundEffect_function_signatures[] = {
    "QObject parent"
    // static
    , ""
    // prototype
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , "String category"
    , "int loopCount"
    , "bool muted"
    , "QUrl url"
    , "qreal volume"
    , ""
    , ""
    , ""
""
};

static const int qtscript_QSoundEffect_function_lengths[] = {
    1
    // static
    , 0
    // prototype
    , 0
    , 0
    , 0
    , 0
    , 0
    , 0
    , 1
    , 1
    , 1
    , 1
    , 1
    , 0
    , 0
    , 0
    , 0
};

static QScriptValue qtscript_QSoundEffect_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QSoundEffect::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QSoundEffect*)
Q_DECLARE_METATYPE(QtScriptShell_QSoundEffect*)
Q_DECLARE_METATYPE(QSoundEffect::Status)
Q_DECLARE_METATYPE(QSoundEffect::Loop)

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
// QSoundEffect::Status
//

static const QSoundEffect::Status qtscript_QSoundEffect_Status_values[] = {
    QSoundEffect::Null
    , QSoundEffect::Loading
    , QSoundEffect::Ready
    , QSoundEffect::Error
};

static const char * const qtscript_QSoundEffect_Status_keys[] = {
    "Null"
    , "Loading"
    , "Ready"
    , "Error"
};

static QString qtscript_QSoundEffect_Status_toStringHelper(QSoundEffect::Status value)
{
    if ((value >= QSoundEffect::Null) && (value <= QSoundEffect::Error))
        return qtscript_QSoundEffect_Status_keys[static_cast<int>(value)-static_cast<int>(QSoundEffect::Null)];
    return QString();
}

static QScriptValue qtscript_QSoundEffect_Status_toScriptValue(QScriptEngine *engine, const QSoundEffect::Status &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QSoundEffect"));
    return clazz.property(qtscript_QSoundEffect_Status_toStringHelper(value));
}

static void qtscript_QSoundEffect_Status_fromScriptValue(const QScriptValue &value, QSoundEffect::Status &out)
{
    out = qvariant_cast<QSoundEffect::Status>(value.toVariant());
}

static QScriptValue qtscript_construct_QSoundEffect_Status(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QSoundEffect::Null) && (arg <= QSoundEffect::Error))
        return qScriptValueFromValue(engine,  static_cast<QSoundEffect::Status>(arg));
    return context->throwError(QString::fromLatin1("Status(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QSoundEffect_Status_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QSoundEffect::Status value = qscriptvalue_cast<QSoundEffect::Status>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QSoundEffect_Status_toString(QScriptContext *context, QScriptEngine *engine)
{
    QSoundEffect::Status value = qscriptvalue_cast<QSoundEffect::Status>(context->thisObject());
    return QScriptValue(engine, qtscript_QSoundEffect_Status_toStringHelper(value));
}

static QScriptValue qtscript_create_QSoundEffect_Status_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QSoundEffect_Status,
        qtscript_QSoundEffect_Status_valueOf, qtscript_QSoundEffect_Status_toString);
    qScriptRegisterMetaType<QSoundEffect::Status>(engine, qtscript_QSoundEffect_Status_toScriptValue,
        qtscript_QSoundEffect_Status_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 4; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QSoundEffect_Status_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QSoundEffect_Status_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QSoundEffect::Loop
//

static const QSoundEffect::Loop qtscript_QSoundEffect_Loop_values[] = {
    QSoundEffect::Infinite
};

static const char * const qtscript_QSoundEffect_Loop_keys[] = {
    "Infinite"
};

static QString qtscript_QSoundEffect_Loop_toStringHelper(QSoundEffect::Loop value)
{
    if ((value >= QSoundEffect::Infinite) && (value <= QSoundEffect::Infinite))
        return qtscript_QSoundEffect_Loop_keys[static_cast<int>(value)-static_cast<int>(QSoundEffect::Infinite)];
    return QString();
}

static QScriptValue qtscript_QSoundEffect_Loop_toScriptValue(QScriptEngine *engine, const QSoundEffect::Loop &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QSoundEffect"));
    return clazz.property(qtscript_QSoundEffect_Loop_toStringHelper(value));
}

static void qtscript_QSoundEffect_Loop_fromScriptValue(const QScriptValue &value, QSoundEffect::Loop &out)
{
    out = qvariant_cast<QSoundEffect::Loop>(value.toVariant());
}

static QScriptValue qtscript_construct_QSoundEffect_Loop(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QSoundEffect::Infinite) && (arg <= QSoundEffect::Infinite))
        return qScriptValueFromValue(engine,  static_cast<QSoundEffect::Loop>(arg));
    return context->throwError(QString::fromLatin1("Loop(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QSoundEffect_Loop_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QSoundEffect::Loop value = qscriptvalue_cast<QSoundEffect::Loop>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QSoundEffect_Loop_toString(QScriptContext *context, QScriptEngine *engine)
{
    QSoundEffect::Loop value = qscriptvalue_cast<QSoundEffect::Loop>(context->thisObject());
    return QScriptValue(engine, qtscript_QSoundEffect_Loop_toStringHelper(value));
}

static QScriptValue qtscript_create_QSoundEffect_Loop_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QSoundEffect_Loop,
        qtscript_QSoundEffect_Loop_valueOf, qtscript_QSoundEffect_Loop_toString);
    qScriptRegisterMetaType<QSoundEffect::Loop>(engine, qtscript_QSoundEffect_Loop_toScriptValue,
        qtscript_QSoundEffect_Loop_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 1; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QSoundEffect_Loop_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QSoundEffect_Loop_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QSoundEffect
//

static QScriptValue qtscript_QSoundEffect_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QSoundEffect* _q_self = qscriptvalue_cast<QSoundEffect*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QSoundEffect.%0(): this object is not a QSoundEffect")
            .arg(qtscript_QSoundEffect_function_names[_id+2]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->category();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isLoaded();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isMuted();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isPlaying();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->loopCount();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->loopsRemaining();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        _q_self->setCategory(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 7:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->setLoopCount(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 8:
    if (context->argumentCount() == 1) {
        bool _q_arg0 = context->argument(0).toBoolean();
        _q_self->setMuted(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 9:
    if (context->argumentCount() == 1) {
        QUrl _q_arg0 = qscriptvalue_cast<QUrl>(context->argument(0));
        _q_self->setSource(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 10:
    if (context->argumentCount() == 1) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        _q_self->setVolume(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 11:
    if (context->argumentCount() == 0) {
        QUrl _q_result = _q_self->source();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 12:
    if (context->argumentCount() == 0) {
        QSoundEffect::Status _q_result = _q_self->status();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 13:
    if (context->argumentCount() == 0) {
        qreal _q_result = _q_self->volume();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 14: {
    QString result = QString::fromLatin1("QSoundEffect");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QSoundEffect_throw_ambiguity_error_helper(context,
        qtscript_QSoundEffect_function_names[_id+2],
        qtscript_QSoundEffect_function_signatures[_id+2]);
}

static QScriptValue qtscript_QSoundEffect_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QSoundEffect(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QSoundEffect* _q_cpp_result = new QtScriptShell_QSoundEffect();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QSoundEffect*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QObject* _q_arg0 = context->argument(0).toQObject();
        QtScriptShell_QSoundEffect* _q_cpp_result = new QtScriptShell_QSoundEffect(_q_arg0);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QSoundEffect*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QStringList _q_result = QSoundEffect::supportedMimeTypes();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QSoundEffect_throw_ambiguity_error_helper(context,
        qtscript_QSoundEffect_function_names[_id],
        qtscript_QSoundEffect_function_signatures[_id]);
}

static QScriptValue qtscript_QSoundEffect_toScriptValue(QScriptEngine *engine, QSoundEffect* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QSoundEffect_fromScriptValue(const QScriptValue &value, QSoundEffect* &out)
{
    out = qobject_cast<QSoundEffect*>(value.toQObject());
}

QScriptValue qtscript_create_QSoundEffect_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QSoundEffect*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QSoundEffect*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QObject*>()));
    for (int i = 0; i < 15; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QSoundEffect_prototype_call, qtscript_QSoundEffect_function_lengths[i+2]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QSoundEffect_function_names[i+2]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QSoundEffect*>(engine, qtscript_QSoundEffect_toScriptValue, 
        qtscript_QSoundEffect_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QSoundEffect_static_call, proto, qtscript_QSoundEffect_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));
    for (int i = 0; i < 1; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QSoundEffect_static_call,
            qtscript_QSoundEffect_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i+1)));
        ctor.setProperty(QString::fromLatin1(qtscript_QSoundEffect_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    ctor.setProperty(QString::fromLatin1("Status"),
        qtscript_create_QSoundEffect_Status_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("Loop"),
        qtscript_create_QSoundEffect_Loop_class(engine, ctor));
    return ctor;
}
