// This file is a part of "grblControl" application.
// Copyright 2015 Hayrullin Denis Ravilevich

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

    QPoint delta = event->globalPos() - m_pressedPos;

    emit mouseMoved(delta.x(), delta.y());
}

void GroupBox::mousePressEvent(QMouseEvent *event)
{
    QGroupBox::mousePressEvent(event);
    m_pressedPos = event->globalPos();

    emit mousePressed();
}

