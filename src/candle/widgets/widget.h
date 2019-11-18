// This file is a part of "Candle" application.
// Copyright 2015-2016 Hayrullin Denis Ravilevich

#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class Widget : public QWidget
{
    Q_OBJECT
public:
    explicit Widget(QWidget *parent = 0);

signals:
    void sizeChanged(QSize newSize);

protected:
    void resizeEvent(QResizeEvent *);

public slots:
};

#endif // WIDGET_H
