#include "qtscriptshell_QStyle.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qapplication.h>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qicon.h>
#include <qlist.h>
#include <qobject.h>
#include <qpainter.h>
#include <qpalette.h>
#include <qpixmap.h>
#include <qpoint.h>
#include <qrect.h>
#include <qsize.h>
#include <qstyle.h>
#include <qstyleoption.h>
#include <qwidget.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)

Q_DECLARE_METATYPE(QChildEvent*)
Q_DECLARE_METATYPE(QEvent*)
Q_DECLARE_METATYPE(QStyle::ComplexControl)
Q_DECLARE_METATYPE(const QStyleOptionComplex*)
Q_DECLARE_METATYPE(QPainter*)
Q_DECLARE_METATYPE(const QWidget*)
Q_DECLARE_METATYPE(QStyle::ControlElement)
Q_DECLARE_METATYPE(const QStyleOption*)
Q_DECLARE_METATYPE(QPalette::ColorRole)
Q_DECLARE_METATYPE(QStyle::PrimitiveElement)
Q_DECLARE_METATYPE(QIcon::Mode)
Q_DECLARE_METATYPE(QStyle::SubControl)
Q_DECLARE_METATYPE(QSizePolicy::ControlType)
Q_DECLARE_METATYPE(Qt::Orientation)
Q_DECLARE_METATYPE(QStyle::PixelMetric)
Q_DECLARE_METATYPE(QApplication*)
Q_DECLARE_METATYPE(QWidget*)
Q_DECLARE_METATYPE(QStyle::ContentsType)
Q_DECLARE_METATYPE(QStyle::StandardPixmap)
Q_DECLARE_METATYPE(QStyle::StyleHint)
Q_DECLARE_METATYPE(QStyleHintReturn*)
Q_DECLARE_METATYPE(QStyle::SubElement)
Q_DECLARE_METATYPE(QTimerEvent*)

QtScriptShell_QStyle::QtScriptShell_QStyle()
    : QStyle() {}

QtScriptShell_QStyle::~QtScriptShell_QStyle() {}

void QtScriptShell_QStyle::childEvent(QChildEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("childEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("childEvent") & QScriptValue::QObjectMember)) {
        QStyle::childEvent(event);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, event));
    }
}

void QtScriptShell_QStyle::customEvent(QEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("customEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("customEvent") & QScriptValue::QObjectMember)) {
        QStyle::customEvent(event);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, event));
    }
}

void QtScriptShell_QStyle::drawComplexControl(QStyle::ComplexControl  cc, const QStyleOptionComplex*  opt, QPainter*  p, const QWidget*  widget) const
{
    QScriptValue _q_function = __qtscript_self.property("drawComplexControl");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("drawComplexControl") & QScriptValue::QObjectMember)) {
        qFatal("QStyle::drawComplexControl() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, cc)
            << qScriptValueFromValue(_q_engine, const_cast<const QStyleOptionComplex *>(opt))
            << qScriptValueFromValue(_q_engine, p)
            << qScriptValueFromValue(_q_engine, const_cast<const QWidget *>(widget)));
    }
}

void QtScriptShell_QStyle::drawControl(QStyle::ControlElement  element, const QStyleOption*  opt, QPainter*  p, const QWidget*  w) const
{
    QScriptValue _q_function = __qtscript_self.property("drawControl");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("drawControl") & QScriptValue::QObjectMember)) {
        qFatal("QStyle::drawControl() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, element)
            << qScriptValueFromValue(_q_engine, const_cast<const QStyleOption *>(opt))
            << qScriptValueFromValue(_q_engine, p)
            << qScriptValueFromValue(_q_engine, const_cast<const QWidget *>(w)));
    }
}

void QtScriptShell_QStyle::drawItemPixmap(QPainter*  painter, const QRect&  rect, int  alignment, const QPixmap&  pixmap) const
{
    QScriptValue _q_function = __qtscript_self.property("drawItemPixmap");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("drawItemPixmap") & QScriptValue::QObjectMember)) {
        QStyle::drawItemPixmap(painter, rect, alignment, pixmap);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, painter)
            << qScriptValueFromValue(_q_engine, rect)
            << qScriptValueFromValue(_q_engine, alignment)
            << qScriptValueFromValue(_q_engine, pixmap));
    }
}

void QtScriptShell_QStyle::drawItemText(QPainter*  painter, const QRect&  rect, int  flags, const QPalette&  pal, bool  enabled, const QString&  text, QPalette::ColorRole  textRole) const
{
    QScriptValue _q_function = __qtscript_self.property("drawItemText");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("drawItemText") & QScriptValue::QObjectMember)) {
        QStyle::drawItemText(painter, rect, flags, pal, enabled, text, textRole);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, painter)
            << qScriptValueFromValue(_q_engine, rect)
            << qScriptValueFromValue(_q_engine, flags)
            << qScriptValueFromValue(_q_engine, pal)
            << qScriptValueFromValue(_q_engine, enabled)
            << qScriptValueFromValue(_q_engine, text)
            << qScriptValueFromValue(_q_engine, textRole));
    }
}

void QtScriptShell_QStyle::drawPrimitive(QStyle::PrimitiveElement  pe, const QStyleOption*  opt, QPainter*  p, const QWidget*  w) const
{
    QScriptValue _q_function = __qtscript_self.property("drawPrimitive");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("drawPrimitive") & QScriptValue::QObjectMember)) {
        qFatal("QStyle::drawPrimitive() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, pe)
            << qScriptValueFromValue(_q_engine, const_cast<const QStyleOption *>(opt))
            << qScriptValueFromValue(_q_engine, p)
            << qScriptValueFromValue(_q_engine, const_cast<const QWidget *>(w)));
    }
}

bool  QtScriptShell_QStyle::event(QEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("event");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("event") & QScriptValue::QObjectMember)) {
        return QStyle::event(event);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, event)));
    }
}

bool  QtScriptShell_QStyle::eventFilter(QObject*  watched, QEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("eventFilter");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("eventFilter") & QScriptValue::QObjectMember)) {
        return QStyle::eventFilter(watched, event);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<bool >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, watched)
            << qScriptValueFromValue(_q_engine, event)));
    }
}

QPixmap  QtScriptShell_QStyle::generatedIconPixmap(QIcon::Mode  iconMode, const QPixmap&  pixmap, const QStyleOption*  opt) const
{
    QScriptValue _q_function = __qtscript_self.property("generatedIconPixmap");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("generatedIconPixmap") & QScriptValue::QObjectMember)) {
        qFatal("QStyle::generatedIconPixmap() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QPixmap >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, iconMode)
            << qScriptValueFromValue(_q_engine, pixmap)
            << qScriptValueFromValue(_q_engine, const_cast<const QStyleOption *>(opt))));
    }
}

QStyle::SubControl  QtScriptShell_QStyle::hitTestComplexControl(QStyle::ComplexControl  cc, const QStyleOptionComplex*  opt, const QPoint&  pt, const QWidget*  widget) const
{
    QScriptValue _q_function = __qtscript_self.property("hitTestComplexControl");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("hitTestComplexControl") & QScriptValue::QObjectMember)) {
        qFatal("QStyle::hitTestComplexControl() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QStyle::SubControl >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, cc)
            << qScriptValueFromValue(_q_engine, const_cast<const QStyleOptionComplex *>(opt))
            << qScriptValueFromValue(_q_engine, pt)
            << qScriptValueFromValue(_q_engine, const_cast<const QWidget *>(widget))));
    }
}

QRect  QtScriptShell_QStyle::itemPixmapRect(const QRect&  r, int  flags, const QPixmap&  pixmap) const
{
    QScriptValue _q_function = __qtscript_self.property("itemPixmapRect");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("itemPixmapRect") & QScriptValue::QObjectMember)) {
        return QStyle::itemPixmapRect(r, flags, pixmap);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QRect >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, r)
            << qScriptValueFromValue(_q_engine, flags)
            << qScriptValueFromValue(_q_engine, pixmap)));
    }
}

int  QtScriptShell_QStyle::layoutSpacing(QSizePolicy::ControlType  control1, QSizePolicy::ControlType  control2, Qt::Orientation  orientation, const QStyleOption*  option, const QWidget*  widget) const
{
    QScriptValue _q_function = __qtscript_self.property("layoutSpacing");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("layoutSpacing") & QScriptValue::QObjectMember)) {
        qFatal("QStyle::layoutSpacing() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<int >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, control1)
            << qScriptValueFromValue(_q_engine, control2)
            << qScriptValueFromValue(_q_engine, orientation)
            << qScriptValueFromValue(_q_engine, const_cast<const QStyleOption *>(option))
            << qScriptValueFromValue(_q_engine, const_cast<const QWidget *>(widget))));
    }
}

int  QtScriptShell_QStyle::pixelMetric(QStyle::PixelMetric  metric, const QStyleOption*  option, const QWidget*  widget) const
{
    QScriptValue _q_function = __qtscript_self.property("pixelMetric");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("pixelMetric") & QScriptValue::QObjectMember)) {
        qFatal("QStyle::pixelMetric() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<int >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, metric)
            << qScriptValueFromValue(_q_engine, const_cast<const QStyleOption *>(option))
            << qScriptValueFromValue(_q_engine, const_cast<const QWidget *>(widget))));
    }
}

void QtScriptShell_QStyle::polish(QApplication*  application)
{
    QScriptValue _q_function = __qtscript_self.property("polish");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("polish") & QScriptValue::QObjectMember)) {
        QStyle::polish(application);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, application));
    }
}

void QtScriptShell_QStyle::polish(QPalette&  palette)
{
    QScriptValue _q_function = __qtscript_self.property("polish");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("polish") & QScriptValue::QObjectMember)) {
        QStyle::polish(palette);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, palette));
    }
}

void QtScriptShell_QStyle::polish(QWidget*  widget)
{
    QScriptValue _q_function = __qtscript_self.property("polish");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("polish") & QScriptValue::QObjectMember)) {
        QStyle::polish(widget);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, widget));
    }
}

QSize  QtScriptShell_QStyle::sizeFromContents(QStyle::ContentsType  ct, const QStyleOption*  opt, const QSize&  contentsSize, const QWidget*  w) const
{
    QScriptValue _q_function = __qtscript_self.property("sizeFromContents");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("sizeFromContents") & QScriptValue::QObjectMember)) {
        qFatal("QStyle::sizeFromContents() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QSize >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, ct)
            << qScriptValueFromValue(_q_engine, const_cast<const QStyleOption *>(opt))
            << qScriptValueFromValue(_q_engine, contentsSize)
            << qScriptValueFromValue(_q_engine, const_cast<const QWidget *>(w))));
    }
}

QIcon  QtScriptShell_QStyle::standardIcon(QStyle::StandardPixmap  standardIcon, const QStyleOption*  option, const QWidget*  widget) const
{
    QScriptValue _q_function = __qtscript_self.property("standardIcon");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("standardIcon") & QScriptValue::QObjectMember)) {
        qFatal("QStyle::standardIcon() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QIcon >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, standardIcon)
            << qScriptValueFromValue(_q_engine, const_cast<const QStyleOption *>(option))
            << qScriptValueFromValue(_q_engine, const_cast<const QWidget *>(widget))));
    }
}

QPalette  QtScriptShell_QStyle::standardPalette() const
{
    QScriptValue _q_function = __qtscript_self.property("standardPalette");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("standardPalette") & QScriptValue::QObjectMember)) {
        return QStyle::standardPalette();
    } else {
        return qscriptvalue_cast<QPalette >(_q_function.call(__qtscript_self));
    }
}

QPixmap  QtScriptShell_QStyle::standardPixmap(QStyle::StandardPixmap  standardPixmap, const QStyleOption*  opt, const QWidget*  widget) const
{
    QScriptValue _q_function = __qtscript_self.property("standardPixmap");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("standardPixmap") & QScriptValue::QObjectMember)) {
        qFatal("QStyle::standardPixmap() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QPixmap >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, standardPixmap)
            << qScriptValueFromValue(_q_engine, const_cast<const QStyleOption *>(opt))
            << qScriptValueFromValue(_q_engine, const_cast<const QWidget *>(widget))));
    }
}

int  QtScriptShell_QStyle::styleHint(QStyle::StyleHint  stylehint, const QStyleOption*  opt, const QWidget*  widget, QStyleHintReturn*  returnData) const
{
    QScriptValue _q_function = __qtscript_self.property("styleHint");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("styleHint") & QScriptValue::QObjectMember)) {
        qFatal("QStyle::styleHint() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<int >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, stylehint)
            << qScriptValueFromValue(_q_engine, const_cast<const QStyleOption *>(opt))
            << qScriptValueFromValue(_q_engine, const_cast<const QWidget *>(widget))
            << qScriptValueFromValue(_q_engine, returnData)));
    }
}

QRect  QtScriptShell_QStyle::subControlRect(QStyle::ComplexControl  cc, const QStyleOptionComplex*  opt, QStyle::SubControl  sc, const QWidget*  widget) const
{
    QScriptValue _q_function = __qtscript_self.property("subControlRect");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("subControlRect") & QScriptValue::QObjectMember)) {
        qFatal("QStyle::subControlRect() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QRect >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, cc)
            << qScriptValueFromValue(_q_engine, const_cast<const QStyleOptionComplex *>(opt))
            << qScriptValueFromValue(_q_engine, sc)
            << qScriptValueFromValue(_q_engine, const_cast<const QWidget *>(widget))));
    }
}

QRect  QtScriptShell_QStyle::subElementRect(QStyle::SubElement  subElement, const QStyleOption*  option, const QWidget*  widget) const
{
    QScriptValue _q_function = __qtscript_self.property("subElementRect");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("subElementRect") & QScriptValue::QObjectMember)) {
        qFatal("QStyle::subElementRect() is abstract!");
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        return qscriptvalue_cast<QRect >(_q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, subElement)
            << qScriptValueFromValue(_q_engine, const_cast<const QStyleOption *>(option))
            << qScriptValueFromValue(_q_engine, const_cast<const QWidget *>(widget))));
    }
}

void QtScriptShell_QStyle::timerEvent(QTimerEvent*  event)
{
    QScriptValue _q_function = __qtscript_self.property("timerEvent");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("timerEvent") & QScriptValue::QObjectMember)) {
        QStyle::timerEvent(event);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, event));
    }
}

void QtScriptShell_QStyle::unpolish(QApplication*  application)
{
    QScriptValue _q_function = __qtscript_self.property("unpolish");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("unpolish") & QScriptValue::QObjectMember)) {
        QStyle::unpolish(application);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, application));
    }
}

void QtScriptShell_QStyle::unpolish(QWidget*  widget)
{
    QScriptValue _q_function = __qtscript_self.property("unpolish");
    if (!_q_function.isFunction() || QTSCRIPT_IS_GENERATED_FUNCTION(_q_function)
        || (__qtscript_self.propertyFlags("unpolish") & QScriptValue::QObjectMember)) {
        QStyle::unpolish(widget);
    } else {
        QScriptEngine *_q_engine = __qtscript_self.engine();
        _q_function.call(__qtscript_self,
            QScriptValueList()
            << qScriptValueFromValue(_q_engine, widget));
    }
}

