#include "tooldrawer.h"
#include "math.h"

ToolDrawer::ToolDrawer(QObject *parent) :
    GLDrawable(parent)
{
    m_toolDiameter = 3;
    m_toolLength = 15;
    m_toolPosition = QVector3D(0, 0, 20);
    m_rotationAngle = 0;
}

void ToolDrawer::draw()
{
    glLineWidth(1);
    glColor3f(1.0, 0.6, 0.0);

    const int arcs = 4;

    for (int i = 0; i < arcs; i++) {

<<<<<<< HEAD
        double x = m_toolPosition.x() + m_toolDiameter / 2 * cos(m_rotationAngle / 180 * M_PI + (2 * M_PI / arcs) * i);
        double y = m_toolPosition.y() + m_toolDiameter / 2 * sin(m_rotationAngle / 180 * M_PI + (2 * M_PI / arcs) * i);
=======
        double x = m_toolPosition.x() + m_toolDiameter / 2 * cos(m_rotationAngle + (2 * M_PI / arcs) * i);
        double y = m_toolPosition.y() + m_toolDiameter / 2 * sin(m_rotationAngle + (2 * M_PI / arcs) * i);
>>>>>>> origin/master

        glBegin(GL_LINES);
        glVertex3f(x, y, m_toolPosition.z());
        glVertex3f(x, y, m_toolPosition.z() + m_toolLength);
        glEnd();

        glBegin(GL_LINES);
        glVertex3f(m_toolPosition.x(), m_toolPosition.y(), 0);
        glVertex3f(x, y, 0);
        glEnd();
    }

    glBegin(GL_LINE_LOOP);
    //glColor3f(0.0, 0.0, 0.0);
    for (int i = 0; i <= 50; i++) {
        double angle = 2 * M_PI * i / 50;
        double x = m_toolPosition.x() + m_toolDiameter / 2 * cos(angle);
        double y = m_toolPosition.y() + m_toolDiameter / 2 * sin(angle);
        glVertex3f(x, y, m_toolPosition.z());
    }
    glEnd();

    glBegin(GL_LINE_LOOP);
    //glColor3f(0.0, 0.0, 0.0);
    for (int i = 0; i <= 50; i++) {
        double angle = 2 * M_PI * i / 50;
        double x = m_toolPosition.x() + m_toolDiameter / 2 * cos(angle);
        double y = m_toolPosition.y() + m_toolDiameter / 2 * sin(angle);
        glVertex3f(x, y, m_toolPosition.z() + m_toolLength);
    }
    glEnd();

    glBegin(GL_LINE_LOOP);
    //glColor3f(0.0, 0.0, 0.0);
    for (int i = 0; i <= 50; i++) {
        double angle = 2 * M_PI * i / 50;
        double x = m_toolPosition.x() + m_toolDiameter / 2 * cos(angle);
        double y = m_toolPosition.y() + m_toolDiameter / 2 * sin(angle);
        glVertex3f(x, y, 0);
    }
    glEnd();

//    glColor3f(0, 0, 0.5);
//    glLineStipple(4, 0xAAAA);
//    glEnable(GL_LINE_STIPPLE);

//    glBegin(GL_LINES);
//    glVertex3f(m_toolPosition.x() - 5, m_toolPosition.y(), 0);
//    glVertex3f(m_toolPosition.x() + 5, m_toolPosition.y(), 0);
//    glEnd();

//    glBegin(GL_LINES);
//    glVertex3f(m_toolPosition.x(), m_toolPosition.y() - 5, 0);
//    glVertex3f(m_toolPosition.x(), m_toolPosition.y() + 5, 0);
//    glEnd();

//    glDisable(GL_LINE_STIPPLE);
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
<<<<<<< HEAD

void ToolDrawer::rotate(double angle)
{
    m_rotationAngle = normalizeAngle(m_rotationAngle + angle);
}

double ToolDrawer::normalizeAngle(double angle)
{
    while (angle < 0) angle += 360;
    while (angle > 360) angle -= 360;

    return angle;
}
=======
>>>>>>> origin/master
