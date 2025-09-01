// This file is a part of "Candle" application.
// Copyright 2015-2025 Hayrullin Denis Ravilevich

#include "selectiondrawer.h"

SelectionDrawer::SelectionDrawer()
{
    m_pointSize = 6.0;
}

bool SelectionDrawer::updateData()
{
    m_points.clear();

    VertexData vertex;
    vertex.type = VertexDataTypePoint;
    vertex.color = Util::colorToVector(m_color);
    vertex.position = m_position;
    vertex.data = QVector3D(m_pointSize, 0, 0);
    m_points.append(vertex);

    return true;
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
