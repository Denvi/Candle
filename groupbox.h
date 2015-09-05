// This file is a part of "grblControl" application.
// Copyright 2015 Hayrullin Denis Ravilevich

#ifndef GROUPBOX_H
#define GROUPBOX_H

#include <QWidget>
#include <QGroupBox>

class GroupBox : public QGroupBox
{
    Q_OBJECT
public:
    explicit GroupBox(QWidget *parent = 0);

signals:
    void mouseMoved(int dx, int dy);
    void mousePressed();

protected:
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);

private:
    QPoint m_pressedPos;
};

#endif // GROUPBOX_H
