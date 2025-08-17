#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qaction.h>
#include <QVariant>
#include <qaction.h>
#include <qactiongroup.h>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qfont.h>
#include <qgraphicswidget.h>
#include <qicon.h>
#include <qkeysequence.h>
#include <qlist.h>
#include <qmenu.h>
#include <qobject.h>
#include <qwidget.h>

#include "qtscriptshell_QAction.h"

static const char * const qtscript_QAction_function_names[] = {
    "QAction"
    // static
    // prototype
    , "actionGroup"
    , "activate"
    , "associatedGraphicsWidgets"
    , "associatedWidgets"
    , "data"
    , "isSeparator"
    , "menu"
    , "parentWidget"
    , "setActionGroup"
    , "setData"
    , "setMenu"
    , "setSeparator"
    , "setShortcuts"
    , "shortcuts"
    , "showStatusText"
    , "toString"
};

static const char * const qtscript_QAction_function_signatures[] = {
    "QObject parent\nQIcon icon, String text, QObject parent\nString text, QObject parent"
    // static
    // prototype
    , ""
    , "ActionEvent event"
    , ""
    , ""
    , ""
    , ""
    , ""
    , ""
    , "QActionGroup group"
    , "Object var"
    , "QMenu menu"
    , "bool b"
    , "StandardKey arg__1\nList shortcuts"
    , ""
    , "QWidget widget"
""
};

static const int qtscript_QAction_function_lengths[] = {
    3
    // static
    // prototype
    , 0
    , 1
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
    , 1
    , 0
};

static QScriptValue qtscript_QAction_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QAction::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QAction*)
Q_DECLARE_METATYPE(QtScriptShell_QAction*)
Q_DECLARE_METATYPE(QAction::ActionEvent)
Q_DECLARE_METATYPE(QAction::MenuRole)
Q_DECLARE_METATYPE(QActionGroup*)
Q_DECLARE_METATYPE(QGraphicsWidget*)
Q_DECLARE_METATYPE(QList<QGraphicsWidget* >)
Q_DECLARE_METATYPE(QWidget*)
Q_DECLARE_METATYPE(QList<QWidget* >)
Q_DECLARE_METATYPE(QMenu*)
Q_DECLARE_METATYPE(QKeySequence::StandardKey)
Q_DECLARE_METATYPE(QList<QKeySequence >)

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
// QAction::ActionEvent
//

static const QAction::ActionEvent qtscript_QAction_ActionEvent_values[] = {
    QAction::Trigger
    , QAction::Hover
};

static const char * const qtscript_QAction_ActionEvent_keys[] = {
    "Trigger"
    , "Hover"
};

static QString qtscript_QAction_ActionEvent_toStringHelper(QAction::ActionEvent value)
{
    if ((value >= QAction::Trigger) && (value <= QAction::Hover))
        return qtscript_QAction_ActionEvent_keys[static_cast<int>(value)-static_cast<int>(QAction::Trigger)];
    return QString();
}

static QScriptValue qtscript_QAction_ActionEvent_toScriptValue(QScriptEngine *engine, const QAction::ActionEvent &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QAction"));
    return clazz.property(qtscript_QAction_ActionEvent_toStringHelper(value));
}

static void qtscript_QAction_ActionEvent_fromScriptValue(const QScriptValue &value, QAction::ActionEvent &out)
{
    out = qvariant_cast<QAction::ActionEvent>(value.toVariant());
}

static QScriptValue qtscript_construct_QAction_ActionEvent(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QAction::Trigger) && (arg <= QAction::Hover))
        return qScriptValueFromValue(engine,  static_cast<QAction::ActionEvent>(arg));
    return context->throwError(QString::fromLatin1("ActionEvent(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QAction_ActionEvent_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QAction::ActionEvent value = qscriptvalue_cast<QAction::ActionEvent>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QAction_ActionEvent_toString(QScriptContext *context, QScriptEngine *engine)
{
    QAction::ActionEvent value = qscriptvalue_cast<QAction::ActionEvent>(context->thisObject());
    return QScriptValue(engine, qtscript_QAction_ActionEvent_toStringHelper(value));
}

static QScriptValue qtscript_create_QAction_ActionEvent_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QAction_ActionEvent,
        qtscript_QAction_ActionEvent_valueOf, qtscript_QAction_ActionEvent_toString);
    qScriptRegisterMetaType<QAction::ActionEvent>(engine, qtscript_QAction_ActionEvent_toScriptValue,
        qtscript_QAction_ActionEvent_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 2; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QAction_ActionEvent_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QAction_ActionEvent_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QAction::MenuRole
//

static const QAction::MenuRole qtscript_QAction_MenuRole_values[] = {
    QAction::NoRole
    , QAction::TextHeuristicRole
    , QAction::ApplicationSpecificRole
    , QAction::AboutQtRole
    , QAction::AboutRole
    , QAction::PreferencesRole
    , QAction::QuitRole
};

static const char * const qtscript_QAction_MenuRole_keys[] = {
    "NoRole"
    , "TextHeuristicRole"
    , "ApplicationSpecificRole"
    , "AboutQtRole"
    , "AboutRole"
    , "PreferencesRole"
    , "QuitRole"
};

static QString qtscript_QAction_MenuRole_toStringHelper(QAction::MenuRole value)
{
    if ((value >= QAction::NoRole) && (value <= QAction::QuitRole))
        return qtscript_QAction_MenuRole_keys[static_cast<int>(value)-static_cast<int>(QAction::NoRole)];
    return QString();
}

static QScriptValue qtscript_QAction_MenuRole_toScriptValue(QScriptEngine *engine, const QAction::MenuRole &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QAction"));
    return clazz.property(qtscript_QAction_MenuRole_toStringHelper(value));
}

static void qtscript_QAction_MenuRole_fromScriptValue(const QScriptValue &value, QAction::MenuRole &out)
{
    out = qvariant_cast<QAction::MenuRole>(value.toVariant());
}

static QScriptValue qtscript_construct_QAction_MenuRole(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QAction::NoRole) && (arg <= QAction::QuitRole))
        return qScriptValueFromValue(engine,  static_cast<QAction::MenuRole>(arg));
    return context->throwError(QString::fromLatin1("MenuRole(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QAction_MenuRole_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QAction::MenuRole value = qscriptvalue_cast<QAction::MenuRole>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QAction_MenuRole_toString(QScriptContext *context, QScriptEngine *engine)
{
    QAction::MenuRole value = qscriptvalue_cast<QAction::MenuRole>(context->thisObject());
    return QScriptValue(engine, qtscript_QAction_MenuRole_toStringHelper(value));
}

static QScriptValue qtscript_create_QAction_MenuRole_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QAction_MenuRole,
        qtscript_QAction_MenuRole_valueOf, qtscript_QAction_MenuRole_toString);
    qScriptRegisterMetaType<QAction::MenuRole>(engine, qtscript_QAction_MenuRole_toScriptValue,
        qtscript_QAction_MenuRole_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 7; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QAction_MenuRole_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QAction_MenuRole_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QAction
//

static QScriptValue qtscript_QAction_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 15;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QAction* _q_self = qscriptvalue_cast<QAction*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QAction.%0(): this object is not a QAction")
            .arg(qtscript_QAction_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 0) {
        QActionGroup* _q_result = _q_self->actionGroup();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 1) {
        QAction::ActionEvent _q_arg0 = qscriptvalue_cast<QAction::ActionEvent>(context->argument(0));
        _q_self->activate(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 2:
    if (context->argumentCount() == 0) {
        QList<QGraphicsWidget* > _q_result = _q_self->associatedGraphicsWidgets();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        QList<QWidget* > _q_result = _q_self->associatedWidgets();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 0) {
        QVariant _q_result = _q_self->data();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isSeparator();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 0) {
        QMenu* _q_result = _q_self->menu();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 0) {
        QWidget* _q_result = _q_self->parentWidget();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 1) {
        QActionGroup* _q_arg0 = qscriptvalue_cast<QActionGroup*>(context->argument(0));
        _q_self->setActionGroup(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 9:
    if (context->argumentCount() == 1) {
        QVariant _q_arg0 = context->argument(0).toVariant();
        _q_self->setData(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 10:
    if (context->argumentCount() == 1) {
        QMenu* _q_arg0 = qscriptvalue_cast<QMenu*>(context->argument(0));
        _q_self->setMenu(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 11:
    if (context->argumentCount() == 1) {
        bool _q_arg0 = context->argument(0).toBoolean();
        _q_self->setSeparator(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 12:
    if (context->argumentCount() == 1) {
        if ((qMetaTypeId<QKeySequence::StandardKey>() == context->argument(0).toVariant().userType())) {
            QKeySequence::StandardKey _q_arg0 = qscriptvalue_cast<QKeySequence::StandardKey>(context->argument(0));
            _q_self->setShortcuts(_q_arg0);
            return context->engine()->undefinedValue();
        } else if (context->argument(0).isArray()) {
            QList<QKeySequence> _q_arg0;
            qScriptValueToSequence(context->argument(0), _q_arg0);
            _q_self->setShortcuts(_q_arg0);
            return context->engine()->undefinedValue();
        }
    }
    break;

    case 13:
    if (context->argumentCount() == 0) {
        QList<QKeySequence > _q_result = _q_self->shortcuts();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 14:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->showStatusText();
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 1) {
        QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
        bool _q_result = _q_self->showStatusText(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 15: {
    QString result;
    QDebug d(&result);
    d << _q_self;
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QAction_throw_ambiguity_error_helper(context,
        qtscript_QAction_function_names[_id+1],
        qtscript_QAction_function_signatures[_id+1]);
}

static QScriptValue qtscript_QAction_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QAction(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 1) {
        QObject* _q_arg0 = context->argument(0).toQObject();
        QtScriptShell_QAction* _q_cpp_result = new QtScriptShell_QAction(_q_arg0);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QAction*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 2) {
        QString _q_arg0 = context->argument(0).toString();
        QObject* _q_arg1 = context->argument(1).toQObject();
        QtScriptShell_QAction* _q_cpp_result = new QtScriptShell_QAction(_q_arg0, _q_arg1);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QAction*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 3) {
        QIcon _q_arg0 = qscriptvalue_cast<QIcon>(context->argument(0));
        QString _q_arg1 = context->argument(1).toString();
        QObject* _q_arg2 = context->argument(2).toQObject();
        QtScriptShell_QAction* _q_cpp_result = new QtScriptShell_QAction(_q_arg0, _q_arg1, _q_arg2);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QAction*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QAction_throw_ambiguity_error_helper(context,
        qtscript_QAction_function_names[_id],
        qtscript_QAction_function_signatures[_id]);
}

static QScriptValue qtscript_QAction_toScriptValue(QScriptEngine *engine, QAction* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QAction_fromScriptValue(const QScriptValue &value, QAction* &out)
{
    out = qobject_cast<QAction*>(value.toQObject());
}

QScriptValue qtscript_create_QAction_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QAction*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QAction*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QObject*>()));
    for (int i = 0; i < 16; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QAction_prototype_call, qtscript_QAction_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QAction_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QAction*>(engine, qtscript_QAction_toScriptValue, 
        qtscript_QAction_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QAction_static_call, proto, qtscript_QAction_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("ActionEvent"),
        qtscript_create_QAction_ActionEvent_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("MenuRole"),
        qtscript_create_QAction_MenuRole_class(engine, ctor));
    return ctor;
}
