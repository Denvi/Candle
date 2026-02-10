// This file is a part of "Candle" application.
// Copyright 2015-2025 Hayrullin Denis Ravilevich

#include "selectiondrawer.h"

SelectionDrawer::SelectionDrawer()
{
}

void SelectionDrawer::drawPainter(QPainter &painter, const QMatrix4x4 &projection, double ratio)
{
    static auto polygon = QPolygon({ QPoint(0, 0), QPoint(-4, 32), QPoint(4, 32), QPoint(0, 0) });

    painter.translate((projection * m_position).toPoint());
    painter.scale(1, -1);

    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(QPen(m_color));
    painter.setBrush(QBrush(m_color));
    painter.drawPolygon(polygon);
}

QColor SelectionDrawer::color() const
{
    return m_color;
}

void SelectionDrawer::setColor(const QColor &color)
{
    m_color = color;
}

const QVector3D &SelectionDrawer::position()
{
    return m_position;
}

void SelectionDrawer::setPosition(const QVector3D &position)
{
    m_position = position;
}