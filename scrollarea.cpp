#include <QDebug>
#include <QLayout>
#include <QScrollBar>
#include <QTimer>
#include <QMouseEvent>
#include "scrollarea.h"

ScrollArea::ScrollArea(QWidget *parent) : QScrollArea(parent)
{
    m_update = false;

    connect(this->verticalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(onVerticalScrollBarValueChanged(int)));
    connect(this->verticalScrollBar(), SIGNAL(rangeChanged(int,int)), this, SLOT(onVerticalScrollBarRangeChanged(int,int)));

    this->setMouseTracking(true);
}

QSize ScrollArea::sizeHint() const
{
    QSize hint = widget()->sizeHint();
    hint.setHeight(hint.height() + 2);

    return hint;
}

void ScrollArea::setWidget(QWidget *widget)
{
    connect(static_cast<Widget*>(widget), SIGNAL(sizeChanged(QSize)), this, SLOT(onContentSizeChanged(QSize)));

    QList<GroupBox*> list = widget->findChildren<GroupBox*>();
    foreach (GroupBox *box, list) {
        connect(box, SIGNAL(mouseMoved(int,int)), this, SLOT(onScroll(int,int)));
    }

    QScrollArea::setWidget(widget);
}

void ScrollArea::resizeEvent(QResizeEvent *re)
{
    updateBorders();
}

void ScrollArea::mouseMoveEvent(QMouseEvent *me)
{
    if (me->buttons() & Qt::LeftButton != 0) {
    }
}

void ScrollArea::onContentSizeChanged(QSize newSize)
{
    this->updateGeometry();
}

void ScrollArea::onVerticalScrollBarValueChanged(int newValue)
{
    updateBorders();
}

void ScrollArea::onVerticalScrollBarRangeChanged(int, int)
{
    if (m_update) {
        m_update = false;
    }
}

void ScrollArea::onScroll(int dx, int dy)
{
    QScrollBar *bar = this->verticalScrollBar();
    int delta = (double)dy / this->height() * (bar->maximum() - bar->minimum());

    bar->setValue(bar->value() - delta);
}

void ScrollArea::updateBorders()
{
    QScrollBar* bar = this->verticalScrollBar();
    bool fitted = this->geometry().height() > this->widget()->sizeHint().height();

    this->styleSheet().clear();

    QString style = QString("QScrollArea {border-top: 1px solid %1; border-bottom: 1px solid %2;}")
            .arg(bar->value() > bar->minimum() && !fitted ? "palette(midlight)" : "transparent")
            .arg(bar->value() < bar->maximum() && !fitted ? "palette(midlight)" : "transparent");

    this->setStyleSheet(style);
}
