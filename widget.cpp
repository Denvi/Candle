// This file is a part of "grblControl" application.
// Copyright 2015 Hayrullin Denis Ravilevich

#include <QResizeEvent>
#include <QDebug>
#include "widget.h"

Widget::Widget(QWidget *parent) : QWidget(parent)
{

}

void Widget::resizeEvent(QResizeEvent *re)
{
    emit sizeChanged(re->size());
}

