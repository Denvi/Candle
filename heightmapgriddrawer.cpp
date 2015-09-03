// This file is a part of "grblControl" application.
// Copyright 2015 Hayrullin Denis Ravilevich

#include "heightmapgriddrawer.h"

HeightMapGridDrawer::HeightMapGridDrawer(QObject *parent) : GLDrawable(parent)
{
    m_model = NULL;
}

void HeightMapGridDrawer::draw()
{
    if (!m_visible || m_model == NULL) return;

    glLineWidth(m_lineWidth);
    glPointSize(4);
//    glColor3f(1.0, 0.6, 0.0);

    int gridPointsX = m_model->columnCount();
    int gridPointsY = m_model->rowCount();

    double gridStepX = gridPointsX > 1 ? m_borderRect.width() / (gridPointsX - 1) : 0;
    double gridStepY = gridPointsY > 1 ? m_borderRect.height() / (gridPointsY - 1) : 0;

    m_linesCount = 0;

    for (int i = 0; i < gridPointsY; i++) {
        for (int j = 0; j < gridPointsX; j++) {
            if (m_model == NULL || std::isnan(m_model->data(m_model->index(i, j), Qt::UserRole).toDouble())) {
                glBegin(GL_LINES);
                m_linesCount++;
                glColor3f(1.0, 0.6, 0.0);
                glVertex3f(m_borderRect.x() + gridStepX * j, m_borderRect.y() + gridStepY * i, m_zTop);
                glVertex3f(m_borderRect.x() + gridStepX * j, m_borderRect.y() + gridStepY * i, m_zBottom);
                glEnd();
            } else {
                glBegin(GL_POINTS);                
                glColor3f(0.0, 0.0, 1.0);
                glVertex3f(m_borderRect.x() + gridStepX * j, m_borderRect.y() + gridStepY * i, m_model->data(m_model->index(i, j), Qt::UserRole).toDouble());
                glEnd();
            }
        }
    }

    glColor3f(0.0, 0.0, 1.0);

    for (int i = 0; i < gridPointsY; i++) {
        glBegin(GL_LINE_STRIP);
        for (int j = 0; j < gridPointsX; j++) {
            if (std::isnan(m_model->data(m_model->index(i, j), Qt::UserRole).toDouble())) continue;
            m_linesCount++;
            glVertex3f(m_borderRect.x() + gridStepX * j, m_borderRect.y() + gridStepY * i, m_model->data(m_model->index(i, j), Qt::UserRole).toDouble());
        }
        glEnd();
    }

    for (int j = 0; j < gridPointsX; j++) {
        glBegin(GL_LINE_STRIP);
        for (int i = 0; i < gridPointsY; i++) {
            if (std::isnan(m_model->data(m_model->index(i, j), Qt::UserRole).toDouble())) continue;
            m_linesCount++;
            glVertex3f(m_borderRect.x() + gridStepX * j, m_borderRect.y() + gridStepY * i, m_model->data(m_model->index(i, j), Qt::UserRole).toDouble());
        }
        glEnd();
    }
}

QPointF HeightMapGridDrawer::gridSize() const
{
    return m_gridSize;
}

void HeightMapGridDrawer::setGridSize(const QPointF &gridSize)
{
    m_gridSize = gridSize;
}
QRectF HeightMapGridDrawer::borderRect() const
{
    return m_borderRect;
}

void HeightMapGridDrawer::setBorderRect(const QRectF &borderRect)
{
    m_borderRect = borderRect;
}
double HeightMapGridDrawer::zTop() const
{
    return m_zTop;
}

void HeightMapGridDrawer::setZTop(double zTop)
{
    m_zTop = zTop;
}
double HeightMapGridDrawer::zBottom() const
{
    return m_zBottom;
}

void HeightMapGridDrawer::setZBottom(double zBottom)
{
    m_zBottom = zBottom;
}
QAbstractTableModel *HeightMapGridDrawer::model() const
{
    return m_model;
}

void HeightMapGridDrawer::setModel(QAbstractTableModel *model)
{
    m_model = model;
}

int HeightMapGridDrawer::getLinesCount()
{
    return m_linesCount;
}






