#include "qtscriptshell_QUiLoader.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <QtWidgets/QAction>
#include <qaction.h>
#include <qactiongroup.h>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qdir.h>
#include <qiodevice.h>
#include <qlayout.h>
#include <qlist.h>
#include <qobject.h>
#include <qstringlist.h>
#include <quiloader.h>
#include <qwidget.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)

Q_DECLARE_METATYPE(QChildEvent*)
Q_DECLARE_METATYPE(QAction*)
Q_DECLARE_METATYPE(QActionGroup*)
Q_DECLARE_METATYPE(QLayout*)
Q_DECLARE_METATYPE(QWidget*)
Q_DECLARE_METATYPE(QEvent*)
Q_DECLARE_METATYPE(QTimerEvent*)

QtScriptShell_QUiLoader::QtScriptShell_QUiLoader(QObject*  parent)
    : QUiLoader(parent) {}

QtScriptShell_QUiLoader::~QtScriptShell_QUiLoader() {}

void QtScriptShell_QUiLoader::childEvent(QChildEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("childEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("childEvent") & QScriptValue::QObjectMember)) {
        QUiLoader::childEvent(event);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, event));
    }
}

QAction*  QtScriptShell_QUiLoader::createAction(QObject*  parent, const QString&  name)
{
    QScriptValue _q_function = __qtscript_self.property("createAction");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("createAction") & QScriptValue::QObjectMember)) {
        return QUiLoader::createAction(parent, name);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QAction* >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, parent)
            << qScriptValueFromValue(_q_engine, name)));
    }
}

QActionGroup*  QtScriptShell_QUiLoader::createActionGroup(QObject*  parent, const QString&  name)
{
    QScriptValue _q_function = __qtscript_self.property("createActionGroup");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("createActionGroup") & QScriptValue::QObjectMember)) {
        return QUiLoader::createActionGroup(parent, name);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QActionGroup* >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, parent)
            << qScriptValueFromValue(_q_engine, name)));
    }
}

QLayout*  QtScriptShell_QUiLoader::createLayout(const QString&  className, QObject*  parent, const QString&  name)
{
    QScriptValue _q_function = __qtscript_self.property("createLayout");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("createLayout") & QScriptValue::QObjectMember)) {
        return QUiLoader::createLayout(className, parent, name);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QLayout* >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, className)
            << qScriptValueFromValue(_q_engine, parent)
            << qScriptValueFromValue(_q_engine, name)));
    }
}

QWidget*  QtScriptShell_QUiLoader::createWidget(const QString&  className, QWidget*  parent, const QString&  name)
{
    QScriptValue _q_function = __qtscript_self.property("createWidget");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("createWidget") & QScriptValue::QObjectMember)) {
        return QUiLoader::createWidget(className, parent, name);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QWidget* >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, className)
            << qScriptValueFromValue(_q_engine, parent)
            << qScriptValueFromValue(_q_engine, name)));
    }
}

void QtScriptShell_QUiLoader::customEvent(QEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("customEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("customEvent") & QScriptValue::QObjectMember)) {
        QUiLoader::customEvent(event);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, event));
    }
}

bool  QtScriptShell_QUiLoader::event(QEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("event");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("event") & QScriptValue::QObjectMember)) {
        return QUiLoader::event(event);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, event)));
    }
}

bool  QtScriptShell_QUiLoader::eventFilter(QObject*  watched, QEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("eventFilter");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("eventFilter") & QScriptValue::QObjectMember)) {
        return QUiLoader::eventFilter(watched, event);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, watched)
            << qScriptValueFromValue(_q_engine, event)));
    }
}

void QtScriptShell_QUiLoader::timerEvent(QTimerEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("timerEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("timerEvent") & QScriptValue::QObjectMember)) {
        QUiLoader::timerEvent(event);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, event));
    }
}

