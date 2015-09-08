// This file is a part of "grblControl" application.
// Copyright 2015 Hayrullin Denis Ravilevich

#include <QDebug>
#include "gcodedrawer.h"
#include "math.h"
#include "frmmain.h"

GcodeDrawer::GcodeDrawer()
{
}

void GcodeDrawer::updateData()
{
    QList<LineSegment*> list = m_viewParser->getLineSegmentList();
    VertexData vertex;
    bool drawFirstPoint = true;

    // Clear all vertex data
    m_vertexData.clear();

    for (int i = 0; i < list.count(); i++) {

        if (std::isnan(list[i]->getEnd().z())) continue;

        // Find first point of toolpath
        if (drawFirstPoint) {

            if (std::isnan(list[i]->getEnd().x()) || std::isnan(list[i]->getEnd().y())) continue;
            QVector3D end = list[i]->getEnd();

            // TODO: Draw first toolpath point

            drawFirstPoint = false;
            continue;
        }

        // Prepare vertices
        if (list[i]->isFastTraverse()) vertex.start = list[i]->getStart();
        else vertex.start = QVector3D(NAN, NAN, NAN);

        if (list[i]->drawn()) vertex.color = QVector3D(0.85, 0.85, 0.85);
        else if (list[i]->isHightlight()) vertex.color = QVector3D(0.57, 0.51, 0.9);
        else if (list[i]->isFastTraverse()) vertex.color = QVector3D(0.0, 0.0, 0.0);
        else if (list[i]->isZMovement()) vertex.color = QVector3D(1.0, 0.0, 0.0);
        else vertex.color = QVector3D(0.0, 0.0, 0.0);

        // Line start
        vertex.position = list[i]->getStart();
        m_vertexData.append(vertex);

        // Line end
        vertex.position = list[i]->getEnd();
        m_vertexData.append(vertex);
    }
}

/*void GcodeDrawer::draw()
{
    if (!m_visible) return;

    QList<LineSegment*> list = m_viewParser->getLineSegmentList();
    bool drawFirstPoint = true;

    glLineWidth(m_lineWidth);

    for (int i = 0; i < list.count(); i++) {

        if (std::isnan(list[i]->getEnd().z())) continue;

        // First point
        if (drawFirstPoint) {

            if (std::isnan(list[i]->getEnd().x()) || std::isnan(list[i]->getEnd().y())) continue;

            double size = qMax(qMax(getSizes().x(), getSizes().y()), getSizes().z()) / 75;

            QVector3D end = list[i]->getEnd();

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

            drawFirstPoint = false;
            continue;
        }

        if (list[i]->isFastTraverse()) {
            glLineStipple(1, 0x00ff);
            glEnable(GL_LINE_STIPPLE);
        }

        if (list[i]->drawn()) {
//            glLineWidth(1);
            glColor3f(0.85, 0.85, 0.85);
        }
        else if (list[i]->isHightlight()) {
            glColor3f(0.57, 0.51, 0.9);
        }
        else if (list[i]->isFastTraverse()) {
//            glLineWidth(1);
            glColor3f(0.0, 0.0, 0.0);
        }
        else if (list[i]->isZMovement()) {
//            glLineWidth(1);
            glColor3f(1, 0, 0.0);
        }
        else {
//            glLineWidth(m_lineWidth);
            glColor3f(0.0, 0.0, 0.0);
        }

        glBegin(GL_LINES);
        glVertex3f(list[i]->getStart().x(), list[i]->getStart().y(), list[i]->getStart().z());
        glVertex3f(list[i]->getEnd().x(), list[i]->getEnd().y(), list[i]->getEnd().z());
        glEnd();

        glDisable(GL_LINE_STIPPLE);
    }
}*/

QVector3D GcodeDrawer::getSizes()
{
    QVector3D min = m_viewParser->getMinimumExtremes();
    QVector3D max = m_viewParser->getMaximumExtremes();

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

void GcodeDrawer::setViewParser(GcodeViewParse* viewParser)
{
    m_viewParser = viewParser;
}

GcodeViewParse *GcodeDrawer::viewParser()
{
    return m_viewParser;
}
