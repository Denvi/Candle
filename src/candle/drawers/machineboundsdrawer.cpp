// This file is a part of "Candle" application.
// Copyright 2015-2021 Hayrullin Denis Ravilevich

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

    // Border
    QRectF r = m_borderRect.translated(-m_offset);

    // Color
    QVector3D c(0.8, 0.8, 0.8);

    // Vertices
    m_lines
        << VertexData(QVector3D(r.x(), r.y(), 0), c, QVector3D(sNan, sNan, sNan))
        << VertexData(QVector3D(r.x(), r.y() + r.height(), 0), c, QVector3D(sNan, sNan, sNan))
        << VertexData(QVector3D(r.x(), r.y() + r.height(), 0), c, QVector3D(sNan, sNan, sNan))
        << VertexData(QVector3D(r.x() + r.width(), r.y() + r.height(), 0), c, QVector3D(sNan, sNan, sNan))
        << VertexData(QVector3D(r.x() + r.width(), r.y() + r.height(), 0), c, QVector3D(sNan, sNan, sNan))
        << VertexData(QVector3D(r.x() + r.width(), r.y(), 0), c, QVector3D(sNan, sNan, sNan))
        << VertexData(QVector3D(r.x() + r.width(), r.y(), 0), c, QVector3D(sNan, sNan, sNan))
        << VertexData(QVector3D(r.x(), r.y(), 0), c, QVector3D(sNan, sNan, sNan));

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

QPointF MachineBoundsDrawer::offset() const
{
    return m_offset;
}

void MachineBoundsDrawer::setOffset(const QPointF &offset)
{
    m_offset = offset;
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
