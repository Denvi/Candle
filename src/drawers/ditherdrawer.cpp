// This file is a part of "Candle" application.
// Copyright 2015-2016 Hayrullin Denis Ravilevich

#include "ditherdrawer.h"

DitherDrawer::DitherDrawer() : QObject()
{   
    m_geometryUpdated = false;
    m_pointSize = 6;
    m_ignoreZ = false;
    m_grayscaleSegments = false;
    m_grayscaleCode = DitherDrawer::S;
    m_grayscaleMin = 0;
    m_grayscaleMax = 255;

    connect(&m_timerVertexUpdate, SIGNAL(timeout()), SLOT(onTimerVertexUpdate()));
    m_timerVertexUpdate.start(100);
}

void DitherDrawer::update()
{
    m_indexes.clear();
    m_geometryUpdated = false;
    ShaderDrawable::update();
}

void DitherDrawer::update(QList<int> indexes)
{
    // Store segments to update
    m_indexes += indexes;
//    ShaderDrawable::update();
}

bool DitherDrawer::updateData()
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
//                qDebug() << "nan point" << list->at(i)->getEnd();
                continue;
            }

            // Find first point of toolpath
            if (drawFirstPoint) {

                if (qIsNaN(list->at(i)->getEnd().x()) || qIsNaN(list->at(i)->getEnd().y())) continue;

                // Draw first toolpath point
                vertex.color = Util::colorToVector(m_colorStart);
                vertex.position = list->at(i)->getEnd();
                if (m_ignoreZ) vertex.position.setZ(0);
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
            if (m_ignoreZ) vertex.position.setZ(0);
            m_lines.append(vertex);

            // Line end
            vertex.position = list->at(i)->getEnd();
            if (m_ignoreZ) vertex.position.setZ(0);
            m_lines.append(vertex);

            // Draw last toolpath point
            if (i == list->count() - 1) {
                vertex.color = Util::colorToVector(m_colorEnd);
                vertex.position = list->at(i)->getEnd();
                if (m_ignoreZ) vertex.position.setZ(0);
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

        int vertexIndexFirst = qMax(list.at(*mm.first)->vertexIndex(), 0);
        int vertexIndexLast = qMax(list.at(*mm.second)->vertexIndex(), 0);
        int vertexCount = (vertexIndexLast - vertexIndexFirst) + 2;

//        qDebug() << "updating vertices" << vertexIndexFirst << vertexIndexLast << vertexCount;

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
            vertexIndex = list.at(i)->vertexIndex() - vertexIndexFirst;
            if (vertexIndex >= 0) {
                // Update vertex array
                if (data[vertexIndex].color == drawnColor // If vertex of drawn segment
                        && getSegmentColor(list.at(i)) == highlightColor); // dont highlight
                else {
                    data[vertexIndex].color = getSegmentColor(list.at(i));
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

QVector3D DitherDrawer::getSegmentColor(LineSegment *segment)
{
    if (segment->drawn()) return Util::colorToVector(m_colorDrawn);//QVector3D(0.85, 0.85, 0.85);
    else if (segment->isHightlight()) return Util::colorToVector(m_colorHighlight);//QVector3D(0.57, 0.51, 0.9);
    else if (segment->isFastTraverse()) return Util::colorToVector(m_colorNormal);// QVector3D(0.0, 0.0, 0.0);
    else if (segment->isZMovement()) return Util::colorToVector(m_colorZMovement);//QVector3D(1.0, 0.0, 0.0);
    else if (m_grayscaleSegments) switch (m_grayscaleCode) {
    case GrayscaleCode::S:
        return Util::colorToVector(QColor::fromHsl(0, 0, qBound<int>(0, 255 - 255 / (m_grayscaleMax - m_grayscaleMin) * segment->getSpindleSpeed(), 255)));
    case GrayscaleCode::Z:
        return Util::colorToVector(QColor::fromHsl(0, 0, qBound<int>(0, 255 - 255 / (m_grayscaleMax - m_grayscaleMin) * segment->getStart().z(), 255)));
    }
    return Util::colorToVector(m_colorNormal);//QVector3D(0.0, 0.0, 0.0);
}

int DitherDrawer::getSegmentType(LineSegment* segment)
{
    return segment->isFastTraverse() + segment->isZMovement() * 2;
}

QVector3D DitherDrawer::getSizes()
{
    QVector3D min = m_viewParser->getMinimumExtremes();
    QVector3D max = m_viewParser->getMaximumExtremes();

    return QVector3D(max.x() - min.x(), max.y() - min.y(), max.z() - min.z());
}

QVector3D DitherDrawer::getMinimumExtremes()
{
    QVector3D v = m_viewParser->getMinimumExtremes();
    if (m_ignoreZ) v.setZ(0);

    return v;
}

QVector3D DitherDrawer::getMaximumExtremes()
{
    QVector3D v = m_viewParser->getMaximumExtremes();
    if (m_ignoreZ) v.setZ(0);

    return v;
}

void DitherDrawer::setViewParser(GcodeViewParse* viewParser)
{
    m_viewParser = viewParser;
}

GcodeViewParse *DitherDrawer::viewParser()
{
    return m_viewParser;
}
bool DitherDrawer::simplify() const
{
    return m_simplify;
}

void DitherDrawer::setSimplify(bool simplify)
{
    m_simplify = simplify;
}
double DitherDrawer::simplifyPrecision() const
{
    return m_simplifyPrecision;
}

void DitherDrawer::setSimplifyPrecision(double simplifyPrecision)
{
    m_simplifyPrecision = simplifyPrecision;
}

bool DitherDrawer::geometryUpdated()
{
    return m_geometryUpdated;
}
QColor DitherDrawer::colorNormal() const
{
    return m_colorNormal;
}

void DitherDrawer::setColorNormal(const QColor &colorNormal)
{
    m_colorNormal = colorNormal;
}

QColor DitherDrawer::colorHighlight() const
{
    return m_colorHighlight;
}

void DitherDrawer::setColorHighlight(const QColor &colorHighlight)
{
    m_colorHighlight = colorHighlight;
}
QColor DitherDrawer::colorZMovement() const
{
    return m_colorZMovement;
}

void DitherDrawer::setColorZMovement(const QColor &colorZMovement)
{
    m_colorZMovement = colorZMovement;
}

QColor DitherDrawer::colorDrawn() const
{
    return m_colorDrawn;
}

void DitherDrawer::setColorDrawn(const QColor &colorDrawn)
{
    m_colorDrawn = colorDrawn;
}
QColor DitherDrawer::colorStart() const
{
    return m_colorStart;
}

void DitherDrawer::setColorStart(const QColor &colorStart)
{
    m_colorStart = colorStart;
}
QColor DitherDrawer::colorEnd() const
{
    return m_colorEnd;
}

void DitherDrawer::setColorEnd(const QColor &colorEnd)
{
    m_colorEnd = colorEnd;
}

bool DitherDrawer::getIgnoreZ() const
{
    return m_ignoreZ;
}

void DitherDrawer::setIgnoreZ(bool ignoreZ)
{
    m_ignoreZ = ignoreZ;
}

void DitherDrawer::onTimerVertexUpdate()
{
    if (!m_indexes.isEmpty()) ShaderDrawable::update();
}

int DitherDrawer::grayscaleMax() const
{
    return m_grayscaleMax;
}

void DitherDrawer::setGrayscaleMax(int grayscaleMax)
{
    m_grayscaleMax = grayscaleMax;
}

int DitherDrawer::grayscaleMin() const
{
    return m_grayscaleMin;
}

void DitherDrawer::setGrayscaleMin(int grayscaleMin)
{
    m_grayscaleMin = grayscaleMin;
}

DitherDrawer::GrayscaleCode DitherDrawer::grayscaleCode() const
{
    return m_grayscaleCode;
}

void DitherDrawer::setGrayscaleCode(const GrayscaleCode &grayscaleCode)
{
    m_grayscaleCode = grayscaleCode;
}

bool DitherDrawer::getGrayscaleSegments() const
{
    return m_grayscaleSegments;
}

void DitherDrawer::setGrayscaleSegments(bool grayscaleSegments)
{
    m_grayscaleSegments = grayscaleSegments;
}









