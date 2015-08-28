#include "heightmapgriddrawer.h"

HeightMapGridDrawer::HeightMapGridDrawer(QObject *parent) : GLDrawable(parent)
{

}

void HeightMapGridDrawer::draw()
{
    if (!m_visible) return;

    glLineWidth(m_lineWidth);
    glColor3f(1.0, 0.6, 0.0);

    int xPoints = m_borderRect.width() / m_gridSize.x() + 1;
    int yPoints = m_borderRect.height() / m_gridSize.y() + 1;

    m_gridSize.setX(m_borderRect.width() / (xPoints - 1));
    m_gridSize.setY(m_borderRect.height() / (yPoints - 1));

    glBegin(GL_LINES);

    for (int i = 0; i < yPoints; i++) {
        for (int j = 0; j < xPoints; j++) {
            glVertex3f(m_borderRect.x() + m_gridSize.x() * j, m_borderRect.y() + m_gridSize.y() * i, m_zTop);
            glVertex3f(m_borderRect.x() + m_gridSize.x() * j, m_borderRect.y() + m_gridSize.y() * i, m_zBottom);
        }
    }
    glEnd();
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





