#include "heightmapinterpolationdrawer.h"

HeightMapInterpolationDrawer::HeightMapInterpolationDrawer(QObject *parent) : GLDrawable(parent)
{
    m_data = NULL;
}

void HeightMapInterpolationDrawer::draw()
{
    if (!m_visible || m_data == NULL) return;

    glLineWidth(m_lineWidth);
    glPointSize(4);
    glColor3f(0.0, 0.8, 0.0);

    int interpolationPointsX = m_data->at(0).count();
    int interpolationPointsY = m_data->count();

    double interpolationStepX = interpolationPointsX > 1 ? m_borderRect.width() / (interpolationPointsX - 1) : 0;
    double interpolationStepY = interpolationPointsY > 1 ? m_borderRect.height() / (interpolationPointsY - 1) : 0;

    double min = m_data->at(0).at(0);
    double max = min;

    for (int i = 0; i < interpolationPointsY; i++) {
        for (int j = 0; j < interpolationPointsX; j++) {
            min = Util::nMin(min, m_data->at(i).at(j));
            max = Util::nMax(max, m_data->at(i).at(j));
        }
    }

    QColor color;

//    glBegin(GL_POINTS);
//    for (int i = 0; i < yPoints; i++) {
//        for (int j = 0; j < xPoints; j++) {
//            glVertex3f(m_borderRect.x() + gridX * j, m_borderRect.y() + gridY * i, m_data->at(i).at(j));
//        }
//    }
//    glEnd();
    m_linesCount = 0;

    for (int i = 0; i < interpolationPointsY; i++) {
        glBegin(GL_LINE_STRIP);
        for (int j = 0; j < interpolationPointsX; j++) {
            if (std::isnan(m_data->at(i).at(j))) continue;
            m_linesCount++;
            color.setHsvF(0.67 * (max - m_data->at(i).at(j)) / (max - min), 1.0, 1.0);
            glColor3f(color.redF(), color.greenF(), color.blueF());
            glVertex3f(m_borderRect.x() + interpolationStepX * j, m_borderRect.y() + interpolationStepY * i, m_data->at(i).at(j));
        }
        glEnd();
    }

    for (int j = 0; j < interpolationPointsX; j++) {
        glBegin(GL_LINE_STRIP);
        for (int i = 0; i < interpolationPointsY; i++) {
            if (std::isnan(m_data->at(i).at(j))) continue;
            m_linesCount++;
            color.setHsvF(0.67 * (max - m_data->at(i).at(j)) / (max - min), 1.0, 1.0);
            glColor3f(color.redF(), color.greenF(), color.blueF());
            glVertex3f(m_borderRect.x() + interpolationStepX * j, m_borderRect.y() + interpolationStepY * i, m_data->at(i).at(j));
        }
        glEnd();
    }
}

QVector<QVector<double> > *HeightMapInterpolationDrawer::data() const
{
    return m_data;
}

void HeightMapInterpolationDrawer::setData(QVector<QVector<double> > *data)
{
    m_data = data;
}
QRectF HeightMapInterpolationDrawer::borderRect() const
{
    return m_borderRect;
}

void HeightMapInterpolationDrawer::setBorderRect(const QRectF &borderRect)
{
    m_borderRect = borderRect;
}

int HeightMapInterpolationDrawer::getLinesCount()
{
    return m_linesCount;
}





