#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <slider.h>
#include <QPaintEngine>
#include <QVariant>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qcursor.h>
#include <qevent.h>
#include <qfont.h>
#include <qicon.h>
#include <qkeysequence.h>
#include <qlayout.h>
#include <qlist.h>
#include <qlocale.h>
#include <qmargins.h>
#include <qobject.h>
#include <qpaintdevice.h>
#include <qpainter.h>
#include <qpalette.h>
#include <qpixmap.h>
#include <qpoint.h>
#include <qrect.h>
#include <qregion.h>
#include <qsize.h>
#include <qsizepolicy.h>
#include <qslider.h>
#include <qstyle.h>
#include <qstyleoption.h>
#include <qwidget.h>

#include "qtscriptshell_Slider.h"

static const char * const qtscript_Slider_function_names[] = {
    "Slider"
    // static
    // prototype
    , "currentValue"
    , "setCurrentValue"
    , "toString"
};

static const char * const qtscript_Slider_function_signatures[] = {
    "QWidget parent"
    // static
    // prototype
    , ""
    , "int currentValue"
""
};

static const int qtscript_Slider_function_lengths[] = {
    1
    // static
    // prototype
    , 0
    , 1
    , 0
};

static QScriptValue qtscript_Slider_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("Slider::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(Slider*)
Q_DECLARE_METATYPE(QtScriptShell_Slider*)
Q_DECLARE_METATYPE(QWidget*)
Q_DECLARE_METATYPE(QSlider*)

//
// Slider
//

static QScriptValue qtscript_Slider_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 2;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    Slider* _q_self = qscriptvalue_cast<Slider*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("Slider.%0(): this object is not a Slider")
            .arg(qtscript_Slider_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->currentValue();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->setCurrentValue(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 2: {
    QString result = QString::fromLatin1("Slider");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_Slider_throw_ambiguity_error_helper(context,
        qtscript_Slider_function_names[_id+1],
        qtscript_Slider_function_signatures[_id+1]);
}

static QScriptValue qtscript_Slider_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("Slider(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_Slider* _q_cpp_result = new QtScriptShell_Slider();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (Slider*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        QtScriptShell_Slider* _q_cpp_result = new QtScriptShell_Slider(_q_arg0);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (Slider*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_Slider_throw_ambiguity_error_helper(context,
        qtscript_Slider_function_names[_id],
        qtscript_Slider_function_signatures[_id]);
}

static QScriptValue qtscript_Slider_toScriptValue(QScriptEngine *engine, Slider* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_Slider_fromScriptValue(const QScriptValue &value, Slider* &out)
{
    out = qobject_cast<Slider*>(value.toQObject());
}

QScriptValue qtscript_create_Slider_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<Slider*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((Slider*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QSlider*>()));
    for (int i = 0; i < 3; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_Slider_prototype_call, qtscript_Slider_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_Slider_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<Slider*>(engine, qtscript_Slider_toScriptValue, 
        qtscript_Slider_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_Slider_static_call, proto, qtscript_Slider_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
