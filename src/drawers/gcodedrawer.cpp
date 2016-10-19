// This file is a part of "Candle" application.
// Copyright 2015-2016 Hayrullin Denis Ravilevich

#include "gcodedrawer.h"

GcodeDrawer::GcodeDrawer()
{
    m_geometryUpdated = false;
    m_pointSize = 6;
    m_ignoreZ = true;
    m_colorizeSegments = true;
    m_colorizeType = GcodeDrawer::S;
}

void GcodeDrawer::update()
{
    m_indexes.clear();
    m_geometryUpdated = false;
    ShaderDrawable::update();
}

void GcodeDrawer::update(QList<int> indexes)
{
    // Store segments to update
    m_indexes += indexes;
    ShaderDrawable::update();
}

bool GcodeDrawer::updateData()
{
    if (m_indexes.isEmpty()) {
        qDebug() << "updating geometry" << this;

        QList<LineSegment*> *list = m_viewParser->getLines();
        VertexData vertex;

        qDebug() << "lines count" << list->count();

        // Create vertices array
        // Clear all vertex data
        m_lines.clear();
        m_points.clear();

        bool drawFirstPoint = true;
        for (int i = 0; i < list->count(); i++) {

            if (qIsNaN(list->at(i)->getEnd().z())) {
                qDebug() << "nan point" << list->at(i)->getEnd();
                continue;
            }

            // Find first point of toolpath
            if (drawFirstPoint) {

                if (qIsNaN(list->at(i)->getEnd().x()) || qIsNaN(list->at(i)->getEnd().y())) continue;

                // Draw first toolpath point
                vertex.color = Util::colorToVector(m_colorStart);
                vertex.position = list->at(i)->getEnd();
                vertex.start = QVector3D(sNan, sNan, m_pointSize);
                m_points.append(vertex);

                drawFirstPoint = false;
                continue;
            }

            // Prepare vertices
            if (list->at(i)->isFastTraverse()) vertex.start = list->at(i)->getStart();
            else vertex.start = QVector3D(sNan, sNan, sNan);

            // Simplify geometry
            int j = i;
            if (m_simplify && i < list->count() - 1) {
                QVector3D start = list->at(i)->getEnd() - list->at(i)->getStart();
                QVector3D next;
                double length = start.length();
                bool straight = false;

                do {
                    list->at(i)->setVertexIndex(m_lines.count()); // Store vertex index
                    i++;
                    if (i < list->count() - 1) {
                        next = list->at(i)->getEnd() - list->at(i)->getStart();
                        length += next.length();
//                        straight = start.crossProduct(start.normalized(), next.normalized()).length() < 0.025;
                    }
                // Split short & straight lines
                } while ((length < m_simplifyPrecision || straight) && i < list->count()
                         && getSegmentType(list->at(i)) == getSegmentType(list->at(j)));
                i--;
            } else {
                list->at(i)->setVertexIndex(m_lines.count()); // Store vertex index
            }

            // Set color
            vertex.color = getSegmentColor(list->at(i));

            // Line start
            vertex.position = list->at(j)->getStart();
            m_lines.append(vertex);

            // Line end
            vertex.position = list->at(i)->getEnd();
            m_lines.append(vertex);

            // Draw last toolpath point
            if (i == list->count() - 1) {
                vertex.color = Util::colorToVector(m_colorEnd);
                vertex.position = list->at(i)->getEnd();
                vertex.start = QVector3D(sNan, sNan, m_pointSize);
                m_points.append(vertex);
            }
        }
        m_indexes.clear();
        m_geometryUpdated = true;
        return true;
    } else {
        // Update vertices
        QList<LineSegment*> list = m_viewParser->getLineSegmentList();

        // Get vertices indexes
        auto mm = std::minmax_element(m_indexes.begin(), m_indexes.end());

        int vertexIndexFirst = qMax(list[*mm.first]->vertexIndex(), 0);
        int vertexIndexLast = qMax(list[*mm.second]->vertexIndex(), 0);
        int vertexCount = (vertexIndexLast - vertexIndexFirst) + 2;

        qDebug() << "updating vertices" << vertexIndexFirst << vertexIndexLast << vertexCount;

        // Allocate buffer
        VertexData *data = (VertexData*)malloc(vertexCount * sizeof(VertexData));

        // Read current vertices
        if (data) m_vbo.read(vertexIndexFirst * sizeof(VertexData), data, vertexCount * sizeof(VertexData));
        else {           // Can't read vbo
            m_indexes.clear();
            return true; // Update full vbo via allocate;
        }

        // Prepare colors
        QVector3D drawnColor = Util::colorToVector(m_colorDrawn);
        QVector3D highlightColor = Util::colorToVector(m_colorHighlight);

        // Update vertices for each line segment
        int vertexIndex;
        foreach (int i, m_indexes) {
            // Update vertex pair
            if (i < 0 || i > list.count() - 1) continue;
            vertexIndex = list[i]->vertexIndex() - vertexIndexFirst;
            if (vertexIndex >= 0) {
                // Update vertex array
                if (data[vertexIndex].color == drawnColor // If vertex of drawn segment
                        && getSegmentColor(list[i]) == highlightColor); // dont highlight
                else {
                    data[vertexIndex].color = getSegmentColor(list[i]);
                    data[vertexIndex + 1].color = data[vertexIndex].color;
                }
            }
        }

        m_vbo.write(vertexIndexFirst * sizeof(VertexData), data, vertexCount * sizeof(VertexData));
        free(data);
        m_indexes.clear();
        return false; // Update only vao
    }
}

QVector3D GcodeDrawer::getSegmentColor(LineSegment *segment)
{
    if (segment->drawn()) return Util::colorToVector(m_colorDrawn);//QVector3D(0.85, 0.85, 0.85);
    else if (segment->isHightlight()) return Util::colorToVector(m_colorHighlight);//QVector3D(0.57, 0.51, 0.9);
    else if (segment->isFastTraverse()) return Util::colorToVector(m_colorNormal);// QVector3D(0.0, 0.0, 0.0);
    else if (segment->isZMovement()) return Util::colorToVector(m_colorZMovement);//QVector3D(1.0, 0.0, 0.0);
    else if (m_colorizeSegments) switch (m_colorizeType) {
    case ColorizeType::S:
        return Util::colorToVector(QColor::fromHsl(0, 0, 255 - segment->getSpindleSpeed()));
    case ColorizeType::Z:
        return Util::colorToVector(QColor::fromHsl(0, 0, 255 - segment->getStart().z()));
    case ColorizeType::P:
        return Util::colorToVector(QColor::fromHsl(0, 0, 255 - segment->getDwell()));
        break;
    }
    return Util::colorToVector(m_colorNormal);//QVector3D(0.0, 0.0, 0.0);
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
    return m_viewParser->getMinimumExtremes();;
}

QVector3D GcodeDrawer::getMaximumExtremes()
{
    return m_viewParser->getMaximumExtremes();;
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

bool GcodeDrawer::geometryUpdated()
{
    return m_geometryUpdated;
}
QColor GcodeDrawer::colorNormal() const
{
    return m_colorNormal;
}

void GcodeDrawer::setColorNormal(const QColor &colorNormal)
{
    m_colorNormal = colorNormal;
}

QColor GcodeDrawer::colorHighlight() const
{
    return m_colorHighlight;
}

void GcodeDrawer::setColorHighlight(const QColor &colorHighlight)
{
    m_colorHighlight = colorHighlight;
}
QColor GcodeDrawer::colorZMovement() const
{
    return m_colorZMovement;
}

void GcodeDrawer::setColorZMovement(const QColor &colorZMovement)
{
    m_colorZMovement = colorZMovement;
}

QColor GcodeDrawer::colorDrawn() const
{
    return m_colorDrawn;
}

void GcodeDrawer::setColorDrawn(const QColor &colorDrawn)
{
    m_colorDrawn = colorDrawn;
}
QColor GcodeDrawer::colorStart() const
{
    return m_colorStart;
}

void GcodeDrawer::setColorStart(const QColor &colorStart)
{
    m_colorStart = colorStart;
}
QColor GcodeDrawer::colorEnd() const
{
    return m_colorEnd;
}

void GcodeDrawer::setColorEnd(const QColor &colorEnd)
{
    m_colorEnd = colorEnd;
}

bool GcodeDrawer::getIgnoreZ() const
{
    return m_ignoreZ;
}

void GcodeDrawer::setIgnoreZ(bool ignoreZ)
{
    m_ignoreZ = ignoreZ;
}









