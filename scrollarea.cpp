// This file is a part of "grblControl" application.
// Copyright 2015 Hayrullin Denis Ravilevich

#include <QDebug>
#include <QLayout>
#include <QScrollBar>
#include <QTimer>
#include <QMouseEvent>
#include "scrollarea.h"

ScrollArea::ScrollArea(QWidget *parent) : QScrollArea(parent)
{
    m_update = false;
    m_width = 0;

    connect(this->verticalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(onVerticalScrollBarValueChanged(int)));
    connect(this->verticalScrollBar(), SIGNAL(rangeChanged(int,int)), this, SLOT(onVerticalScrollBarRangeChanged(int,int)));

    this->setMouseTracking(true);
}

QSize ScrollArea::sizeHint() const
{
    QSize hint = widget()->sizeHint();
    hint.setHeight(hint.height() + 4);  // top + bottom border width
    hint.setWidth(m_width);

    return hint;
}

void ScrollArea::setWidget(QWidget *widget)
{
    connect(static_cast<Widget*>(widget), SIGNAL(sizeChanged(QSize)), this, SLOT(onContentSizeChanged(QSize)));

    QList<GroupBox*> list = widget->findChildren<GroupBox*>();
    foreach (GroupBox *box, list) {
        connect(box, SIGNAL(mouseMoved(int,int)), this, SLOT(onScroll(int,int)));
        m_width = qMax<int>(m_width, box->sizeHint().width() + box->layout()->contentsMargins().left()); // 1 * margin
    }   

    QScrollArea::setWidget(widget);
}

void ScrollArea::resizeEvent(QResizeEvent *re)
{
    updateBorders();
}

void ScrollArea::mouseMoveEvent(QMouseEvent *me)
{
    QPoint delta = me->globalPos() - m_previousPos;
    m_previousPos = me->globalPos();

    onScroll(delta.x(), delta.y());
}

void ScrollArea::mousePressEvent(QMouseEvent *me)
{
    m_previousPos = me->globalPos();
}

void ScrollArea::onContentSizeChanged(QSize newSize)
{
    this->widget()->setMinimumWidth(m_width);
    this->updateGeometry();
}

void ScrollArea::onVerticalScrollBarValueChanged(int newValue)
{
    updateBorders();
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

    QString style = QString("QScrollArea {border-top: 2px solid %1; border-bottom: 2px solid %2;}")
            .arg(bar->value() > bar->minimum() && !fitted ? "qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:1 #D5DFE5, stop:0 white)"
                                                          : "transparent")
            .arg(bar->value() < bar->maximum() && !fitted ? "qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:1 #D5DFE5, stop:0 white)"
                                                          : "transparent");

    this->setStyleSheet(style);
}
