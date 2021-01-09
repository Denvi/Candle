#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qframe.h>
#include <QVariant>
#include <qaction.h>
#include <qbitmap.h>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qcursor.h>
#include <qevent.h>
#include <qfont.h>
#include <qframe.h>
#include <qgraphicseffect.h>
#include <qgraphicsproxywidget.h>
#include <qicon.h>
#include <qkeysequence.h>
#include <qlayout.h>
#include <qlist.h>
#include <qlocale.h>
#include <qmargins.h>
#include <qobject.h>
#include <qpaintdevice.h>
#include <qpaintengine.h>
#include <qpainter.h>
#include <qpalette.h>
#include <qpixmap.h>
#include <qpoint.h>
#include <qrect.h>
#include <qregion.h>
#include <qsize.h>
#include <qsizepolicy.h>
#include <qstyle.h>
#include <qstyleoption.h>
#include <qwidget.h>

#include "qtscriptshell_QFrame.h"

static const char * const qtscript_QFrame_function_names[] = {
    "QFrame"
    // static
    // prototype
    , "frameStyle"
    , "setFrameStyle"
    , "sizeHint"
    , "toString"
};

static const char * const qtscript_QFrame_function_signatures[] = {
    "QWidget parent, WindowFlags f"
    // static
    // prototype
    , ""
    , "int arg__1"
    , ""
""
};

static const int qtscript_QFrame_function_lengths[] = {
    2
    // static
    // prototype
    , 0
    , 1
    , 0
    , 0
};

static QScriptValue qtscript_QFrame_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QFrame::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QFrame*)
Q_DECLARE_METATYPE(QtScriptShell_QFrame*)
Q_DECLARE_METATYPE(QFrame::Shape)
Q_DECLARE_METATYPE(QWidget*)
Q_DECLARE_METATYPE(QFlags<Qt::WindowType>)

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
// QFrame::Shape
//

static const QFrame::Shape qtscript_QFrame_Shape_values[] = {
    QFrame::NoFrame
    , QFrame::Box
    , QFrame::Panel
    , QFrame::WinPanel
    , QFrame::HLine
    , QFrame::VLine
    , QFrame::StyledPanel
};

static const char * const qtscript_QFrame_Shape_keys[] = {
    "NoFrame"
    , "Box"
    , "Panel"
    , "WinPanel"
    , "HLine"
    , "VLine"
    , "StyledPanel"
};

static QString qtscript_QFrame_Shape_toStringHelper(QFrame::Shape value)
{
    if ((value >= QFrame::NoFrame) && (value <= QFrame::StyledPanel))
        return qtscript_QFrame_Shape_keys[static_cast<int>(value)-static_cast<int>(QFrame::NoFrame)];
    return QString();
}

static QScriptValue qtscript_QFrame_Shape_toScriptValue(QScriptEngine *engine, const QFrame::Shape &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QFrame"));
    return clazz.property(qtscript_QFrame_Shape_toStringHelper(value));
}

static void qtscript_QFrame_Shape_fromScriptValue(const QScriptValue &value, QFrame::Shape &out)
{
    out = qvariant_cast<QFrame::Shape>(value.toVariant());
}

static QScriptValue qtscript_construct_QFrame_Shape(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QFrame::NoFrame) && (arg <= QFrame::StyledPanel))
        return qScriptValueFromValue(engine,  static_cast<QFrame::Shape>(arg));
    return context->throwError(QString::fromLatin1("Shape(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QFrame_Shape_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QFrame::Shape value = qscriptvalue_cast<QFrame::Shape>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QFrame_Shape_toString(QScriptContext *context, QScriptEngine *engine)
{
    QFrame::Shape value = qscriptvalue_cast<QFrame::Shape>(context->thisObject());
    return QScriptValue(engine, qtscript_QFrame_Shape_toStringHelper(value));
}

static QScriptValue qtscript_create_QFrame_Shape_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QFrame_Shape,
        qtscript_QFrame_Shape_valueOf, qtscript_QFrame_Shape_toString);
    qScriptRegisterMetaType<QFrame::Shape>(engine, qtscript_QFrame_Shape_toScriptValue,
        qtscript_QFrame_Shape_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 7; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QFrame_Shape_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QFrame_Shape_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QFrame
//

static QScriptValue qtscript_QFrame_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QFrame* _q_self = qscriptvalue_cast<QFrame*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QFrame.%0(): this object is not a QFrame")
            .arg(qtscript_QFrame_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        int _q_result = _q_self->frameStyle();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->setFrameStyle(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        QSize _q_result = _q_self->sizeHint();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 3: {
    QString result = QString::fromLatin1("QFrame");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QFrame_throw_ambiguity_error_helper(context,
        qtscript_QFrame_function_names[_id+1],
        qtscript_QFrame_function_signatures[_id+1]);
}

static QScriptValue qtscript_QFrame_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QFrame(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QFrame* _q_cpp_result = new QtScriptShell_QFrame();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QFrame*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        QtScriptShell_QFrame* _q_cpp_result = new QtScriptShell_QFrame(_q_arg0);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QFrame*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 2) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        QFlags<Qt::WindowType> _q_arg1 = qscriptvalue_cast<QFlags<Qt::WindowType> >(context->argument(1));
        QtScriptShell_QFrame* _q_cpp_result = new QtScriptShell_QFrame(_q_arg0, _q_arg1);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QFrame*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QFrame_throw_ambiguity_error_helper(context,
        qtscript_QFrame_function_names[_id],
        qtscript_QFrame_function_signatures[_id]);
}

static QScriptValue qtscript_QFrame_toScriptValue(QScriptEngine *engine, QFrame* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QFrame_fromScriptValue(const QScriptValue &value, QFrame* &out)
{
    out = qobject_cast<QFrame*>(value.toQObject());
}

QScriptValue qtscript_create_QFrame_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QFrame*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QFrame*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QWidget*>()));
    for (int i = 0; i < 4; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QFrame_prototype_call, qtscript_QFrame_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QFrame_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QFrame*>(engine, qtscript_QFrame_toScriptValue, 
        qtscript_QFrame_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QFrame_static_call, proto, qtscript_QFrame_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("Shape"),
        qtscript_create_QFrame_Shape_class(engine, ctor));
    return ctor;
}
