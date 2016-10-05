// This file is a part of "Candle" application.
// Copyright 2015-2016 Hayrullin Denis Ravilevich

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

