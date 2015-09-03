// This file is a part of "grblControl" application.
// Copyright 2015 Hayrullin Denis Ravilevich

#include "heightmapborderdrawer.h"

HeightMapBorderDrawer::HeightMapBorderDrawer(QObject *parent) : GLDrawable(parent)
{

}

void HeightMapBorderDrawer::draw()
{
    if (!m_visible) return;

    glLineWidth(m_lineWidth);
    glColor3f(1.0, 0.0, 0.0);

    glBegin(GL_LINE_LOOP);
    glVertex3f(m_borderRect.x(), m_borderRect.y(), 0);
    glVertex3f(m_borderRect.x(), m_borderRect.y() + m_borderRect.height(), 0);
    glVertex3f(m_borderRect.x() + m_borderRect.width(), m_borderRect.y() + m_borderRect.height(), 0);
    glVertex3f(m_borderRect.x() + m_borderRect.width(), m_borderRect.y(), 0);
    glVertex3f(m_borderRect.x(), m_borderRect.y(), 0);
    glEnd();
}

QRectF HeightMapBorderDrawer::borderRect() const
{
    return m_borderRect;
}

void HeightMapBorderDrawer::setBorderRect(const QRectF &borderRect)
{
    m_borderRect = borderRect;
}

int HeightMapBorderDrawer::getLinesCount()
{
    return 4;
}


