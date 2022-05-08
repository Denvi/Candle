#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <styledtoolbutton.h>
#include <QActionEvent>
#include <QPaintEngine>
#include <QVariant>
#include <qbytearray.h>
#include <qcolor.h>
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
#include <qstyle.h>
#include <qstyleoption.h>
#include <qwidget.h>
#include <styledtoolbutton.h>

#include "qtscriptshell_StyledToolButton.h"

static const char * const qtscript_StyledToolButton_function_names[] = {
    "StyledToolButton"
    // static
    // prototype
    , "isHover"
    , "toString"
};

static const char * const qtscript_StyledToolButton_function_signatures[] = {
    "QWidget parent"
    // static
    // prototype
    , ""
""
};

static const int qtscript_StyledToolButton_function_lengths[] = {
    1
    // static
    // prototype
    , 0
    , 0
};

static QScriptValue qtscript_StyledToolButton_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("StyledToolButton::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(StyledToolButton*)
Q_DECLARE_METATYPE(QtScriptShell_StyledToolButton*)
Q_DECLARE_METATYPE(QWidget*)
Q_DECLARE_METATYPE(QToolButton*)

//
// StyledToolButton
//

static QScriptValue qtscript_StyledToolButton_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 1;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    StyledToolButton* _q_self = qscriptvalue_cast<StyledToolButton*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("StyledToolButton.%0(): this object is not a StyledToolButton")
            .arg(qtscript_StyledToolButton_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isHover();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 1: {
    QString result = QString::fromLatin1("StyledToolButton");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_StyledToolButton_throw_ambiguity_error_helper(context,
        qtscript_StyledToolButton_function_names[_id+1],
        qtscript_StyledToolButton_function_signatures[_id+1]);
}

static QScriptValue qtscript_StyledToolButton_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("StyledToolButton(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_StyledToolButton* _q_cpp_result = new QtScriptShell_StyledToolButton();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (StyledToolButton*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        QtScriptShell_StyledToolButton* _q_cpp_result = new QtScriptShell_StyledToolButton(_q_arg0);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (StyledToolButton*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_StyledToolButton_throw_ambiguity_error_helper(context,
        qtscript_StyledToolButton_function_names[_id],
        qtscript_StyledToolButton_function_signatures[_id]);
}

static QScriptValue qtscript_StyledToolButton_toScriptValue(QScriptEngine *engine, StyledToolButton* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_StyledToolButton_fromScriptValue(const QScriptValue &value, StyledToolButton* &out)
{
    out = qobject_cast<StyledToolButton*>(value.toQObject());
}

QScriptValue qtscript_create_StyledToolButton_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<StyledToolButton*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((StyledToolButton*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QToolButton*>()));
    for (int i = 0; i < 2; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_StyledToolButton_prototype_call, qtscript_StyledToolButton_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_StyledToolButton_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<StyledToolButton*>(engine, qtscript_StyledToolButton_toScriptValue, 
        qtscript_StyledToolButton_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_StyledToolButton_static_call, proto, qtscript_StyledToolButton_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
