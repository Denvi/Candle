// This file is a part of "Candle" application.
// Copyright 2015-2016 Hayrullin Denis Ravilevich

#include "heightmapborderdrawer.h"

HeightMapBorderDrawer::HeightMapBorderDrawer()
{
}

QRectF HeightMapBorderDrawer::borderRect() const
{
    return m_borderRect;
}

void HeightMapBorderDrawer::setBorderRect(const QRectF &borderRect)
{
    m_borderRect = borderRect;
    update();
}

bool HeightMapBorderDrawer::updateData()
{
    m_lines = {
        {QVector3D(m_borderRect.x(), m_borderRect.y(), 0), QVector3D(1.0, 0.0, 0.0), QVector3D(sNan, sNan, sNan)},
        {QVector3D(m_borderRect.x(), m_borderRect.y() + m_borderRect.height(), 0), QVector3D(1.0, 0.0, 0.0), QVector3D(sNan, sNan, sNan)},
        {QVector3D(m_borderRect.x(), m_borderRect.y() + m_borderRect.height(), 0), QVector3D(1.0, 0.0, 0.0), QVector3D(sNan, sNan, sNan)},
        {QVector3D(m_borderRect.x() + m_borderRect.width(), m_borderRect.y() + m_borderRect.height(), 0), QVector3D(1.0, 0.0, 0.0), QVector3D(sNan, sNan, sNan)},
        {QVector3D(m_borderRect.x() + m_borderRect.width(), m_borderRect.y() + m_borderRect.height(), 0), QVector3D(1.0, 0.0, 0.0), QVector3D(sNan, sNan, sNan)},
        {QVector3D(m_borderRect.x() + m_borderRect.width(), m_borderRect.y(), 0), QVector3D(1.0, 0.0, 0.0), QVector3D(sNan, sNan, sNan)},
        {QVector3D(m_borderRect.x() + m_borderRect.width(), m_borderRect.y(), 0), QVector3D(1.0, 0.0, 0.0), QVector3D(sNan, sNan, sNan)},
        {QVector3D(m_borderRect.x(), m_borderRect.y(), 0), QVector3D(1.0, 0.0, 0.0), QVector3D(sNan, sNan, sNan)},
    };
    return true;
}


