// This file is a part of "Candle" application.
// Copyright 2015-2016 Hayrullin Denis Ravilevich

#ifndef SCROLLAREA_H
#define SCROLLAREA_H

#include <QWidget>
#include <QScrollArea>
#include "widget.h"
#include "groupbox.h"

class ScrollArea : public QScrollArea
{
    Q_OBJECT

public:
    explicit ScrollArea(QWidget *parent = 0);

    QSize sizeHint() const;
    void setWidget(QWidget *widget);
    void updateMinimumWidth();

public slots:

signals:
    void sizeHintRequest();

protected:
    void resizeEvent(QResizeEvent *re);
    void mouseMoveEvent(QMouseEvent *me);
    void mousePressEvent(QMouseEvent *me);
    void mouseReleaseEvent(QMouseEvent *me);

private slots:
    void onContentSizeChanged(QSize newSize);
    void onVerticalScrollBarValueChanged(int newValue);
    void onScroll(int dx, int dy);
    void onPressed();

private:
    bool m_update;
    QPoint m_pressedPos;
    int m_pressedValue;
    int m_width;

    void updateBorders();
};

#endif // SCROLLAREA_H
