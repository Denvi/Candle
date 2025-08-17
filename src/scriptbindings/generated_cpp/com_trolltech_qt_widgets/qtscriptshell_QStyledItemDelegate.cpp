#include "qtscriptshell_QStyledItemDelegate.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qabstractitemmodel.h>
#include <qabstractitemview.h>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qevent.h>
#include <qitemeditorfactory.h>
#include <qlist.h>
#include <qlocale.h>
#include <qobject.h>
#include <qpainter.h>
#include <qsize.h>
#include <qstyleditemdelegate.h>
#include <qstyleoption.h>
#include <qvector.h>
#include <qwidget.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)

Q_DECLARE_METATYPE(QChildEvent*)
Q_DECLARE_METATYPE(QWidget*)
Q_DECLARE_METATYPE(QStyleOptionViewItem)
Q_DECLARE_METATYPE(QEvent*)
Q_DECLARE_METATYPE(QAbstractItemModel*)
Q_DECLARE_METATYPE(QHelpEvent*)
Q_DECLARE_METATYPE(QAbstractItemView*)
Q_DECLARE_METATYPE(QStyleOptionViewItem*)
Q_DECLARE_METATYPE(QPainter*)
Q_DECLARE_METATYPE(QVector<int >)
Q_DECLARE_METATYPE(QTimerEvent*)

QtScriptShell_QStyledItemDelegate::QtScriptShell_QStyledItemDelegate(QObject*  parent)
    : QStyledItemDelegate(parent) {}

QtScriptShell_QStyledItemDelegate::~QtScriptShell_QStyledItemDelegate() {}

void QtScriptShell_QStyledItemDelegate::childEvent(QChildEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("childEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("childEvent") & QScriptValue::QObjectMember)) {
        QStyledItemDelegate::childEvent(event);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, event));
    }
}

QWidget*  QtScriptShell_QStyledItemDelegate::createEditor(QWidget*  parent, const QStyleOptionViewItem&  option, const QModelIndex&  index) const
{
    QScriptValue _q_function = __qtscript_self.property("createEditor");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("createEditor") & QScriptValue::QObjectMember)) {
        return QStyledItemDelegate::createEditor(parent, option, index);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QWidget* >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, parent)
            << qScriptValueFromValue(_q_engine, option)
            << qScriptValueFromValue(_q_engine, index)));
    }
}

void QtScriptShell_QStyledItemDelegate::customEvent(QEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("customEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("customEvent") & QScriptValue::QObjectMember)) {
        QStyledItemDelegate::customEvent(event);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, event));
    }
}

void QtScriptShell_QStyledItemDelegate::destroyEditor(QWidget*  editor, const QModelIndex&  index) const
{
    QScriptValue _q_function = __qtscript_self.property("destroyEditor");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("destroyEditor") & QScriptValue::QObjectMember)) {
        QStyledItemDelegate::destroyEditor(editor, index);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, editor)
            << qScriptValueFromValue(_q_engine, index));
    }
}

QString  QtScriptShell_QStyledItemDelegate::displayText(const QVariant&  value, const QLocale&  locale) const
{
    QScriptValue _q_function = __qtscript_self.property("displayText");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("displayText") & QScriptValue::QObjectMember)) {
        return QStyledItemDelegate::displayText(value, locale);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QString >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, value)
            << qScriptValueFromValue(_q_engine, locale)));
    }
}

bool  QtScriptShell_QStyledItemDelegate::editorEvent(QEvent*  event, QAbstractItemModel*  model, const QStyleOptionViewItem&  option, const QModelIndex&  index)
{
    QScriptValue _q_function = __qtscript_self.property("editorEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("editorEvent") & QScriptValue::QObjectMember)) {
        return QStyledItemDelegate::editorEvent(event, model, option, index);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, event)
            << qScriptValueFromValue(_q_engine, model)
            << qScriptValueFromValue(_q_engine, option)
            << qScriptValueFromValue(_q_engine, index)));
    }
}

bool  QtScriptShell_QStyledItemDelegate::event(QEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("event");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("event") & QScriptValue::QObjectMember)) {
        return QStyledItemDelegate::event(event);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, event)));
    }
}

bool  QtScriptShell_QStyledItemDelegate::eventFilter(QObject*  object, QEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("eventFilter");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("eventFilter") & QScriptValue::QObjectMember)) {
        return QStyledItemDelegate::eventFilter(object, event);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, object)
            << qScriptValueFromValue(_q_engine, event)));
    }
}

bool  QtScriptShell_QStyledItemDelegate::helpEvent(QHelpEvent*  event, QAbstractItemView*  view, const QStyleOptionViewItem&  option, const QModelIndex&  index)
{
    QScriptValue _q_function = __qtscript_self.property("helpEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("helpEvent") & QScriptValue::QObjectMember)) {
        return QStyledItemDelegate::helpEvent(event, view, option, index);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, event)
            << qScriptValueFromValue(_q_engine, view)
            << qScriptValueFromValue(_q_engine, option)
            << qScriptValueFromValue(_q_engine, index)));
    }
}

void QtScriptShell_QStyledItemDelegate::initStyleOption(QStyleOptionViewItem*  option, const QModelIndex&  index) const
{
    QScriptValue _q_function = __qtscript_self.property("initStyleOption");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("initStyleOption") & QScriptValue::QObjectMember)) {
        QStyledItemDelegate::initStyleOption(option, index);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, option)
            << qScriptValueFromValue(_q_engine, index));
    }
}

void QtScriptShell_QStyledItemDelegate::paint(QPainter*  painter, const QStyleOptionViewItem&  option, const QModelIndex&  index) const
{
    QScriptValue _q_function = __qtscript_self.property("paint");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("paint") & QScriptValue::QObjectMember)) {
        QStyledItemDelegate::paint(painter, option, index);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, painter)
            << qScriptValueFromValue(_q_engine, option)
            << qScriptValueFromValue(_q_engine, index));
    }
}

QVector<int >  QtScriptShell_QStyledItemDelegate::paintingRoles() const
{
    QScriptValue _q_function = __qtscript_self.property("paintingRoles");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("paintingRoles") & QScriptValue::QObjectMember)) {
        return QStyledItemDelegate::paintingRoles();
    } else {
        return qscriptvalue_cast<QVector<int > >(_q_function.call(__qtscript_self));
    }
}

void QtScriptShell_QStyledItemDelegate::setEditorData(QWidget*  editor, const QModelIndex&  index) const
{
    QScriptValue _q_function = __qtscript_self.property("setEditorData");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setEditorData") & QScriptValue::QObjectMember)) {
        QStyledItemDelegate::setEditorData(editor, index);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, editor)
            << qScriptValueFromValue(_q_engine, index));
    }
}

void QtScriptShell_QStyledItemDelegate::setModelData(QWidget*  editor, QAbstractItemModel*  model, const QModelIndex&  index) const
{
    QScriptValue _q_function = __qtscript_self.property("setModelData");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("setModelData") & QScriptValue::QObjectMember)) {
        QStyledItemDelegate::setModelData(editor, model, index);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, editor)
            << qScriptValueFromValue(_q_engine, model)
            << qScriptValueFromValue(_q_engine, index));
    }
}

QSize  QtScriptShell_QStyledItemDelegate::sizeHint(const QStyleOptionViewItem&  option, const QModelIndex&  index) const
{
    QScriptValue _q_function = __qtscript_self.property("sizeHint");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("sizeHint") & QScriptValue::QObjectMember)) {
        return QStyledItemDelegate::sizeHint(option, index);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QSize >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, option)
            << qScriptValueFromValue(_q_engine, index)));
    }
}

void QtScriptShell_QStyledItemDelegate::timerEvent(QTimerEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("timerEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("timerEvent") & QScriptValue::QObjectMember)) {
        QStyledItemDelegate::timerEvent(event);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, event));
    }
}

void QtScriptShell_QStyledItemDelegate::updateEditorGeometry(QWidget*  editor, const QStyleOptionViewItem&  option, const QModelIndex&  index) const
{
    QScriptValue _q_function = __qtscript_self.property("updateEditorGeometry");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("updateEditorGeometry") & QScriptValue::QObjectMember)) {
        QStyledItemDelegate::updateEditorGeometry(editor, option, index);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, editor)
            << qScriptValueFromValue(_q_engine, option)
            << qScriptValueFromValue(_q_engine, index));
    }
}

