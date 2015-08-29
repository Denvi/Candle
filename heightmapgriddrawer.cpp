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
    glColor3f(1.0, 0.6, 0.0);

    int xPoints = m_model->columnCount();
    int yPoints = m_model->rowCount();

    double gridX = xPoints > 1 ? m_borderRect.width() / (xPoints - 1) : 0;
    double gridY = yPoints > 1 ? m_borderRect.height() / (yPoints - 1) : 0;

    for (int i = 0; i < yPoints; i++) {
        for (int j = 0; j < xPoints; j++) {
            if (m_model == NULL || std::isnan(m_model->data(m_model->index(i, j)).toDouble())) {
                glBegin(GL_LINES);
                glVertex3f(m_borderRect.x() + gridX * j, m_borderRect.y() + gridY * i, m_zTop);
                glVertex3f(m_borderRect.x() + gridX * j, m_borderRect.y() + gridY * i, m_zBottom);
                glEnd();
            } else {
                glBegin(GL_POINTS);
                glVertex3f(m_borderRect.x() + gridX * j, m_borderRect.y() + gridY * i, m_model->data(m_model->index(i, j)).toDouble());
                glEnd();
            }
        }
    }

    for (int i = 0; i < yPoints; i++) {
        glBegin(GL_LINE_STRIP);
        for (int j = 0; j < xPoints; j++) {
            glVertex3f(m_borderRect.x() + gridX * j, m_borderRect.y() + gridY * i, m_model->data(m_model->index(i, j)).toDouble());
        }
        glEnd();
    }

    for (int j = 0; j < xPoints; j++) {
        glBegin(GL_LINE_STRIP);
        for (int i = 0; i < yPoints; i++) {
            glVertex3f(m_borderRect.x() + gridX * j, m_borderRect.y() + gridY * i, m_model->data(m_model->index(i, j)).toDouble());
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






