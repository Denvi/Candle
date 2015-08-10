#include "tooldrawer.h"
#include "math.h"

ToolDrawer::ToolDrawer(QObject *parent) :
    GLDrawable(parent)
{
    m_toolDiameter = 3;
    m_toolLength = 15;
    m_toolPosition = QVector3D(0, 0, 0);
    m_rotationAngle = 0;
}

void ToolDrawer::draw()
{
    glLineWidth(m_lineWidth);
    glColor3f(1.0, 0.6, 0.0);

    const int arcs = 4;

    glBegin(GL_LINES);
    for (int i = 0; i < arcs; i++) {

        double x = m_toolPosition.x() + m_toolDiameter / 2 * cos(m_rotationAngle / 180 * M_PI + (2 * M_PI / arcs) * i);
        double y = m_toolPosition.y() + m_toolDiameter / 2 * sin(m_rotationAngle / 180 * M_PI + (2 * M_PI / arcs) * i);

        // Side lines
        glVertex3f(x, y, m_toolPosition.z() + m_endLength);
        glVertex3f(x, y, m_toolPosition.z() + m_toolLength);
//        glEnd();

        // Bottom lines
//        glBegin(GL_LINES);
        glVertex3f(m_toolPosition.x(), m_toolPosition.y(), m_toolPosition.z());
        glVertex3f(x, y, m_toolPosition.z() + m_endLength);
//        glEnd();

        // Top lines
//        glBegin(GL_LINES);
        glVertex3f(m_toolPosition.x(), m_toolPosition.y(), m_toolPosition.z() + m_toolLength);
        glVertex3f(x, y, m_toolPosition.z() + m_toolLength);
//        glEnd();

        // Zero Z lines
//        glBegin(GL_LINES);
        glVertex3f(m_toolPosition.x(), m_toolPosition.y(), 0);
        glVertex3f(x, y, 0);
    }
    glEnd();

    // Bottom circle
    glBegin(GL_LINE_LOOP);
    //glColor3f(0.0, 0.0, 0.0);
    for (int i = 0; i <= 50; i++) {
        double angle = 2 * M_PI * i / 50;
        double x = m_toolPosition.x() + m_toolDiameter / 2 * cos(angle);
        double y = m_toolPosition.y() + m_toolDiameter / 2 * sin(angle);
        glVertex3f(x, y, m_toolPosition.z() + m_endLength);
    }
    glEnd();

    // Top circle
    glBegin(GL_LINE_LOOP);
    //glColor3f(0.0, 0.0, 0.0);
    for (int i = 0; i <= 50; i++) {
        double angle = 2 * M_PI * i / 50;
        double x = m_toolPosition.x() + m_toolDiameter / 2 * cos(angle);
        double y = m_toolPosition.y() + m_toolDiameter / 2 * sin(angle);
        glVertex3f(x, y, m_toolPosition.z() + m_toolLength);
    }
    glEnd();

    // Zero Z circle
    if (m_endLength > 0) {
        glBegin(GL_POINTS);
        glVertex3f(m_toolPosition.x(), m_toolPosition.y(), 0);
        glEnd();
    } else {
        glBegin(GL_LINE_LOOP);
        //glColor3f(0.0, 0.0, 0.0);
        for (int i = 0; i <= 50; i++) {
            double angle = 2 * M_PI * i / 50;
            double x = m_toolPosition.x() + m_toolDiameter / 2 * cos(angle);
            double y = m_toolPosition.y() + m_toolDiameter / 2 * sin(angle);
            glVertex3f(x, y, 0);
        }
        glEnd();
    }
}

QVector3D ToolDrawer::getSizes()
{
    return QVector3D(m_toolPosition.x() + m_toolDiameter / 2, m_toolPosition.y() + m_toolDiameter / 2, m_toolPosition.z() + m_toolLength);
}

QVector3D ToolDrawer::getMinimumExtremes()
{
    return QVector3D(0, 0, 0);
}

QVector3D ToolDrawer::getMaximumExtremes()
{
    return QVector3D(m_toolPosition.x() + m_toolDiameter / 2, m_toolPosition.y() + m_toolDiameter / 2, m_toolPosition.z() + m_toolLength);
}

double ToolDrawer::toolDiameter() const
{
    return m_toolDiameter;
}

void ToolDrawer::setToolDiameter(double toolDiameter)
{
    m_toolDiameter = toolDiameter;
}
double ToolDrawer::toolLength() const
{
    return m_toolLength;
}

void ToolDrawer::setToolLength(double toolLength)
{
    m_toolLength = toolLength;
}
QVector3D ToolDrawer::toolPosition() const
{
    return m_toolPosition;
}

void ToolDrawer::setToolPosition(const QVector3D &toolPosition)
{
    m_toolPosition = toolPosition;
}
double ToolDrawer::rotationAngle() const
{
    return m_rotationAngle;
}

void ToolDrawer::setRotationAngle(double rotationAngle)
{
    m_rotationAngle = rotationAngle;
}

void ToolDrawer::rotate(double angle)
{
    m_rotationAngle = normalizeAngle(m_rotationAngle + angle);
}
double ToolDrawer::lineWidth() const
{
    return m_lineWidth;
}

void ToolDrawer::setLineWidth(double lineWidth)
{
    m_lineWidth = lineWidth;
}
double ToolDrawer::toolAngle() const
{
    return m_toolAngle;
}

void ToolDrawer::setToolAngle(double toolAngle)
{
    m_toolAngle = toolAngle;

    m_endLength = m_toolAngle > 0 && m_toolAngle < 180 ? m_toolDiameter / 2 / tan(m_toolAngle / 180 * M_PI / 2) : 0;
    if (m_toolLength < m_endLength) m_toolLength = m_endLength;
}

double ToolDrawer::normalizeAngle(double angle)
{
    while (angle < 0) angle += 360;
    while (angle > 360) angle -= 360;
    
    return angle;
}
