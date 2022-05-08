#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qabstractanimation.h>
#include <QVariant>
#include <qabstractanimation.h>
#include <qanimationgroup.h>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qlist.h>
#include <qobject.h>

#include "qtscriptshell_QAbstractAnimation.h"

static const char * const qtscript_QAbstractAnimation_function_names[] = {
    "QAbstractAnimation"
    // static
    // prototype
    , "currentLoopTime"
    , "group"
    , "totalDuration"
    , "toString"
};

static const char * const qtscript_QAbstractAnimation_function_signatures[] = {
    "QObject parent"
    // static
    // prototype
    , ""
    , ""
    , ""
""
};

static const int qtscript_QAbstractAnimation_function_lengths[] = {
    1
    // static
    // prototype
    , 0
    , 0
    , 0
    , 0
};

static QScriptValue qtscript_QAbstractAnimation_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QAbstractAnimation::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QAbstractAnimation*)
Q_DECLARE_METATYPE(QtScriptShell_QAbstractAnimation*)
Q_DECLARE_METATYPE(QAbstractAnimation::Direction)
Q_DECLARE_METATYPE(QAnimationGroup*)

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
// QAbstractAnimation::Direction
//

static const QAbstractAnimation::Direction qtscript_QAbstractAnimation_Direction_values[] = {
    QAbstractAnimation::Forward
    , QAbstractAnimation::Backward
};

static const char * const qtscript_QAbstractAnimation_Direction_keys[] = {
    "Forward"
    , "Backward"
};

static QString qtscript_QAbstractAnimation_Direction_toStringHelper(QAbstractAnimation::Direction value)
{
    if ((value >= QAbstractAnimation::Forward) && (value <= QAbstractAnimation::Backward))
        return qtscript_QAbstractAnimation_Direction_keys[static_cast<int>(value)-static_cast<int>(QAbstractAnimation::Forward)];
    return QString();
}

static QScriptValue qtscript_QAbstractAnimation_Direction_toScriptValue(QScriptEngine *engine, const QAbstractAnimation::Direction &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QAbstractAnimation"));
    return clazz.property(qtscript_QAbstractAnimation_Direction_toStringHelper(value));
}

static void qtscript_QAbstractAnimation_Direction_fromScriptValue(const QScriptValue &value, QAbstractAnimation::Direction &out)
{
    out = qvariant_cast<QAbstractAnimation::Direction>(value.toVariant());
}

static QScriptValue qtscript_construct_QAbstractAnimation_Direction(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QAbstractAnimation::Forward) && (arg <= QAbstractAnimation::Backward))
        return qScriptValueFromValue(engine,  static_cast<QAbstractAnimation::Direction>(arg));
    return context->throwError(QString::fromLatin1("Direction(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QAbstractAnimation_Direction_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QAbstractAnimation::Direction value = qscriptvalue_cast<QAbstractAnimation::Direction>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QAbstractAnimation_Direction_toString(QScriptContext *context, QScriptEngine *engine)
{
    QAbstractAnimation::Direction value = qscriptvalue_cast<QAbstractAnimation::Direction>(context->thisObject());
    return QScriptValue(engine, qtscript_QAbstractAnimation_Direction_toStringHelper(value));
}

static QScriptValue qtscript_create_QAbstractAnimation_Direction_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QAbstractAnimation_Direction,
        qtscript_QAbstractAnimation_Direction_valueOf, qtscript_QAbstractAnimation_Direction_toString);
    qScriptRegisterMetaType<QAbstractAnimation::Direction>(engine, qtscript_QAbstractAnimation_Direction_toScriptValue,
        qtscript_QAbstractAnimation_Direction_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 2; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QAbstractAnimation_Direction_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QAbstractAnimation_Direction_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QAbstractAnimation
//

static QScriptValue qtscript_QAbstractAnimation_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 3;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QAbstractAnimation* _q_self = qscriptvalue_cast<QAbstractAnimation*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QAbstractAnimation.%0(): this object is not a QAbstractAnimation")
            .arg(qtscript_QAbstractAnimation_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->currentLoopTime();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 0) {
        QAnimationGroup* _q_result = _q_self->group();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->totalDuration();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 3: {
    QString result = QString::fromLatin1("QAbstractAnimation");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QAbstractAnimation_throw_ambiguity_error_helper(context,
        qtscript_QAbstractAnimation_function_names[_id+1],
        qtscript_QAbstractAnimation_function_signatures[_id+1]);
}

static QScriptValue qtscript_QAbstractAnimation_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QAbstractAnimation(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QAbstractAnimation* _q_cpp_result = new QtScriptShell_QAbstractAnimation();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QAbstractAnimation*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QObject* _q_arg0 = context->argument(0).toQObject();
        QtScriptShell_QAbstractAnimation* _q_cpp_result = new QtScriptShell_QAbstractAnimation(_q_arg0);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QAbstractAnimation*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QAbstractAnimation_throw_ambiguity_error_helper(context,
        qtscript_QAbstractAnimation_function_names[_id],
        qtscript_QAbstractAnimation_function_signatures[_id]);
}

static QScriptValue qtscript_QAbstractAnimation_toScriptValue(QScriptEngine *engine, QAbstractAnimation* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QAbstractAnimation_fromScriptValue(const QScriptValue &value, QAbstractAnimation* &out)
{
    out = qobject_cast<QAbstractAnimation*>(value.toQObject());
}

QScriptValue qtscript_create_QAbstractAnimation_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QAbstractAnimation*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QAbstractAnimation*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QObject*>()));
    for (int i = 0; i < 4; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QAbstractAnimation_prototype_call, qtscript_QAbstractAnimation_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QAbstractAnimation_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QAbstractAnimation*>(engine, qtscript_QAbstractAnimation_toScriptValue, 
        qtscript_QAbstractAnimation_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QAbstractAnimation_static_call, proto, qtscript_QAbstractAnimation_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("Direction"),
        qtscript_create_QAbstractAnimation_Direction_class(engine, ctor));
    return ctor;
}
