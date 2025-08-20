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
    vertex.position = m_endPosition;
    vertex.data = QVector3D(m_pointSize, 0, 0);
    m_points.append(vertex);

    return true;
}

QVector3D SelectionDrawer::endPosition() const
{
    return m_endPosition;
}

void SelectionDrawer::setEndPosition(const QVector3D &endPosition)
{
    m_endPosition = endPosition;
}

QColor SelectionDrawer::color() const
{
    return m_color;
}

void SelectionDrawer::setColor(const QColor &color)
{
    m_color = color;
}

QVector3D SelectionDrawer::startPosition() const
{
    return m_startPosition;
}

void SelectionDrawer::setStartPosition(const QVector3D &startPosition)
{
    m_startPosition = startPosition;
}
