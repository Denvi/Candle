#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qsound.h>
#include <QVariant>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qlist.h>
#include <qobject.h>

#include "qtscriptshell_QSound.h"

static const char * const qtscript_QSound_function_names[] = {
    "QSound"
    // static
    , "play"
    // prototype
    , "fileName"
    , "isFinished"
    , "loops"
    , "loopsRemaining"
    , "setLoops"
    , "toString"
};

static const char * const qtscript_QSound_function_signatures[] = {
    "String filename, QObject parent"
    // static
    , "String filename"
    // prototype
    , ""
    , ""
    , ""
    , ""
    , "int arg__1"
""
};

static const int qtscript_QSound_function_lengths[] = {
    2
    // static
    , 1
    // prototype
    , 0
    , 0
    , 0
    , 0
    , 1
    , 0
};

static QScriptValue qtscript_QSound_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QSound::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QSound*)
Q_DECLARE_METATYPE(QtScriptShell_QSound*)
Q_DECLARE_METATYPE(QSound::Loop)

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
// QSound::Loop
//

static const QSound::Loop qtscript_QSound_Loop_values[] = {
    QSound::Infinite
};

static const char * const qtscript_QSound_Loop_keys[] = {
    "Infinite"
};

static QString qtscript_QSound_Loop_toStringHelper(QSound::Loop value)
{
    if ((value >= QSound::Infinite) && (value <= QSound::Infinite))
        return qtscript_QSound_Loop_keys[static_cast<int>(value)-static_cast<int>(QSound::Infinite)];
    return QString();
}

static QScriptValue qtscript_QSound_Loop_toScriptValue(QScriptEngine *engine, const QSound::Loop &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QSound"));
    return clazz.property(qtscript_QSound_Loop_toStringHelper(value));
}

static void qtscript_QSound_Loop_fromScriptValue(const QScriptValue &value, QSound::Loop &out)
{
    out = qvariant_cast<QSound::Loop>(value.toVariant());
}

static QScriptValue qtscript_construct_QSound_Loop(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QSound::Infinite) && (arg <= QSound::Infinite))
        return qScriptValueFromValue(engine,  static_cast<QSound::Loop>(arg));
    return context->throwError(QString::fromLatin1("Loop(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QSound_Loop_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QSound::Loop value = qscriptvalue_cast<QSound::Loop>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QSound_Loop_toString(QScriptContext *context, QScriptEngine *engine)
{
    QSound::Loop value = qscriptvalue_cast<QSound::Loop>(context->thisObject());
    return QScriptValue(engine, qtscript_QSound_Loop_toStringHelper(value));
}

static QScriptValue qtscript_create_QSound_Loop_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QSound_Loop,
        qtscript_QSound_Loop_valueOf, qtscript_QSound_Loop_toString);
    qScriptRegisterMetaType<QSound::Loop>(engine, qtscript_QSound_Loop_toScriptValue,
        qtscript_QSound_Loop_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 1; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QSound_Loop_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QSound_Loop_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QSound
//

static QScriptValue qtscript_QSound_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 5;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QSound* _q_self = qscriptvalue_cast<QSound*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QSound.%0(): this object is not a QSound")
            .arg(qtscript_QSound_function_names[_id+2]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        QString _q_result = _q_self->fileName();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isFinished();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->loops();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->loopsRemaining();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->setLoops(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 5: {
    QString result = QString::fromLatin1("QSound");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QSound_throw_ambiguity_error_helper(context,
        qtscript_QSound_function_names[_id+2],
        qtscript_QSound_function_signatures[_id+2]);
}

static QScriptValue qtscript_QSound_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QSound(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        QtScriptShell_QSound* _q_cpp_result = new QtScriptShell_QSound(_q_arg0);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QSound*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        QObject* _q_arg1 = context->argument(1).toQObject();
        QtScriptShell_QSound* _q_cpp_result = new QtScriptShell_QSound(_q_arg0, _q_arg1);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QSound*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    case 1:
    if (context->argumentCount() == 1) {
        QString _q_arg0 = context->argument(0).toString();
        QSound::play(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QSound_throw_ambiguity_error_helper(context,
        qtscript_QSound_function_names[_id],
        qtscript_QSound_function_signatures[_id]);
}

static QScriptValue qtscript_QSound_toScriptValue(QScriptEngine *engine, QSound* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QSound_fromScriptValue(const QScriptValue &value, QSound* &out)
{
    out = qobject_cast<QSound*>(value.toQObject());
}

QScriptValue qtscript_create_QSound_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QSound*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QSound*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QObject*>()));
    for (int i = 0; i < 6; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QSound_prototype_call, qtscript_QSound_function_lengths[i+2]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QSound_function_names[i+2]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QSound*>(engine, qtscript_QSound_toScriptValue, 
        qtscript_QSound_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QSound_static_call, proto, qtscript_QSound_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));
    for (int i = 0; i < 1; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QSound_static_call,
            qtscript_QSound_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i+1)));
        ctor.setProperty(QString::fromLatin1(qtscript_QSound_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    ctor.setProperty(QString::fromLatin1("Loop"),
        qtscript_create_QSound_Loop_class(engine, ctor));
    return ctor;
}
