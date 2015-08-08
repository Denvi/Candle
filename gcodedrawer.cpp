#include <QDebug>
#include "gcodedrawer.h"
#include "math.h"
#include "frmmain.h"

GcodeDrawer::GcodeDrawer(QObject *parent) :
    GLDrawable(parent)
{
    qDebug() << parent;
}

void GcodeDrawer::draw()
{
    foreach (LineSegment* ls, m_viewParser->getLineSegmentList()) {

        glLineWidth(m_lineWidth);

        // First point
        if (ls->getLineNumber() == 0) {

            double size = qMax(qMax(getSizes().x(), getSizes().y()), getSizes().z()) / 75;

            QVector3D end = ls->getEnd();

            glColor3f(1.0, 0.0, 0.0);
            glBegin(GL_LINE_LOOP);
            for (int i = 0; i <= 20; i++) {
                double angle = 2 * M_PI * i / 20;
                double x = end.x() + size * cos(angle);
                double y = end.y() + size * sin(angle);
                glVertex3f(x, y, end.z());
            }
            glEnd();
            glBegin(GL_LINE_LOOP);
            for (int i = 0; i <= 20; i++) {
                double angle = 2 * M_PI * i / 20;
                double x = end.x() + size * cos(angle);
                double z = end.z() + size * sin(angle);
                glVertex3f(x, end.y(), z);
            }
            glEnd();
            glBegin(GL_LINE_LOOP);
            for (int i = 0; i <= 20; i++) {
                double angle = 2 * M_PI * i / 20;
                double y = end.y() + size * cos(angle);
                double z = end.z() + size * sin(angle);
                glVertex3f(end.x(), y, z);
            }
            glEnd();
            continue;
        }

        if (ls->isFastTraverse()) {
            glLineStipple(1, 0x00ff);
            glEnable(GL_LINE_STIPPLE);
        }

        if (ls->drawn()) {
//            glLineWidth(1);
            glColor3f(0.85, 0.85, 0.85);
        }
        else if (ls->isFastTraverse()) {
//            glLineWidth(1);
            glColor3f(0.0, 0.0, 0.0);
        }
        else if (ls->isZMovement()) {
//            glLineWidth(1);
            glColor3f(1, 0, 0.0);
        }
        else {
//            glLineWidth(m_lineWidth);
            glColor3f(0.0, 0.0, 0.0);
        }

        glBegin(GL_LINES);
        glVertex3f(ls->getStart().x(), ls->getStart().y(), ls->getStart().z());
        glVertex3f(ls->getEnd().x(), ls->getEnd().y(), ls->getEnd().z());
        glEnd();

        glDisable(GL_LINE_STIPPLE);
    }
}

QVector3D GcodeDrawer::getSizes()
{
    QVector3D min = m_viewParser->getMinimumExtremes();
    QVector3D max = m_viewParser->getMaximumExtremes();

//    qDebug() << m_viewParser->getMaximumExtremes() - m_viewParser->getMinimumExtremes();
//    qDebug() << QVector3D(max.x() - min.x(), max.y() - min.y(), max.z() - min.z());

    return QVector3D(max.x() - min.x(), max.y() - min.y(), max.z() - min.z());
}

QVector3D GcodeDrawer::getMinimumExtremes()
{
    return m_viewParser->getMinimumExtremes();
}

QVector3D GcodeDrawer::getMaximumExtremes()
{
    return m_viewParser->getMaximumExtremes();
}

int GcodeDrawer::getLinesCount()
{
    return m_viewParser->getLineSegmentList().count();
}
double GcodeDrawer::lineWidth() const
{
    return m_lineWidth;
}

void GcodeDrawer::setLineWidth(double lineWidth)
{
    m_lineWidth = lineWidth;
}


void GcodeDrawer::setViewParser(GcodeViewParse* viewParser)
{
    m_viewParser = viewParser;
}

//void GcodeDrawer::setLines(QList<LineSegment *> lines)
//{
//    m_lines = lines;
//}
