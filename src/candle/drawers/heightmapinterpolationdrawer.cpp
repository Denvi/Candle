// This file is a part of "Candle" application.
// Copyright 2015-2016 Hayrullin Denis Ravilevich

#include "heightmapinterpolationdrawer.h"

HeightMapInterpolationDrawer::HeightMapInterpolationDrawer()
{
    m_data = NULL;
}

bool HeightMapInterpolationDrawer::updateData()
{
    // Check if data is present
    if (!m_data || m_data->count() == 0) {
        m_lines.clear();
        return true;
    }

    QColor color;

    // Clear data
    m_lines.clear();

    // Prepare vertex
    VertexData vertex;
    vertex.start = QVector3D(sNan, sNan, sNan);

    // Calculate grid parameters
    int interpolationPointsX = m_data->at(0).count();
    int interpolationPointsY = m_data->count();

    double interpolationStepX = interpolationPointsX > 1 ? m_borderRect.width() / (interpolationPointsX - 1) : 0;
    double interpolationStepY = interpolationPointsY > 1 ? m_borderRect.height() / (interpolationPointsY - 1) : 0;

    // Find min & max values for coloring
    double min = m_data->at(0).at(0);
    double max = min;

    for (int i = 0; i < interpolationPointsY; i++) {
        for (int j = 0; j < interpolationPointsX; j++) {
            min = Util::nMin(min, m_data->at(i).at(j));
            max = Util::nMax(max, m_data->at(i).at(j));
        }
    }

    // Horizontal lines
    for (int i = 0; i < interpolationPointsY; i++) {
        for (int j = 1; j < interpolationPointsX; j++) {
            if (qIsNaN(m_data->at(i).at(j))) continue;
            color.setHsvF(0.67 * (max - m_data->at(i).at(j - 1)) / (max - min), 1.0, 1.0);
            vertex.color = QVector3D(color.redF(), color.greenF(), color.blueF());

            vertex.position = QVector3D(m_borderRect.x() + interpolationStepX * (j - 1), m_borderRect.y() + interpolationStepY * i, m_data->at(i).at(j - 1));
            m_lines.append(vertex);

            color.setHsvF(0.67 * (max - m_data->at(i).at(j)) / (max - min), 1.0, 1.0);
            vertex.color = QVector3D(color.redF(), color.greenF(), color.blueF());

            vertex.position = QVector3D(m_borderRect.x() + interpolationStepX * j, m_borderRect.y() + interpolationStepY * i, m_data->at(i).at(j));
            m_lines.append(vertex);
        }
    }

    // Vertical lines
    for (int j = 0; j < interpolationPointsX; j++) {
        for (int i = 1; i < interpolationPointsY; i++) {
            if (qIsNaN(m_data->at(i).at(j))) continue;
            color.setHsvF(0.67 * (max - m_data->at(i - 1).at(j)) / (max - min), 1.0, 1.0);
            vertex.color = QVector3D(color.redF(), color.greenF(), color.blueF());

            vertex.position = QVector3D(m_borderRect.x() + interpolationStepX * j, m_borderRect.y() + interpolationStepY * (i - 1), m_data->at(i - 1).at(j));
            m_lines.append(vertex);

            color.setHsvF(0.67 * (max - m_data->at(i).at(j)) / (max - min), 1.0, 1.0);
            vertex.color = QVector3D(color.redF(), color.greenF(), color.blueF());

            vertex.position = QVector3D(m_borderRect.x() + interpolationStepX * j, m_borderRect.y() + interpolationStepY * i, m_data->at(i).at(j));
            m_lines.append(vertex);
        }
    }

    return true;
}

QVector<QVector<double> > *HeightMapInterpolationDrawer::data() const
{
    return m_data;
}

void HeightMapInterpolationDrawer::setData(QVector<QVector<double> > *data)
{
    m_data = data;
    update();
}
QRectF HeightMapInterpolationDrawer::borderRect() const
{
    return m_borderRect;
}

void HeightMapInterpolationDrawer::setBorderRect(const QRectF &borderRect)
{
    m_borderRect = borderRect;
}




