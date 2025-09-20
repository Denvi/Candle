// This file is a part of "Candle" application.
// Copyright 2015-2025 Hayrullin Denis Ravilevich

#include "machineboundsdrawer.h"

MachineBoundsDrawer::MachineBoundsDrawer()
{
    m_pointSize = 4;
    m_gridSize = QSizeF(10, 10);
    m_borderRect = QRectF(0, 0, 1, 1);
}

bool MachineBoundsDrawer::updateData()
{
    // Clear data
    m_lines.clear();

    // Color
    QVector3D shadowColor(0.9f, 0.9f, 0.9f);
    QVector3D mainColor(0.5f, 0.5f, 0.5f);

    // Border
    m_lines = {
        // Inner
        {QVector3D(0, 0, 0), mainColor, QVector3D(), VertexDataTypeLine},
        {QVector3D(0, 0 + m_borderRect.height(), 0), mainColor, QVector3D(), VertexDataTypeLine},

        {QVector3D(0, 0 + m_borderRect.height(), 0), mainColor, QVector3D(), VertexDataTypeLine},
        {QVector3D(0 + m_borderRect.width(), 0 + m_borderRect.height(), 0), mainColor, QVector3D(), VertexDataTypeLine},

        {QVector3D(0 + m_borderRect.width(), 0 + m_borderRect.height(), 0), mainColor, QVector3D(), VertexDataTypeLine},
        {QVector3D(0 + m_borderRect.width(), 0, 0), mainColor, QVector3D(), VertexDataTypeLine},

        {QVector3D(0 + m_borderRect.width(), 0, 0), mainColor, QVector3D(), VertexDataTypeLine},
        {QVector3D(0, 0, 0), mainColor, QVector3D(), VertexDataTypeLine},

        // Outer
        {QVector3D(-5, -5, 0), shadowColor, QVector3D(), VertexDataTypeLine},
        {QVector3D(-5, 5 + m_borderRect.height(), 0), shadowColor, QVector3D(), VertexDataTypeLine},

        {QVector3D(-5, 5 + m_borderRect.height(), 0), shadowColor, QVector3D(), VertexDataTypeLine},
        {QVector3D(5 + m_borderRect.width(), 5 + m_borderRect.height(), 0), shadowColor, QVector3D(), VertexDataTypeLine},

        {QVector3D(5 + m_borderRect.width(), 5 + m_borderRect.height(), 0), shadowColor, QVector3D(), VertexDataTypeLine},
        {QVector3D(5 + m_borderRect.width(), -5, 0), shadowColor, QVector3D(), VertexDataTypeLine},

        {QVector3D(5 + m_borderRect.width(), -5, 0), shadowColor, QVector3D(), VertexDataTypeLine},
        {QVector3D(-5, -5, 0), shadowColor, QVector3D(), VertexDataTypeLine},
    };

    // Grid
    for (int i = 1; i < m_borderRect.width() / 10; i++)
    {
        m_lines.append(
            VertexData{QVector3D(i * 10, 0, 0), shadowColor, QVector3D(), VertexDataTypeLine}
        );
        m_lines.append(
            VertexData{QVector3D(i * 10, m_borderRect.height(), 0), shadowColor, QVector3D(), VertexDataTypeLine}
        );
    }

    for (int i = 1; i < m_borderRect.height() / 10; i++)
    {
        m_lines.append(
            VertexData{QVector3D(0, i * 10, 0), shadowColor, QVector3D(), VertexDataTypeLine}
        );
        m_lines.append(
            VertexData{QVector3D(m_borderRect.width(), i * 10, 0), shadowColor, QVector3D(), VertexDataTypeLine}
        );
    }

    return true;
}

QSizeF MachineBoundsDrawer::gridSize() const
{
    return m_gridSize;
}

void MachineBoundsDrawer::setGridSize(const QSizeF &gridSize)
{
    m_gridSize = gridSize;
    update();
}
QRectF MachineBoundsDrawer::borderRect() const
{
    return m_borderRect;
}

void MachineBoundsDrawer::setBorderRect(const QRectF &borderRect)
{
    m_borderRect = borderRect;
    update();
}

QVector3D MachineBoundsDrawer::getMinimumExtremes()
{
    return QVector3D();
}

QVector3D MachineBoundsDrawer::getMaximumExtremes()
{
    return QVector3D(m_borderRect.width(), m_borderRect.height(), 0);
}
