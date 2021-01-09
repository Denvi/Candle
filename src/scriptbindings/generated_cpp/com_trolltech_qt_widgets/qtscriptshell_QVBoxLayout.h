#ifndef QTSCRIPTSHELL_QVBOXLAYOUT_H
#define QTSCRIPTSHELL_QVBOXLAYOUT_H

#include <qboxlayout.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QVBoxLayout : public QVBoxLayout
{
public:
    QtScriptShell_QVBoxLayout();
    QtScriptShell_QVBoxLayout(QWidget*  parent);
    ~QtScriptShell_QVBoxLayout();

    void addItem(QLayoutItem*  arg__1);
    void childEvent(QChildEvent*  e);
    QSizePolicy::ControlTypes  controlTypes() const;
    int  count() const;
    void customEvent(QEvent*  event);
    bool  event(QEvent*  event);
    bool  eventFilter(QObject*  watched, QEvent*  event);
    Qt::Orientations  expandingDirections() const;
    QRect  geometry() const;
    bool  hasHeightForWidth() const;
    int  heightForWidth(int  arg__1) const;
    int  indexOf(QWidget*  arg__1) const;
    void invalidate();
    bool  isEmpty() const;
    QLayoutItem*  itemAt(int  arg__1) const;
    QLayout*  layout();
    QSize  maximumSize() const;
    int  minimumHeightForWidth(int  arg__1) const;
    QSize  minimumSize() const;
    void setGeometry(const QRect&  arg__1);
    QSize  sizeHint() const;
    QSpacerItem*  spacerItem();
    QLayoutItem*  takeAt(int  arg__1);
    void timerEvent(QTimerEvent*  event);
    QWidget*  widget();

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QVBOXLAYOUT_H
