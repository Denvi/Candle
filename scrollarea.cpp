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

//    this->setMouseTracking(true);
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
        connect(box, SIGNAL(mousePressed()), this, SLOT(onPressed()));
        m_width = qMax<int>(m_width, box->sizeHint().width() + box->layout()->contentsMargins().left() + 4); // 1 * margin
    }   

    QScrollArea::setWidget(widget);
}

void ScrollArea::resizeEvent(QResizeEvent *re)
{
    updateBorders();
}

void ScrollArea::mouseMoveEvent(QMouseEvent *me)
{
    QPoint delta = me->globalPos() - m_pressedPos;
    onScroll(delta.x(), delta.y());
}

void ScrollArea::mousePressEvent(QMouseEvent *me)
{
    m_pressedPos = me->globalPos();
    m_pressedValue = this->verticalScrollBar()->value();
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
    int delta = (double)dy / (this->sizeHint().height() - this->height()) * (bar->maximum() - bar->minimum());

    bar->setValue(m_pressedValue - delta);
}

void ScrollArea::onPressed()
{
    m_pressedValue = this->verticalScrollBar()->value();
}

void ScrollArea::updateBorders()
{
// Performance issue on changing stylesheet
#ifdef GLES
    return;
#else

    QScrollBar* bar = this->verticalScrollBar();
    bool fitted = this->geometry().height() > this->widget()->sizeHint().height();

    this->styleSheet().clear();

    QString style = QString("QScrollArea {background-color: transparent; border-top: 2px solid %1; border-bottom: 2px solid %2;}")
            .arg(bar->value() > bar->minimum() && !fitted ? "qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:1 #D5DFE5, stop:0 white)"
                                                          : "transparent")
            .arg(bar->value() < bar->maximum() && !fitted ? "qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:1 #D5DFE5, stop:0 white)"
                                                          : "transparent");

    this->setStyleSheet(style);
#endif
}
