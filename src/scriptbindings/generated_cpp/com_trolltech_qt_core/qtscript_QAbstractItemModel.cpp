#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qabstractitemmodel.h>
#include <QVariant>
#include <qabstractitemmodel.h>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qlist.h>
#include <qmimedata.h>
#include <qobject.h>
#include <qsize.h>
#include <qstringlist.h>
#include <qvector.h>

#include "qtscriptshell_QAbstractItemModel.h"

static const char * const qtscript_QAbstractItemModel_function_names[] = {
    "QAbstractItemModel"
    // static
    // prototype
    , "buddy"
    , "canDropMimeData"
    , "dropMimeData"
    , "insertColumn"
    , "insertColumns"
    , "insertRow"
    , "insertRows"
    , "itemData"
    , "mimeData"
    , "mimeTypes"
    , "moveColumn"
    , "moveColumns"
    , "moveRow"
    , "moveRows"
    , "removeColumn"
    , "removeColumns"
    , "removeRow"
    , "removeRows"
    , "roleNames"
    , "setHeaderData"
    , "setItemData"
    , "sort"
    , "span"
    , "supportedDragActions"
    , "supportedDropActions"
    , "toString"
};

static const char * const qtscript_QAbstractItemModel_function_signatures[] = {
    "QObject parent"
    // static
    // prototype
    , "QModelIndex index"
    , "QMimeData data, DropAction action, int row, int column, QModelIndex parent"
    , "QMimeData data, DropAction action, int row, int column, QModelIndex parent"
    , "int column, QModelIndex parent"
    , "int column, int count, QModelIndex parent"
    , "int row, QModelIndex parent"
    , "int row, int count, QModelIndex parent"
    , "QModelIndex index"
    , "List indexes"
    , ""
    , "QModelIndex sourceParent, int sourceColumn, QModelIndex destinationParent, int destinationChild"
    , "QModelIndex sourceParent, int sourceColumn, int count, QModelIndex destinationParent, int destinationChild"
    , "QModelIndex sourceParent, int sourceRow, QModelIndex destinationParent, int destinationChild"
    , "QModelIndex sourceParent, int sourceRow, int count, QModelIndex destinationParent, int destinationChild"
    , "int column, QModelIndex parent"
    , "int column, int count, QModelIndex parent"
    , "int row, QModelIndex parent"
    , "int row, int count, QModelIndex parent"
    , ""
    , "int section, Orientation orientation, Object value, int role"
    , "QModelIndex index, SortedMap roles"
    , "int column, SortOrder order"
    , "QModelIndex index"
    , ""
    , ""
""
};

static const int qtscript_QAbstractItemModel_function_lengths[] = {
    1
    // static
    // prototype
    , 1
    , 5
    , 5
    , 2
    , 3
    , 2
    , 3
    , 1
    , 1
    , 0
    , 4
    , 5
    , 4
    , 5
    , 2
    , 3
    , 2
    , 3
    , 0
    , 4
    , 2
    , 2
    , 1
    , 0
    , 0
    , 0
};

static QScriptValue qtscript_QAbstractItemModel_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QAbstractItemModel::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QAbstractItemModel*)
Q_DECLARE_METATYPE(QtScriptShell_QAbstractItemModel*)
Q_DECLARE_METATYPE(const QMimeData*)
Q_DECLARE_METATYPE(Qt::DropAction)
template <> \
struct QMetaTypeId< QMap<int,QVariant > > \
{ \
    enum { Defined = 1 }; \
    static int qt_metatype_id() \
    { \
        static QBasicAtomicInt metatype_id = Q_BASIC_ATOMIC_INITIALIZER(0); \
        if (!metatype_id.load()) \
            metatype_id.store(qRegisterMetaType< QMap<int,QVariant > >("QMap<int,QVariant >")); \
        return metatype_id.load(); \
    } \
};
Q_DECLARE_METATYPE(QMimeData*)
template <> \
struct QMetaTypeId< QHash<int,QByteArray > > \
{ \
    enum { Defined = 1 }; \
    static int qt_metatype_id() \
    { \
        static QBasicAtomicInt metatype_id = Q_BASIC_ATOMIC_INITIALIZER(0); \
        if (!metatype_id.load()) \
            metatype_id.store(qRegisterMetaType< QHash<int,QByteArray > >("QHash<int,QByteArray >")); \
        return metatype_id.load(); \
    } \
};
Q_DECLARE_METATYPE(Qt::Orientation)
Q_DECLARE_METATYPE(Qt::SortOrder)
Q_DECLARE_METATYPE(QFlags<Qt::DropAction>)

//
// QAbstractItemModel
//

static QScriptValue qtscript_QAbstractItemModel_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 25;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QAbstractItemModel* _q_self = qscriptvalue_cast<QAbstractItemModel*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QAbstractItemModel.%0(): this object is not a QAbstractItemModel")
            .arg(qtscript_QAbstractItemModel_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 1) {
        QModelIndex _q_arg0 = qscriptvalue_cast<QModelIndex>(context->argument(0));
        QModelIndex _q_result = _q_self->buddy(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 1:
    if (context->argumentCount() == 5) {
        const QMimeData* _q_arg0 = qscriptvalue_cast<const QMimeData*>(context->argument(0));
        Qt::DropAction _q_arg1 = qscriptvalue_cast<Qt::DropAction>(context->argument(1));
        int _q_arg2 = context->argument(2).toInt32();
        int _q_arg3 = context->argument(3).toInt32();
        QModelIndex _q_arg4 = qscriptvalue_cast<QModelIndex>(context->argument(4));
        bool _q_result = _q_self->canDropMimeData(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 2:
    if (context->argumentCount() == 5) {
        const QMimeData* _q_arg0 = qscriptvalue_cast<const QMimeData*>(context->argument(0));
        Qt::DropAction _q_arg1 = qscriptvalue_cast<Qt::DropAction>(context->argument(1));
        int _q_arg2 = context->argument(2).toInt32();
        int _q_arg3 = context->argument(3).toInt32();
        QModelIndex _q_arg4 = qscriptvalue_cast<QModelIndex>(context->argument(4));
        bool _q_result = _q_self->dropMimeData(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 3:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        bool _q_result = _q_self->insertColumn(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        QModelIndex _q_arg1 = qscriptvalue_cast<QModelIndex>(context->argument(1));
        bool _q_result = _q_self->insertColumn(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        bool _q_result = _q_self->insertColumns(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 3) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        QModelIndex _q_arg2 = qscriptvalue_cast<QModelIndex>(context->argument(2));
        bool _q_result = _q_self->insertColumns(_q_arg0, _q_arg1, _q_arg2);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        bool _q_result = _q_self->insertRow(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        QModelIndex _q_arg1 = qscriptvalue_cast<QModelIndex>(context->argument(1));
        bool _q_result = _q_self->insertRow(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        bool _q_result = _q_self->insertRows(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 3) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        QModelIndex _q_arg2 = qscriptvalue_cast<QModelIndex>(context->argument(2));
        bool _q_result = _q_self->insertRows(_q_arg0, _q_arg1, _q_arg2);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 1) {
        QModelIndex _q_arg0 = qscriptvalue_cast<QModelIndex>(context->argument(0));
        QMap<int,QVariant > _q_result = _q_self->itemData(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 1) {
        QList<QModelIndex> _q_arg0;
        qScriptValueToSequence(context->argument(0), _q_arg0);
        QMimeData* _q_result = _q_self->mimeData(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 0) {
        QStringList _q_result = _q_self->mimeTypes();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 10:
    if (context->argumentCount() == 4) {
        QModelIndex _q_arg0 = qscriptvalue_cast<QModelIndex>(context->argument(0));
        int _q_arg1 = context->argument(1).toInt32();
        QModelIndex _q_arg2 = qscriptvalue_cast<QModelIndex>(context->argument(2));
        int _q_arg3 = context->argument(3).toInt32();
        bool _q_result = _q_self->moveColumn(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 11:
    if (context->argumentCount() == 5) {
        QModelIndex _q_arg0 = qscriptvalue_cast<QModelIndex>(context->argument(0));
        int _q_arg1 = context->argument(1).toInt32();
        int _q_arg2 = context->argument(2).toInt32();
        QModelIndex _q_arg3 = qscriptvalue_cast<QModelIndex>(context->argument(3));
        int _q_arg4 = context->argument(4).toInt32();
        bool _q_result = _q_self->moveColumns(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 12:
    if (context->argumentCount() == 4) {
        QModelIndex _q_arg0 = qscriptvalue_cast<QModelIndex>(context->argument(0));
        int _q_arg1 = context->argument(1).toInt32();
        QModelIndex _q_arg2 = qscriptvalue_cast<QModelIndex>(context->argument(2));
        int _q_arg3 = context->argument(3).toInt32();
        bool _q_result = _q_self->moveRow(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 13:
    if (context->argumentCount() == 5) {
        QModelIndex _q_arg0 = qscriptvalue_cast<QModelIndex>(context->argument(0));
        int _q_arg1 = context->argument(1).toInt32();
        int _q_arg2 = context->argument(2).toInt32();
        QModelIndex _q_arg3 = qscriptvalue_cast<QModelIndex>(context->argument(3));
        int _q_arg4 = context->argument(4).toInt32();
        bool _q_result = _q_self->moveRows(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 14:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        bool _q_result = _q_self->removeColumn(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        QModelIndex _q_arg1 = qscriptvalue_cast<QModelIndex>(context->argument(1));
        bool _q_result = _q_self->removeColumn(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 15:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        bool _q_result = _q_self->removeColumns(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 3) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        QModelIndex _q_arg2 = qscriptvalue_cast<QModelIndex>(context->argument(2));
        bool _q_result = _q_self->removeColumns(_q_arg0, _q_arg1, _q_arg2);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 16:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        bool _q_result = _q_self->removeRow(_q_arg0);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        QModelIndex _q_arg1 = qscriptvalue_cast<QModelIndex>(context->argument(1));
        bool _q_result = _q_self->removeRow(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 17:
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        bool _q_result = _q_self->removeRows(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 3) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        QModelIndex _q_arg2 = qscriptvalue_cast<QModelIndex>(context->argument(2));
        bool _q_result = _q_self->removeRows(_q_arg0, _q_arg1, _q_arg2);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 18:
    if (context->argumentCount() == 0) {
        QHash<int,QByteArray > _q_result = _q_self->roleNames();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 19:
    if (context->argumentCount() == 3) {
        int _q_arg0 = context->argument(0).toInt32();
        Qt::Orientation _q_arg1 = qscriptvalue_cast<Qt::Orientation>(context->argument(1));
        QVariant _q_arg2 = context->argument(2).toVariant();
        bool _q_result = _q_self->setHeaderData(_q_arg0, _q_arg1, _q_arg2);
        return QScriptValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 4) {
        int _q_arg0 = context->argument(0).toInt32();
        Qt::Orientation _q_arg1 = qscriptvalue_cast<Qt::Orientation>(context->argument(1));
        QVariant _q_arg2 = context->argument(2).toVariant();
        int _q_arg3 = context->argument(3).toInt32();
        bool _q_result = _q_self->setHeaderData(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 20:
    if (context->argumentCount() == 2) {
        QModelIndex _q_arg0 = qscriptvalue_cast<QModelIndex>(context->argument(0));
        QMap<int,QVariant> _q_arg1 = qscriptvalue_cast<QMap<int,QVariant> >(context->argument(1));
        bool _q_result = _q_self->setItemData(_q_arg0, _q_arg1);
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 21:
    if (context->argumentCount() == 1) {
        int _q_arg0 = context->argument(0).toInt32();
        _q_self->sort(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        Qt::SortOrder _q_arg1 = qscriptvalue_cast<Qt::SortOrder>(context->argument(1));
        _q_self->sort(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 22:
    if (context->argumentCount() == 1) {
        QModelIndex _q_arg0 = qscriptvalue_cast<QModelIndex>(context->argument(0));
        QSize _q_result = _q_self->span(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 23:
    if (context->argumentCount() == 0) {
        QFlags<Qt::DropAction> _q_result = _q_self->supportedDragActions();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 24:
    if (context->argumentCount() == 0) {
        QFlags<Qt::DropAction> _q_result = _q_self->supportedDropActions();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 25: {
    QString result = QString::fromLatin1("QAbstractItemModel");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QAbstractItemModel_throw_ambiguity_error_helper(context,
        qtscript_QAbstractItemModel_function_names[_id+1],
        qtscript_QAbstractItemModel_function_signatures[_id+1]);
}

static QScriptValue qtscript_QAbstractItemModel_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QAbstractItemModel(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QAbstractItemModel* _q_cpp_result = new QtScriptShell_QAbstractItemModel();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QAbstractItemModel*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        QObject* _q_arg0 = context->argument(0).toQObject();
        QtScriptShell_QAbstractItemModel* _q_cpp_result = new QtScriptShell_QAbstractItemModel(_q_arg0);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QAbstractItemModel*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QAbstractItemModel_throw_ambiguity_error_helper(context,
        qtscript_QAbstractItemModel_function_names[_id],
        qtscript_QAbstractItemModel_function_signatures[_id]);
}

static QScriptValue qtscript_QAbstractItemModel_toScriptValue(QScriptEngine *engine, QAbstractItemModel* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QAbstractItemModel_fromScriptValue(const QScriptValue &value, QAbstractItemModel* &out)
{
    out = qobject_cast<QAbstractItemModel*>(value.toQObject());
}

QScriptValue qtscript_create_QAbstractItemModel_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QAbstractItemModel*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QAbstractItemModel*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QObject*>()));
    for (int i = 0; i < 26; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QAbstractItemModel_prototype_call, qtscript_QAbstractItemModel_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QAbstractItemModel_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QAbstractItemModel*>(engine, qtscript_QAbstractItemModel_toScriptValue, 
        qtscript_QAbstractItemModel_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QAbstractItemModel_static_call, proto, qtscript_QAbstractItemModel_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    return ctor;
}
