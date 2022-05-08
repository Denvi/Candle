#include <QtScript/QScriptEngine>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <qmetaobject.h>
#include <__package_shared.h>

#include <qgraphicsview.h>
#include <QPainterPath>
#include <QVarLengthArray>
#include <QVariant>
#include <qaction.h>
#include <qbitmap.h>
#include <qbrush.h>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qcursor.h>
#include <qevent.h>
#include <qfont.h>
#include <qgraphicseffect.h>
#include <qgraphicsitem.h>
#include <qgraphicsproxywidget.h>
#include <qgraphicsscene.h>
#include <qgraphicsview.h>
#include <qicon.h>
#include <qkeysequence.h>
#include <qlayout.h>
#include <qlist.h>
#include <qlocale.h>
#include <qmargins.h>
#include <qmatrix.h>
#include <qobject.h>
#include <qpaintdevice.h>
#include <qpaintengine.h>
#include <qpainter.h>
#include <qpainterpath.h>
#include <qpalette.h>
#include <qpixmap.h>
#include <qpoint.h>
#include <qpolygon.h>
#include <qrect.h>
#include <qregion.h>
#include <qscrollbar.h>
#include <qsize.h>
#include <qsizepolicy.h>
#include <qstyle.h>
#include <qstyleoption.h>
#include <qtransform.h>
#include <qwidget.h>

#include "qtscriptshell_QGraphicsView.h"

static const char * const qtscript_QGraphicsView_function_names[] = {
    "QGraphicsView"
    // static
    // prototype
    , "centerOn"
    , "ensureVisible"
    , "fitInView"
    , "isTransformed"
    , "itemAt"
    , "items"
    , "mapFromScene"
    , "mapToScene"
    , "matrix"
    , "render"
    , "resetCachedContent"
    , "resetMatrix"
    , "resetTransform"
    , "rotate"
    , "rubberBandRect"
    , "scale"
    , "scene"
    , "setMatrix"
    , "setOptimizationFlag"
    , "setRenderHint"
    , "setScene"
    , "setSceneRect"
    , "setTransform"
    , "shear"
    , "transform"
    , "translate"
    , "viewportTransform"
    , "toString"
};

static const char * const qtscript_QGraphicsView_function_signatures[] = {
    "QGraphicsScene scene, QWidget parent\nQWidget parent"
    // static
    // prototype
    , "QGraphicsItem item\nQPointF pos\nqreal x, qreal y"
    , "QGraphicsItem item, int xmargin, int ymargin\nQRectF rect, int xmargin, int ymargin\nqreal x, qreal y, qreal w, qreal h, int xmargin, int ymargin"
    , "QGraphicsItem item, AspectRatioMode aspectRadioMode\nQRectF rect, AspectRatioMode aspectRadioMode\nqreal x, qreal y, qreal w, qreal h, AspectRatioMode aspectRadioMode"
    , ""
    , "QPoint pos\nint x, int y"
    , "\nQPainterPath path, ItemSelectionMode mode\nQPoint pos\nQPolygon polygon, ItemSelectionMode mode\nQRect rect, ItemSelectionMode mode\nint x, int y\nint x, int y, int w, int h, ItemSelectionMode mode"
    , "QPainterPath path\nQPointF point\nQPolygonF polygon\nQRectF rect\nqreal x, qreal y\nqreal x, qreal y, qreal w, qreal h"
    , "QPainterPath path\nQPoint point\nQPolygon polygon\nQRect rect\nint x, int y\nint x, int y, int w, int h"
    , ""
    , "QPainter painter, QRectF target, QRect source, AspectRatioMode aspectRatioMode"
    , ""
    , ""
    , ""
    , "qreal angle"
    , ""
    , "qreal sx, qreal sy"
    , ""
    , "QMatrix matrix, bool combine"
    , "OptimizationFlag flag, bool enabled"
    , "RenderHint hint, bool enabled"
    , "QGraphicsScene scene"
    , "qreal x, qreal y, qreal w, qreal h"
    , "QTransform matrix, bool combine"
    , "qreal sh, qreal sv"
    , ""
    , "qreal dx, qreal dy"
    , ""
""
};

static const int qtscript_QGraphicsView_function_lengths[] = {
    2
    // static
    // prototype
    , 2
    , 6
    , 5
    , 0
    , 2
    , 5
    , 4
    , 4
    , 0
    , 4
    , 0
    , 0
    , 0
    , 1
    , 0
    , 2
    , 0
    , 2
    , 2
    , 2
    , 1
    , 4
    , 2
    , 2
    , 0
    , 2
    , 0
    , 0
};

static QScriptValue qtscript_QGraphicsView_throw_ambiguity_error_helper(
    QScriptContext *context, const char *functionName, const char *signatures)
{
    QStringList lines = QString::fromLatin1(signatures).split(QLatin1Char('\n'));
    QStringList fullSignatures;
    for (int i = 0; i < lines.size(); ++i)
        fullSignatures.append(QString::fromLatin1("%0(%1)").arg(functionName).arg(lines.at(i)));
    return context->throwError(QString::fromLatin1("QGraphicsView::%0(): could not find a function match; candidates are:\n%1")
        .arg(functionName).arg(fullSignatures.join(QLatin1String("\n"))));
}

Q_DECLARE_METATYPE(QGraphicsView*)
Q_DECLARE_METATYPE(QtScriptShell_QGraphicsView*)
Q_DECLARE_METATYPE(QGraphicsView::DragMode)
Q_DECLARE_METATYPE(QGraphicsView::ViewportAnchor)
Q_DECLARE_METATYPE(const QGraphicsItem*)
Q_DECLARE_METATYPE(Qt::AspectRatioMode)
Q_DECLARE_METATYPE(QList<QGraphicsItem* >)
Q_DECLARE_METATYPE(QPainterPath)
Q_DECLARE_METATYPE(Qt::ItemSelectionMode)
Q_DECLARE_METATYPE(QPainter*)
Q_DECLARE_METATYPE(QGraphicsScene*)
Q_DECLARE_METATYPE(QGraphicsView::OptimizationFlag)
Q_DECLARE_METATYPE(QPainter::RenderHint)
Q_DECLARE_METATYPE(QWidget*)
Q_DECLARE_METATYPE(QAbstractScrollArea*)

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
// QGraphicsView::DragMode
//

static const QGraphicsView::DragMode qtscript_QGraphicsView_DragMode_values[] = {
    QGraphicsView::NoDrag
    , QGraphicsView::ScrollHandDrag
    , QGraphicsView::RubberBandDrag
};

static const char * const qtscript_QGraphicsView_DragMode_keys[] = {
    "NoDrag"
    , "ScrollHandDrag"
    , "RubberBandDrag"
};

static QString qtscript_QGraphicsView_DragMode_toStringHelper(QGraphicsView::DragMode value)
{
    if ((value >= QGraphicsView::NoDrag) && (value <= QGraphicsView::RubberBandDrag))
        return qtscript_QGraphicsView_DragMode_keys[static_cast<int>(value)-static_cast<int>(QGraphicsView::NoDrag)];
    return QString();
}

static QScriptValue qtscript_QGraphicsView_DragMode_toScriptValue(QScriptEngine *engine, const QGraphicsView::DragMode &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QGraphicsView"));
    return clazz.property(qtscript_QGraphicsView_DragMode_toStringHelper(value));
}

static void qtscript_QGraphicsView_DragMode_fromScriptValue(const QScriptValue &value, QGraphicsView::DragMode &out)
{
    out = qvariant_cast<QGraphicsView::DragMode>(value.toVariant());
}

static QScriptValue qtscript_construct_QGraphicsView_DragMode(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QGraphicsView::NoDrag) && (arg <= QGraphicsView::RubberBandDrag))
        return qScriptValueFromValue(engine,  static_cast<QGraphicsView::DragMode>(arg));
    return context->throwError(QString::fromLatin1("DragMode(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QGraphicsView_DragMode_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QGraphicsView::DragMode value = qscriptvalue_cast<QGraphicsView::DragMode>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QGraphicsView_DragMode_toString(QScriptContext *context, QScriptEngine *engine)
{
    QGraphicsView::DragMode value = qscriptvalue_cast<QGraphicsView::DragMode>(context->thisObject());
    return QScriptValue(engine, qtscript_QGraphicsView_DragMode_toStringHelper(value));
}

static QScriptValue qtscript_create_QGraphicsView_DragMode_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QGraphicsView_DragMode,
        qtscript_QGraphicsView_DragMode_valueOf, qtscript_QGraphicsView_DragMode_toString);
    qScriptRegisterMetaType<QGraphicsView::DragMode>(engine, qtscript_QGraphicsView_DragMode_toScriptValue,
        qtscript_QGraphicsView_DragMode_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 3; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QGraphicsView_DragMode_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QGraphicsView_DragMode_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QGraphicsView::ViewportAnchor
//

static const QGraphicsView::ViewportAnchor qtscript_QGraphicsView_ViewportAnchor_values[] = {
    QGraphicsView::NoAnchor
    , QGraphicsView::AnchorViewCenter
    , QGraphicsView::AnchorUnderMouse
};

static const char * const qtscript_QGraphicsView_ViewportAnchor_keys[] = {
    "NoAnchor"
    , "AnchorViewCenter"
    , "AnchorUnderMouse"
};

static QString qtscript_QGraphicsView_ViewportAnchor_toStringHelper(QGraphicsView::ViewportAnchor value)
{
    if ((value >= QGraphicsView::NoAnchor) && (value <= QGraphicsView::AnchorUnderMouse))
        return qtscript_QGraphicsView_ViewportAnchor_keys[static_cast<int>(value)-static_cast<int>(QGraphicsView::NoAnchor)];
    return QString();
}

static QScriptValue qtscript_QGraphicsView_ViewportAnchor_toScriptValue(QScriptEngine *engine, const QGraphicsView::ViewportAnchor &value)
{
    QScriptValue clazz = engine->globalObject().property(QString::fromLatin1("QGraphicsView"));
    return clazz.property(qtscript_QGraphicsView_ViewportAnchor_toStringHelper(value));
}

static void qtscript_QGraphicsView_ViewportAnchor_fromScriptValue(const QScriptValue &value, QGraphicsView::ViewportAnchor &out)
{
    out = qvariant_cast<QGraphicsView::ViewportAnchor>(value.toVariant());
}

static QScriptValue qtscript_construct_QGraphicsView_ViewportAnchor(QScriptContext *context, QScriptEngine *engine)
{
    int arg = context->argument(0).toInt32();
    if ((arg >= QGraphicsView::NoAnchor) && (arg <= QGraphicsView::AnchorUnderMouse))
        return qScriptValueFromValue(engine,  static_cast<QGraphicsView::ViewportAnchor>(arg));
    return context->throwError(QString::fromLatin1("ViewportAnchor(): invalid enum value (%0)").arg(arg));
}

static QScriptValue qtscript_QGraphicsView_ViewportAnchor_valueOf(QScriptContext *context, QScriptEngine *engine)
{
    QGraphicsView::ViewportAnchor value = qscriptvalue_cast<QGraphicsView::ViewportAnchor>(context->thisObject());
    return QScriptValue(engine, static_cast<int>(value));
}

static QScriptValue qtscript_QGraphicsView_ViewportAnchor_toString(QScriptContext *context, QScriptEngine *engine)
{
    QGraphicsView::ViewportAnchor value = qscriptvalue_cast<QGraphicsView::ViewportAnchor>(context->thisObject());
    return QScriptValue(engine, qtscript_QGraphicsView_ViewportAnchor_toStringHelper(value));
}

static QScriptValue qtscript_create_QGraphicsView_ViewportAnchor_class(QScriptEngine *engine, QScriptValue &clazz)
{
    QScriptValue ctor = qtscript_create_enum_class_helper(
        engine, qtscript_construct_QGraphicsView_ViewportAnchor,
        qtscript_QGraphicsView_ViewportAnchor_valueOf, qtscript_QGraphicsView_ViewportAnchor_toString);
    qScriptRegisterMetaType<QGraphicsView::ViewportAnchor>(engine, qtscript_QGraphicsView_ViewportAnchor_toScriptValue,
        qtscript_QGraphicsView_ViewportAnchor_fromScriptValue, ctor.property(QString::fromLatin1("prototype")));
    for (int i = 0; i < 3; ++i) {
        clazz.setProperty(QString::fromLatin1(qtscript_QGraphicsView_ViewportAnchor_keys[i]),
            engine->newVariant(qVariantFromValue(qtscript_QGraphicsView_ViewportAnchor_values[i])),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    return ctor;
}

//
// QGraphicsView
//

static QScriptValue qtscript_QGraphicsView_prototype_call(QScriptContext *context, QScriptEngine *)
{
#if QT_VERSION > 0x040400
    Q_ASSERT(context->callee().isFunction());
    uint _id = context->callee().data().toUInt32();
#else
    uint _id;
    if (context->callee().isFunction())
        _id = context->callee().data().toUInt32();
    else
        _id = 0xBABE0000 + 27;
#endif
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    QGraphicsView* _q_self = qscriptvalue_cast<QGraphicsView*>(context->thisObject());
    if (!_q_self) {
        return context->throwError(QScriptContext::TypeError,
            QString::fromLatin1("QGraphicsView.%0(): this object is not a QGraphicsView")
            .arg(qtscript_QGraphicsView_function_names[_id+1]));
    }

    switch (_id) {
    case 0:
    if (context->argumentCount() == 1) {
        if (qscriptvalue_cast<const QGraphicsItem*>(context->argument(0))) {
            const QGraphicsItem* _q_arg0 = qscriptvalue_cast<const QGraphicsItem*>(context->argument(0));
            _q_self->centerOn(_q_arg0);
            return context->engine()->undefinedValue();
        } else if ((qMetaTypeId<QPointF>() == context->argument(0).toVariant().userType())) {
            QPointF _q_arg0 = qscriptvalue_cast<QPointF>(context->argument(0));
            _q_self->centerOn(_q_arg0);
            return context->engine()->undefinedValue();
        }
    }
    if (context->argumentCount() == 2) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        _q_self->centerOn(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 1:
    if (context->argumentCount() == 1) {
        if (qscriptvalue_cast<const QGraphicsItem*>(context->argument(0))) {
            const QGraphicsItem* _q_arg0 = qscriptvalue_cast<const QGraphicsItem*>(context->argument(0));
            _q_self->ensureVisible(_q_arg0);
            return context->engine()->undefinedValue();
        } else if ((qMetaTypeId<QRectF>() == context->argument(0).toVariant().userType())) {
            QRectF _q_arg0 = qscriptvalue_cast<QRectF>(context->argument(0));
            _q_self->ensureVisible(_q_arg0);
            return context->engine()->undefinedValue();
        }
    }
    if (context->argumentCount() == 2) {
        if (qscriptvalue_cast<const QGraphicsItem*>(context->argument(0))
            && context->argument(1).isNumber()) {
            const QGraphicsItem* _q_arg0 = qscriptvalue_cast<const QGraphicsItem*>(context->argument(0));
            int _q_arg1 = context->argument(1).toInt32();
            _q_self->ensureVisible(_q_arg0, _q_arg1);
            return context->engine()->undefinedValue();
        } else if ((qMetaTypeId<QRectF>() == context->argument(0).toVariant().userType())
            && context->argument(1).isNumber()) {
            QRectF _q_arg0 = qscriptvalue_cast<QRectF>(context->argument(0));
            int _q_arg1 = context->argument(1).toInt32();
            _q_self->ensureVisible(_q_arg0, _q_arg1);
            return context->engine()->undefinedValue();
        }
    }
    if (context->argumentCount() == 3) {
        if (qscriptvalue_cast<const QGraphicsItem*>(context->argument(0))
            && context->argument(1).isNumber()
            && context->argument(2).isNumber()) {
            const QGraphicsItem* _q_arg0 = qscriptvalue_cast<const QGraphicsItem*>(context->argument(0));
            int _q_arg1 = context->argument(1).toInt32();
            int _q_arg2 = context->argument(2).toInt32();
            _q_self->ensureVisible(_q_arg0, _q_arg1, _q_arg2);
            return context->engine()->undefinedValue();
        } else if ((qMetaTypeId<QRectF>() == context->argument(0).toVariant().userType())
            && context->argument(1).isNumber()
            && context->argument(2).isNumber()) {
            QRectF _q_arg0 = qscriptvalue_cast<QRectF>(context->argument(0));
            int _q_arg1 = context->argument(1).toInt32();
            int _q_arg2 = context->argument(2).toInt32();
            _q_self->ensureVisible(_q_arg0, _q_arg1, _q_arg2);
            return context->engine()->undefinedValue();
        }
    }
    if (context->argumentCount() == 4) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        qreal _q_arg2 = qscriptvalue_cast<qreal>(context->argument(2));
        qreal _q_arg3 = qscriptvalue_cast<qreal>(context->argument(3));
        _q_self->ensureVisible(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 5) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        qreal _q_arg2 = qscriptvalue_cast<qreal>(context->argument(2));
        qreal _q_arg3 = qscriptvalue_cast<qreal>(context->argument(3));
        int _q_arg4 = context->argument(4).toInt32();
        _q_self->ensureVisible(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 6) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        qreal _q_arg2 = qscriptvalue_cast<qreal>(context->argument(2));
        qreal _q_arg3 = qscriptvalue_cast<qreal>(context->argument(3));
        int _q_arg4 = context->argument(4).toInt32();
        int _q_arg5 = context->argument(5).toInt32();
        _q_self->ensureVisible(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4, _q_arg5);
        return context->engine()->undefinedValue();
    }
    break;

    case 2:
    if (context->argumentCount() == 1) {
        if (qscriptvalue_cast<const QGraphicsItem*>(context->argument(0))) {
            const QGraphicsItem* _q_arg0 = qscriptvalue_cast<const QGraphicsItem*>(context->argument(0));
            _q_self->fitInView(_q_arg0);
            return context->engine()->undefinedValue();
        } else if ((qMetaTypeId<QRectF>() == context->argument(0).toVariant().userType())) {
            QRectF _q_arg0 = qscriptvalue_cast<QRectF>(context->argument(0));
            _q_self->fitInView(_q_arg0);
            return context->engine()->undefinedValue();
        }
    }
    if (context->argumentCount() == 2) {
        if (qscriptvalue_cast<const QGraphicsItem*>(context->argument(0))
            && (qMetaTypeId<Qt::AspectRatioMode>() == context->argument(1).toVariant().userType())) {
            const QGraphicsItem* _q_arg0 = qscriptvalue_cast<const QGraphicsItem*>(context->argument(0));
            Qt::AspectRatioMode _q_arg1 = qscriptvalue_cast<Qt::AspectRatioMode>(context->argument(1));
            _q_self->fitInView(_q_arg0, _q_arg1);
            return context->engine()->undefinedValue();
        } else if ((qMetaTypeId<QRectF>() == context->argument(0).toVariant().userType())
            && (qMetaTypeId<Qt::AspectRatioMode>() == context->argument(1).toVariant().userType())) {
            QRectF _q_arg0 = qscriptvalue_cast<QRectF>(context->argument(0));
            Qt::AspectRatioMode _q_arg1 = qscriptvalue_cast<Qt::AspectRatioMode>(context->argument(1));
            _q_self->fitInView(_q_arg0, _q_arg1);
            return context->engine()->undefinedValue();
        }
    }
    if (context->argumentCount() == 4) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        qreal _q_arg2 = qscriptvalue_cast<qreal>(context->argument(2));
        qreal _q_arg3 = qscriptvalue_cast<qreal>(context->argument(3));
        _q_self->fitInView(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 5) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        qreal _q_arg2 = qscriptvalue_cast<qreal>(context->argument(2));
        qreal _q_arg3 = qscriptvalue_cast<qreal>(context->argument(3));
        Qt::AspectRatioMode _q_arg4 = qscriptvalue_cast<Qt::AspectRatioMode>(context->argument(4));
        _q_self->fitInView(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4);
        return context->engine()->undefinedValue();
    }
    break;

    case 3:
    if (context->argumentCount() == 0) {
        bool _q_result = _q_self->isTransformed();
        return QScriptValue(context->engine(), _q_result);
    }
    break;

    case 4:
    if (context->argumentCount() == 1) {
        QPoint _q_arg0 = qscriptvalue_cast<QPoint>(context->argument(0));
        QGraphicsItem* _q_result = _q_self->itemAt(_q_arg0);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        QGraphicsItem* _q_result = _q_self->itemAt(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 5:
    if (context->argumentCount() == 0) {
        QList<QGraphicsItem* > _q_result = _q_self->items();
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    if (context->argumentCount() == 1) {
        if ((qMetaTypeId<QPainterPath>() == context->argument(0).toVariant().userType())) {
            QPainterPath _q_arg0 = qscriptvalue_cast<QPainterPath>(context->argument(0));
            QList<QGraphicsItem* > _q_result = _q_self->items(_q_arg0);
            return qScriptValueFromSequence(context->engine(), _q_result);
        } else if ((qMetaTypeId<QPoint>() == context->argument(0).toVariant().userType())) {
            QPoint _q_arg0 = qscriptvalue_cast<QPoint>(context->argument(0));
            QList<QGraphicsItem* > _q_result = _q_self->items(_q_arg0);
            return qScriptValueFromSequence(context->engine(), _q_result);
        } else if ((qMetaTypeId<QPolygon>() == context->argument(0).toVariant().userType())) {
            QPolygon _q_arg0 = qscriptvalue_cast<QPolygon>(context->argument(0));
            QList<QGraphicsItem* > _q_result = _q_self->items(_q_arg0);
            return qScriptValueFromSequence(context->engine(), _q_result);
        } else if ((qMetaTypeId<QRect>() == context->argument(0).toVariant().userType())) {
            QRect _q_arg0 = qscriptvalue_cast<QRect>(context->argument(0));
            QList<QGraphicsItem* > _q_result = _q_self->items(_q_arg0);
            return qScriptValueFromSequence(context->engine(), _q_result);
        }
    }
    if (context->argumentCount() == 2) {
        if ((qMetaTypeId<QPainterPath>() == context->argument(0).toVariant().userType())
            && (qMetaTypeId<Qt::ItemSelectionMode>() == context->argument(1).toVariant().userType())) {
            QPainterPath _q_arg0 = qscriptvalue_cast<QPainterPath>(context->argument(0));
            Qt::ItemSelectionMode _q_arg1 = qscriptvalue_cast<Qt::ItemSelectionMode>(context->argument(1));
            QList<QGraphicsItem* > _q_result = _q_self->items(_q_arg0, _q_arg1);
            return qScriptValueFromSequence(context->engine(), _q_result);
        } else if ((qMetaTypeId<QPolygon>() == context->argument(0).toVariant().userType())
            && (qMetaTypeId<Qt::ItemSelectionMode>() == context->argument(1).toVariant().userType())) {
            QPolygon _q_arg0 = qscriptvalue_cast<QPolygon>(context->argument(0));
            Qt::ItemSelectionMode _q_arg1 = qscriptvalue_cast<Qt::ItemSelectionMode>(context->argument(1));
            QList<QGraphicsItem* > _q_result = _q_self->items(_q_arg0, _q_arg1);
            return qScriptValueFromSequence(context->engine(), _q_result);
        } else if ((qMetaTypeId<QRect>() == context->argument(0).toVariant().userType())
            && (qMetaTypeId<Qt::ItemSelectionMode>() == context->argument(1).toVariant().userType())) {
            QRect _q_arg0 = qscriptvalue_cast<QRect>(context->argument(0));
            Qt::ItemSelectionMode _q_arg1 = qscriptvalue_cast<Qt::ItemSelectionMode>(context->argument(1));
            QList<QGraphicsItem* > _q_result = _q_self->items(_q_arg0, _q_arg1);
            return qScriptValueFromSequence(context->engine(), _q_result);
        } else if (context->argument(0).isNumber()
            && context->argument(1).isNumber()) {
            int _q_arg0 = context->argument(0).toInt32();
            int _q_arg1 = context->argument(1).toInt32();
            QList<QGraphicsItem* > _q_result = _q_self->items(_q_arg0, _q_arg1);
            return qScriptValueFromSequence(context->engine(), _q_result);
        }
    }
    if (context->argumentCount() == 4) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        int _q_arg2 = context->argument(2).toInt32();
        int _q_arg3 = context->argument(3).toInt32();
        QList<QGraphicsItem* > _q_result = _q_self->items(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    if (context->argumentCount() == 5) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        int _q_arg2 = context->argument(2).toInt32();
        int _q_arg3 = context->argument(3).toInt32();
        Qt::ItemSelectionMode _q_arg4 = qscriptvalue_cast<Qt::ItemSelectionMode>(context->argument(4));
        QList<QGraphicsItem* > _q_result = _q_self->items(_q_arg0, _q_arg1, _q_arg2, _q_arg3, _q_arg4);
        return qScriptValueFromSequence(context->engine(), _q_result);
    }
    break;

    case 6:
    if (context->argumentCount() == 1) {
        if ((qMetaTypeId<QPainterPath>() == context->argument(0).toVariant().userType())) {
            QPainterPath _q_arg0 = qscriptvalue_cast<QPainterPath>(context->argument(0));
            QPainterPath _q_result = _q_self->mapFromScene(_q_arg0);
            return qScriptValueFromValue(context->engine(), _q_result);
        } else if ((qMetaTypeId<QPointF>() == context->argument(0).toVariant().userType())) {
            QPointF _q_arg0 = qscriptvalue_cast<QPointF>(context->argument(0));
            QPoint _q_result = _q_self->mapFromScene(_q_arg0);
            return qScriptValueFromValue(context->engine(), _q_result);
        } else if ((qMetaTypeId<QPolygonF>() == context->argument(0).toVariant().userType())) {
            QPolygonF _q_arg0 = qscriptvalue_cast<QPolygonF>(context->argument(0));
            QPolygon _q_result = _q_self->mapFromScene(_q_arg0);
            return qScriptValueFromValue(context->engine(), _q_result);
        } else if ((qMetaTypeId<QRectF>() == context->argument(0).toVariant().userType())) {
            QRectF _q_arg0 = qscriptvalue_cast<QRectF>(context->argument(0));
            QPolygon _q_result = _q_self->mapFromScene(_q_arg0);
            return qScriptValueFromValue(context->engine(), _q_result);
        }
    }
    if (context->argumentCount() == 2) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        QPoint _q_result = _q_self->mapFromScene(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 4) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        qreal _q_arg2 = qscriptvalue_cast<qreal>(context->argument(2));
        qreal _q_arg3 = qscriptvalue_cast<qreal>(context->argument(3));
        QPolygon _q_result = _q_self->mapFromScene(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 7:
    if (context->argumentCount() == 1) {
        if ((qMetaTypeId<QPainterPath>() == context->argument(0).toVariant().userType())) {
            QPainterPath _q_arg0 = qscriptvalue_cast<QPainterPath>(context->argument(0));
            QPainterPath _q_result = _q_self->mapToScene(_q_arg0);
            return qScriptValueFromValue(context->engine(), _q_result);
        } else if ((qMetaTypeId<QPoint>() == context->argument(0).toVariant().userType())) {
            QPoint _q_arg0 = qscriptvalue_cast<QPoint>(context->argument(0));
            QPointF _q_result = _q_self->mapToScene(_q_arg0);
            return qScriptValueFromValue(context->engine(), _q_result);
        } else if ((qMetaTypeId<QPolygon>() == context->argument(0).toVariant().userType())) {
            QPolygon _q_arg0 = qscriptvalue_cast<QPolygon>(context->argument(0));
            QPolygonF _q_result = _q_self->mapToScene(_q_arg0);
            return qScriptValueFromValue(context->engine(), _q_result);
        } else if ((qMetaTypeId<QRect>() == context->argument(0).toVariant().userType())) {
            QRect _q_arg0 = qscriptvalue_cast<QRect>(context->argument(0));
            QPolygonF _q_result = _q_self->mapToScene(_q_arg0);
            return qScriptValueFromValue(context->engine(), _q_result);
        }
    }
    if (context->argumentCount() == 2) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        QPointF _q_result = _q_self->mapToScene(_q_arg0, _q_arg1);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    if (context->argumentCount() == 4) {
        int _q_arg0 = context->argument(0).toInt32();
        int _q_arg1 = context->argument(1).toInt32();
        int _q_arg2 = context->argument(2).toInt32();
        int _q_arg3 = context->argument(3).toInt32();
        QPolygonF _q_result = _q_self->mapToScene(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 8:
    if (context->argumentCount() == 0) {
        QMatrix _q_result = _q_self->matrix();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 9:
    if (context->argumentCount() == 1) {
        QPainter* _q_arg0 = qscriptvalue_cast<QPainter*>(context->argument(0));
        _q_self->render(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 2) {
        QPainter* _q_arg0 = qscriptvalue_cast<QPainter*>(context->argument(0));
        QRectF _q_arg1 = qscriptvalue_cast<QRectF>(context->argument(1));
        _q_self->render(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 3) {
        QPainter* _q_arg0 = qscriptvalue_cast<QPainter*>(context->argument(0));
        QRectF _q_arg1 = qscriptvalue_cast<QRectF>(context->argument(1));
        QRect _q_arg2 = qscriptvalue_cast<QRect>(context->argument(2));
        _q_self->render(_q_arg0, _q_arg1, _q_arg2);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 4) {
        QPainter* _q_arg0 = qscriptvalue_cast<QPainter*>(context->argument(0));
        QRectF _q_arg1 = qscriptvalue_cast<QRectF>(context->argument(1));
        QRect _q_arg2 = qscriptvalue_cast<QRect>(context->argument(2));
        Qt::AspectRatioMode _q_arg3 = qscriptvalue_cast<Qt::AspectRatioMode>(context->argument(3));
        _q_self->render(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return context->engine()->undefinedValue();
    }
    break;

    case 10:
    if (context->argumentCount() == 0) {
        _q_self->resetCachedContent();
        return context->engine()->undefinedValue();
    }
    break;

    case 11:
    if (context->argumentCount() == 0) {
        _q_self->resetMatrix();
        return context->engine()->undefinedValue();
    }
    break;

    case 12:
    if (context->argumentCount() == 0) {
        _q_self->resetTransform();
        return context->engine()->undefinedValue();
    }
    break;

    case 13:
    if (context->argumentCount() == 1) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        _q_self->rotate(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 14:
    if (context->argumentCount() == 0) {
        QRect _q_result = _q_self->rubberBandRect();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 15:
    if (context->argumentCount() == 2) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        _q_self->scale(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 16:
    if (context->argumentCount() == 0) {
        QGraphicsScene* _q_result = _q_self->scene();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 17:
    if (context->argumentCount() == 1) {
        QMatrix _q_arg0 = qscriptvalue_cast<QMatrix>(context->argument(0));
        _q_self->setMatrix(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 2) {
        QMatrix _q_arg0 = qscriptvalue_cast<QMatrix>(context->argument(0));
        bool _q_arg1 = context->argument(1).toBoolean();
        _q_self->setMatrix(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 18:
    if (context->argumentCount() == 1) {
        QGraphicsView::OptimizationFlag _q_arg0 = qscriptvalue_cast<QGraphicsView::OptimizationFlag>(context->argument(0));
        _q_self->setOptimizationFlag(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 2) {
        QGraphicsView::OptimizationFlag _q_arg0 = qscriptvalue_cast<QGraphicsView::OptimizationFlag>(context->argument(0));
        bool _q_arg1 = context->argument(1).toBoolean();
        _q_self->setOptimizationFlag(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 19:
    if (context->argumentCount() == 1) {
        QPainter::RenderHint _q_arg0 = qscriptvalue_cast<QPainter::RenderHint>(context->argument(0));
        _q_self->setRenderHint(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 2) {
        QPainter::RenderHint _q_arg0 = qscriptvalue_cast<QPainter::RenderHint>(context->argument(0));
        bool _q_arg1 = context->argument(1).toBoolean();
        _q_self->setRenderHint(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 20:
    if (context->argumentCount() == 1) {
        QGraphicsScene* _q_arg0 = qscriptvalue_cast<QGraphicsScene*>(context->argument(0));
        _q_self->setScene(_q_arg0);
        return context->engine()->undefinedValue();
    }
    break;

    case 21:
    if (context->argumentCount() == 4) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        qreal _q_arg2 = qscriptvalue_cast<qreal>(context->argument(2));
        qreal _q_arg3 = qscriptvalue_cast<qreal>(context->argument(3));
        _q_self->setSceneRect(_q_arg0, _q_arg1, _q_arg2, _q_arg3);
        return context->engine()->undefinedValue();
    }
    break;

    case 22:
    if (context->argumentCount() == 1) {
        QTransform _q_arg0 = qscriptvalue_cast<QTransform>(context->argument(0));
        _q_self->setTransform(_q_arg0);
        return context->engine()->undefinedValue();
    }
    if (context->argumentCount() == 2) {
        QTransform _q_arg0 = qscriptvalue_cast<QTransform>(context->argument(0));
        bool _q_arg1 = context->argument(1).toBoolean();
        _q_self->setTransform(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 23:
    if (context->argumentCount() == 2) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        _q_self->shear(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 24:
    if (context->argumentCount() == 0) {
        QTransform _q_result = _q_self->transform();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 25:
    if (context->argumentCount() == 2) {
        qreal _q_arg0 = qscriptvalue_cast<qreal>(context->argument(0));
        qreal _q_arg1 = qscriptvalue_cast<qreal>(context->argument(1));
        _q_self->translate(_q_arg0, _q_arg1);
        return context->engine()->undefinedValue();
    }
    break;

    case 26:
    if (context->argumentCount() == 0) {
        QTransform _q_result = _q_self->viewportTransform();
        return qScriptValueFromValue(context->engine(), _q_result);
    }
    break;

    case 27: {
    QString result = QString::fromLatin1("QGraphicsView");
    return QScriptValue(context->engine(), result);
    }

    default:
    Q_ASSERT(false);
    }
    return qtscript_QGraphicsView_throw_ambiguity_error_helper(context,
        qtscript_QGraphicsView_function_names[_id+1],
        qtscript_QGraphicsView_function_signatures[_id+1]);
}

static QScriptValue qtscript_QGraphicsView_static_call(QScriptContext *context, QScriptEngine *)
{
    uint _id = context->callee().data().toUInt32();
    Q_ASSERT((_id & 0xFFFF0000) == 0xBABE0000);
    _id &= 0x0000FFFF;
    switch (_id) {
    case 0:
    if (context->thisObject().strictlyEquals(context->engine()->globalObject())) {
        return context->throwError(QString::fromLatin1("QGraphicsView(): Did you forget to construct with 'new'?"));
    }
    if (context->argumentCount() == 0) {
        QtScriptShell_QGraphicsView* _q_cpp_result = new QtScriptShell_QGraphicsView();
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QGraphicsView*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    } else if (context->argumentCount() == 1) {
        if (qscriptvalue_cast<QGraphicsScene*>(context->argument(0))) {
            QGraphicsScene* _q_arg0 = qscriptvalue_cast<QGraphicsScene*>(context->argument(0));
            QtScriptShell_QGraphicsView* _q_cpp_result = new QtScriptShell_QGraphicsView(_q_arg0);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QGraphicsView*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        } else if (qscriptvalue_cast<QWidget*>(context->argument(0))) {
            QWidget* _q_arg0 = qscriptvalue_cast<QWidget*>(context->argument(0));
            QtScriptShell_QGraphicsView* _q_cpp_result = new QtScriptShell_QGraphicsView(_q_arg0);
            QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QGraphicsView*)_q_cpp_result, QScriptEngine::AutoOwnership);
            _q_cpp_result->__qtscript_self = _q_result;
            return _q_result;
        }
    } else if (context->argumentCount() == 2) {
        QGraphicsScene* _q_arg0 = qscriptvalue_cast<QGraphicsScene*>(context->argument(0));
        QWidget* _q_arg1 = qscriptvalue_cast<QWidget*>(context->argument(1));
        QtScriptShell_QGraphicsView* _q_cpp_result = new QtScriptShell_QGraphicsView(_q_arg0, _q_arg1);
        QScriptValue _q_result = context->engine()->newQObject(context->thisObject(), (QGraphicsView*)_q_cpp_result, QScriptEngine::AutoOwnership);
        _q_cpp_result->__qtscript_self = _q_result;
        return _q_result;
    }
    break;

    default:
    Q_ASSERT(false);
    }
    return qtscript_QGraphicsView_throw_ambiguity_error_helper(context,
        qtscript_QGraphicsView_function_names[_id],
        qtscript_QGraphicsView_function_signatures[_id]);
}

static QScriptValue qtscript_QGraphicsView_toScriptValue(QScriptEngine *engine, QGraphicsView* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

static void qtscript_QGraphicsView_fromScriptValue(const QScriptValue &value, QGraphicsView* &out)
{
    out = qobject_cast<QGraphicsView*>(value.toQObject());
}

QScriptValue qtscript_create_QGraphicsView_class(QScriptEngine *engine)
{
    engine->setDefaultPrototype(qMetaTypeId<QGraphicsView*>(), QScriptValue());
    QScriptValue proto = engine->newVariant(qVariantFromValue((QGraphicsView*)0));
    proto.setPrototype(engine->defaultPrototype(qMetaTypeId<QAbstractScrollArea*>()));
    for (int i = 0; i < 28; ++i) {
        QScriptValue fun = engine->newFunction(qtscript_QGraphicsView_prototype_call, qtscript_QGraphicsView_function_lengths[i+1]);
        fun.setData(QScriptValue(engine, uint(0xBABE0000 + i)));
        proto.setProperty(QString::fromLatin1(qtscript_QGraphicsView_function_names[i+1]),
            fun, QScriptValue::SkipInEnumeration);
    }

    qScriptRegisterMetaType<QGraphicsView*>(engine, qtscript_QGraphicsView_toScriptValue, 
        qtscript_QGraphicsView_fromScriptValue, proto);

    QScriptValue ctor = engine->newFunction(qtscript_QGraphicsView_static_call, proto, qtscript_QGraphicsView_function_lengths[0]);
    ctor.setData(QScriptValue(engine, uint(0xBABE0000 + 0)));

    ctor.setProperty(QString::fromLatin1("DragMode"),
        qtscript_create_QGraphicsView_DragMode_class(engine, ctor));
    ctor.setProperty(QString::fromLatin1("ViewportAnchor"),
        qtscript_create_QGraphicsView_ViewportAnchor_class(engine, ctor));
    return ctor;
}
