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
    m_lines.clear();
    m_points.clear();

    for (int i = 0; i < list.count(); i++) {

        if (std::isnan(list[i]->getEnd().z())) continue;

        // Find first point of toolpath
        if (drawFirstPoint) {

            if (std::isnan(list[i]->getEnd().x()) || std::isnan(list[i]->getEnd().y())) continue;

            // Draw first toolpath point
            vertex.color = list[i]->drawn() ? QVector3D(0.85, 0.85, 0.85) : QVector3D(1.0, 0.0, 0.0);
            vertex.position = list[i]->getEnd();
            vertex.start = QVector3D(NAN, NAN, NAN);
            m_points.append(vertex);

            drawFirstPoint = false;
            continue;
        }

        // Prepare vertices
        if (list[i]->isFastTraverse()) vertex.start = list[i]->getStart();
        else vertex.start = QVector3D(NAN, NAN, NAN);

        // Simplify geometry
        int j = i;
        if (m_simplify && i < list.count() - 1) {
            QVector3D start = list[i]->getEnd() - list[i]->getStart();
            QVector3D next;
            double length = start.length();
            bool straight;

            do {
                i++;
                if (i < list.count() - 1) {
                    next = list[i]->getEnd() - list[i]->getStart();
                    length += next.length();
                    straight = start.crossProduct(start.normalized(), next.normalized()).length() < 0.025;
                }
            // Split short & straight lines
            } while ((length < m_simplifyPrecision || straight) && i < list.count()
                     && getSegmentType(list[i]) == getSegmentType(list[j]));
            i--;
        }

        // Set color
        if (list[i]->drawn()) vertex.color = QVector3D(0.85, 0.85, 0.85);
        else if (list[i]->isHightlight()) vertex.color = QVector3D(0.57, 0.51, 0.9);
        else if (list[i]->isFastTraverse()) vertex.color = QVector3D(0.0, 0.0, 0.0);
        else if (list[i]->isZMovement()) vertex.color = QVector3D(1.0, 0.0, 0.0);
        else vertex.color = QVector3D(0.0, 0.0, 0.0);

        // Line start
        vertex.position = list[j]->getStart();
        m_lines.append(vertex);

        // Line end
        vertex.position = list[i]->getEnd();
        m_lines.append(vertex);

        // Draw last toolpath point
        if (i == list.count() - 1) {
            vertex.color = list[i]->drawn() ? QVector3D(0.85, 0.85, 0.85) : QVector3D(0.0, 1.0, 0.0);
            vertex.position = list[i]->getEnd();
            vertex.start = QVector3D(NAN, NAN, NAN);
            m_points.append(vertex);
        }
    }
}

int GcodeDrawer::getSegmentType(LineSegment* segment)
{
    return segment->isFastTraverse() + segment->isZMovement() * 2;
}

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

void GcodeDrawer::setViewParser(GcodeViewParse* viewParser)
{
    m_viewParser = viewParser;
}

GcodeViewParse *GcodeDrawer::viewParser()
{
    return m_viewParser;
}
bool GcodeDrawer::simplify() const
{
    return m_simplify;
}

void GcodeDrawer::setSimplify(bool simplify)
{
    m_simplify = simplify;
}
double GcodeDrawer::simplifyPrecision() const
{
    return m_simplifyPrecision;
}

void GcodeDrawer::setSimplifyPrecision(double simplifyPrecision)
{
    m_simplifyPrecision = simplifyPrecision;
}


