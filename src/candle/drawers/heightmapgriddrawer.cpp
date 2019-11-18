// This file is a part of "Candle" application.
// Copyright 2015-2016 Hayrullin Denis Ravilevich

#include "heightmapgriddrawer.h"

HeightMapGridDrawer::HeightMapGridDrawer()
{
    m_model = NULL;
    m_pointSize = 4;
}

bool HeightMapGridDrawer::updateData()
{
    // Clear data
    m_lines.clear();
    m_points.clear();

    // Prepare vertex
    VertexData vertex;
    vertex.start = QVector3D(sNan, sNan, m_pointSize);

    // Calculate grid parameters
    int gridPointsX = m_model->columnCount();
    int gridPointsY = m_model->rowCount();

    double gridStepX = gridPointsX > 1 ? m_borderRect.width() / (gridPointsX - 1) : 0;
    double gridStepY = gridPointsY > 1 ? m_borderRect.height() / (gridPointsY - 1) : 0;

    // Probe path / dots
    for (int i = 0; i < gridPointsY; i++) {
        for (int j = 0; j < gridPointsX; j++) {
            if (m_model == NULL || qIsNaN(m_model->data(m_model->index(i, j), Qt::UserRole).toDouble())) {
                vertex.color = QVector3D(1.0, 0.6, 0.0);
                vertex.position = QVector3D(m_borderRect.x() + gridStepX * j, m_borderRect.y() + gridStepY * i, m_zTop);
                m_lines.append(vertex);
                vertex.position = QVector3D(m_borderRect.x() + gridStepX * j, m_borderRect.y() + gridStepY * i, m_zBottom);
                m_lines.append(vertex);
            } else {
                vertex.color = QVector3D(0.0, 0.0, 1.0);
                vertex.position = QVector3D(m_borderRect.x() + gridStepX * j, m_borderRect.y() + gridStepY * i, m_model->data(m_model->index(i, j), Qt::UserRole).toDouble());
                m_points.append(vertex);
            }
        }
    }

    // Horizontal grid lines
    vertex.color = QVector3D(0.0, 0.0, 1.0);
    for (int i = 0; i < gridPointsY; i++) {
        for (int j = 1; j < gridPointsX; j++) {
            if (qIsNaN(m_model->data(m_model->index(i, j), Qt::UserRole).toDouble())) continue;

            vertex.position = QVector3D(m_borderRect.x() + gridStepX * (j - 1), m_borderRect.y() + gridStepY * i, m_model->data(m_model->index(i, j - 1), Qt::UserRole).toDouble());
            m_lines.append(vertex);

            vertex.position = QVector3D(m_borderRect.x() + gridStepX * j, m_borderRect.y() + gridStepY * i, m_model->data(m_model->index(i, j), Qt::UserRole).toDouble());
            m_lines.append(vertex);
        }
    }

    // Vertical grid lines
    vertex.color = QVector3D(0.0, 0.0, 1.0);
    for (int j = 0; j < gridPointsX; j++) {
        for (int i = 1; i < gridPointsY; i++) {
            if (qIsNaN(m_model->data(m_model->index(i, j), Qt::UserRole).toDouble())) continue;

            vertex.position = QVector3D(m_borderRect.x() + gridStepX * j, m_borderRect.y() + gridStepY * (i - 1), m_model->data(m_model->index(i - 1, j), Qt::UserRole).toDouble());
            m_lines.append(vertex);

            vertex.position = QVector3D(m_borderRect.x() + gridStepX * j, m_borderRect.y() + gridStepY * i, m_model->data(m_model->index(i, j), Qt::UserRole).toDouble());
            m_lines.append(vertex);
        }
    }

    return true;
}

QPointF HeightMapGridDrawer::gridSize() const
{
    return m_gridSize;
}

void HeightMapGridDrawer::setGridSize(const QPointF &gridSize)
{
    m_gridSize = gridSize;
    update();
}
QRectF HeightMapGridDrawer::borderRect() const
{
    return m_borderRect;
}

void HeightMapGridDrawer::setBorderRect(const QRectF &borderRect)
{
    m_borderRect = borderRect;
    update();
}

double HeightMapGridDrawer::zTop() const
{
    return m_zTop;
}

void HeightMapGridDrawer::setZTop(double zTop)
{
    m_zTop = zTop;
    update();
}
double HeightMapGridDrawer::zBottom() const
{
    return m_zBottom;
}

void HeightMapGridDrawer::setZBottom(double zBottom)
{
    m_zBottom = zBottom;
    update();
}

QAbstractTableModel *HeightMapGridDrawer::model() const
{
    return m_model;
}

void HeightMapGridDrawer::setModel(QAbstractTableModel *model)
{
    m_model = model;
    update();
}





