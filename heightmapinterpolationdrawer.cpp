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
    glColor3f(0.0, 0.0, 1.0);

    int xPoints = m_data->at(0).count();
    int yPoints = m_data->count();

    double gridX = xPoints > 1 ? m_borderRect.width() / (xPoints - 1) : 0;
    double gridY = yPoints > 1 ? m_borderRect.height() / (yPoints - 1) : 0;

//    glBegin(GL_POINTS);
//    for (int i = 0; i < yPoints; i++) {
//        for (int j = 0; j < xPoints; j++) {
//            glVertex3f(m_borderRect.x() + gridX * j, m_borderRect.y() + gridY * i, m_data->at(i).at(j));
//        }
//    }
//    glEnd();

    for (int i = 0; i < yPoints; i++) {
        glBegin(GL_LINE_STRIP);
        for (int j = 0; j < xPoints; j++) {
            glVertex3f(m_borderRect.x() + gridX * j, m_borderRect.y() + gridY * i, m_data->at(i).at(j));
        }
        glEnd();
    }

    for (int j = 0; j < xPoints; j++) {
        glBegin(GL_LINE_STRIP);
        for (int i = 0; i < yPoints; i++) {
            glVertex3f(m_borderRect.x() + gridX * j, m_borderRect.y() + gridY * i, m_data->at(i).at(j));
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





