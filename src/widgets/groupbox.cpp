// This file is a part of "Candle" application.
// Copyright 2015-2016 Hayrullin Denis Ravilevich

#include <QMouseEvent>
#include <QDebug>
#include <QCheckBox>
#include "groupbox.h"

GroupBox::GroupBox(QWidget *parent) : QGroupBox(parent)
{

}

void GroupBox::mouseMoveEvent(QMouseEvent *event)
{    
    QGroupBox::mouseMoveEvent(event);

    if (!m_pressedPos.isNull()) {
        QPoint delta = event->globalPos() - m_pressedPos;
        emit mouseMoved(delta.x(), delta.y());
    }
}

void GroupBox::mousePressEvent(QMouseEvent *event)
{
    QGroupBox::mousePressEvent(event);

    m_pressedPos = event->globalPos();
    emit mousePressed();
}

void GroupBox::mouseReleaseEvent(QMouseEvent *event)
{
    QGroupBox::mouseReleaseEvent(event);

    m_pressedPos = QPoint();
    emit mouseReleased();
}

void GroupBox::resizeEvent(QResizeEvent *event)
{
    QGroupBox::resizeEvent(event);
    emit resized(event->size());
}

