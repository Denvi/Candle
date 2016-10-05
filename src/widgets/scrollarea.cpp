// This file is a part of "Candle" application.
// Copyright 2015-2016 Hayrullin Denis Ravilevich

#include <QDebug>
#include <QLayout>
#include <QScrollBar>
#include <QTimer>
#include <QMouseEvent>
#include <QStyle>
#include "scrollarea.h"

ScrollArea::ScrollArea(QWidget *parent) : QScrollArea(parent)
{
    m_update = false;
    m_width = 0;

    this->setStyleSheet("QScrollArea {border-top: 2px solid transparent; border-bottom: 2px solid transparent;}\
                        QScrollArea[topBorder=\"true\"] {border-top: 2px solid qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:1 #D5DFE5, stop:0 white);}\
                        QScrollArea[bottomBorder=\"true\"] {border-bottom: 2px solid qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:1 #D5DFE5, stop:0 white);}");

    this->verticalScrollBar()->setStyleSheet("QScrollBar:vertical {border: none; width: 2px; padding-top: 8px;}\
                                             QScrollBar::handle:vertical {background: darkgray;}\
                                             QScrollBar::add-line:vertical {border: none; background: none; height: 0px;}\
                                             QScrollBar::sub-line:vertical {border: none; background: none; height: 0px;}");

    connect(this->verticalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(onVerticalScrollBarValueChanged(int)));
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
    QScrollArea::setWidget(widget);
}

void ScrollArea::updateMinimumWidth()
{
    m_width = 0;
    QList<GroupBox*> list = this->widget()->findChildren<GroupBox*>();
    foreach (GroupBox *box, list) {
        connect(box, SIGNAL(mouseMoved(int,int)), this, SLOT(onScroll(int,int)));
        connect(box, SIGNAL(mousePressed()), this, SLOT(onPressed()));
        m_width = qMax<int>(m_width, box->sizeHint().width()
                        + static_cast<QWidget*>(box->parent())->layout()->contentsMargins().left()
                        + static_cast<QWidget*>(box->parent())->layout()->contentsMargins().right()); // 1 * margin
    }
    onContentSizeChanged(QSize());
}

void ScrollArea::resizeEvent(QResizeEvent *re)
{
    QScrollArea::resizeEvent(re);

    updateBorders();
}

void ScrollArea::mouseMoveEvent(QMouseEvent *me)
{
    QScrollArea::mouseMoveEvent(me);

    if (!m_pressedPos.isNull()) {
        QPoint delta = me->globalPos() - m_pressedPos;
        onScroll(delta.x(), delta.y());
    }
}

void ScrollArea::mousePressEvent(QMouseEvent *me)
{
    QScrollArea::mousePressEvent(me);

    m_pressedPos = me->globalPos();
    m_pressedValue = this->verticalScrollBar()->value();
}

void ScrollArea::mouseReleaseEvent(QMouseEvent *me)
{
    QScrollArea::mouseReleaseEvent(me);

    m_pressedPos = QPoint();
}

void ScrollArea::onContentSizeChanged(QSize newSize)
{
    Q_UNUSED(newSize)

    this->widget()->setMinimumWidth(m_width);
    this->updateGeometry();
}

void ScrollArea::onVerticalScrollBarValueChanged(int newValue)
{
    Q_UNUSED(newValue)

    updateBorders();
}

void ScrollArea::onScroll(int dx, int dy)
{
    Q_UNUSED(dx)

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

    this->setProperty("topBorder", bar->value() > bar->minimum() && !fitted);
    this->setProperty("bottomBorder", bar->value() < bar->maximum() && !fitted);

    style()->unpolish(this);
    this->ensurePolished();
#endif
}
