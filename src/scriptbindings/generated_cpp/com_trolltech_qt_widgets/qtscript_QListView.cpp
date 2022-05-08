#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qlistview.h>
#include <QVariant>
#include <qabstractitemdelegate.h>
#include <qabstractitemmodel.h>
#include <qaction.h>
#include <qbitmap.h>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qcursor.h>
#include <qevent.h>
#include <qfont.h>
#include <qgraphicseffect.h>
#include <qgraphicsproxywidget.h>
#include <qicon.h>
#include <qitemselectionmodel.h>
#include <qkeysequence.h>
#include <qlayout.h>
#include <qlist.h>
#include <qlistview.h>
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
#include <qscrollbar.h>
#include <qsize.h>
#include <qsizepolicy.h>
#include <qstyle.h>
#include <qstyleoption.h>
#include <qvector.h>
#include <qwidget.h>

#include "qtscriptshell_QListView.h"

static const char * const qtscript_QListView_function_names[] = {
    "QListView"
    // static
    // prototype
    , "clearPropertyFlags"
    , "isRowHidden"
    , "setRowHidden"
    , "toString"
};

static const char * const qtscript_QListView_function_signatures[] = {
    "QWidget parent"
    // static
    // prototype
    , ""
    , "int row"
    , "int row, bool hide"
""
};

static const int qtscript_QListView_function_lengths[] = {
    1
    // static
    // prototype
    , 0
    , 1
    , 2
    , 0
};

static QScriptValue qtscript_QListView_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QListView::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QListView*)
Q_DECLARE_METATYPE(QtScriptShell_QListView*)
Q_DECLARE_METATYPE(QListView::Movement)
Q_DECLARE_METATYPE(QWidget*)
Q_DECLARE_METATYPE(QAbstractItemView*)

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
// QListView::Movement
//

static const QListView::Movement qtscript_QListView_Movement_values[] = {
    QListView::Static
    , QListView::Free
    , QListView::Snap
};

static const char * const qtscript_QListView_Movement_keys[] = {
    "Static"
    , "Free"
    , "Snap"
};

static QString qtscript_QListView_Movement_toStringHelper(QListView::Movement value)
{
    if ((value >= QListView::Static) && (value <= QListView::Snap))
        return qtscript_QListView_Movement_keys[static_cast<int>(value)-static_cast<int>(QListView::Static)];
    return QString();
}

static QScriptValue qtscript_QListView_Movement_toScriptValue(QScriptEngine *engine, const QListView::Movement &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QListView"));
    return clazz.property(qtscript_QListView_Movement_toStringHelper(value));
}

static void qtscript_QListView_Movement_fromScriptValue(const QScriptValue &value, QListView::Movement &out)
{
    out = qvariant_cast<QListView::Movement>(value.toVariant());
}

static QScriptValue qtscript_construct_QListView_Movement(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QListView::Static) && (arg <= QListView::Snap))
        return qScriptValueFromValue(engine,  static_cast<QListView::Movement>(arg));
    return context->throwError(QString::fromLatin1("Movement(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QListView_Movement_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QListView::Movement value = qscriptvalue_cast<QListView::Movement>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QListView_Movement_toString(QScriptContext *context, QScriptEngine *engine)
{
    QListView::Movement value = qscriptvalue_cast<QListView::Movement>(context->thisObject());
    return QScriptValue(engine, qtscript_QListView_Movement_toStringHelper(value));
}

static QScriptValue qtscript_create_QListView_Movement_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QListView_Movement,
        qtscript_QListView_Movement_valueOf, qtscript_QListView_Movement_toString);
    qScriptRegisterMetaType<QListView::Movement>(engine, qtscript_QListView_Movement_toScriptValue,
        qtscript_QListView_Movement_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 3; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QListView_Movement_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QListView_Movement_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QListView
//

static QScriptValue qtscript_QListView_prototype_call(QScriptContext *context, QScriptEngine *)
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
    QListView* _q_self = qscriptvalue_cast<QListView*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QListView.%0(): this object is not a QListView")
            .arg(qtscript_QListView_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        _q_self->clearPropertyFlags();
        return context->engine()->undefinedValue();
    }
    break;

    case 1:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        bool _q_result = _q_self->isRowHidden(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        bool _q_arg1 = context->argument(1).toBoolean();
        _q_self->setRowHidden(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 3: {
    QString result = QString::fromLatin1("QListView");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QListView_throw_ambiguity_error_helper(context,
        qtscript_QListView_function_names[_id+1],
        qtscript_QListView_function_signatures[_id+1]);
}

static QScriptValue qtscript_QListView_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QListView(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QListView* _q_cpp_result = new QtScriptShell_QListView();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QListView*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        QtScriptShell_QListView* _q_cpp_result = new QtScriptShell_QListView(_q_arg0);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QListView*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QListView_throw_ambiguity_error_helper(context,
        qtscript_QListView_function_names[_id],
        qtscript_QListView_function_signatures[_id]);
}

static QScriptValue qtscript_QListView_toScriptValue(QScriptEngine *engine, QListView* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QListView_fromScriptValue(const QScriptValue &value, QListView* &out)
{
    out = qobject_cast<QListView*>(value.toQObject());
}

QScriptValue qtscript_create_QListView_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QListView*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QListView*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QAbstractItemView*>()));
    for (int i = 0; i < 4; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QListView_prototype_call, qtscript_QListView_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QListView_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QListView*>(engine, qtscript_QListView_toScriptValue, 
        qtscript_QListView_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QListView_static_call, proto, qtscript_QListView_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("Movement"),
        qtscript_create_QListView_Movement_class(engine, ctor));
    return ctor;
}
