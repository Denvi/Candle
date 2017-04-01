// This file is a part of "Candle" application.
// Copyright 2015-2016 Hayrullin Denis Ravilevich

#include "gcodedrawer.h"

GcodeDrawer::GcodeDrawer() : QObject()
{   
    m_geometryUpdated = false;
    m_pointSize = 6;
    m_ignoreZ = false;
    m_grayscaleSegments = false;
    m_grayscaleCode = GcodeDrawer::S;
    m_grayscaleMin = 0;
    m_grayscaleMax = 255;
    m_drawMode = GcodeDrawer::Vectors;

    connect(&m_timerVertexUpdate, SIGNAL(timeout()), SLOT(onTimerVertexUpdate()));
    m_timerVertexUpdate.start(100);
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
}

bool GcodeDrawer::updateData()
{
    switch (m_drawMode) {
    case GcodeDrawer::Vectors:
        if (m_indexes.isEmpty()) return prepareVectors(); else return updateVectors();
    case GcodeDrawer::Raster:
        if (m_indexes.isEmpty()) return prepareRaster(); else return updateRaster();
    }
}

bool GcodeDrawer::prepareVectors()
{
    qDebug() << "preparing vectors" << this;

    QList<LineSegment*> *list = m_viewParser->getLines();
    VertexData vertex;

    qDebug() << "lines count" << list->count();

    // Clear all vertex data
    m_lines.clear();
    m_points.clear();
    m_triangles.clear();

    // Delete texture on mode change
    if (m_texture) {
        m_texture->destroy();
        delete m_texture;
        m_texture = NULL;
    }

    bool drawFirstPoint = true;
    for (int i = 0; i < list->count(); i++) {

        if (qIsNaN(list->at(i)->getEnd().z())) {
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
//                    straight = start.crossProduct(start.normalized(), next.normalized()).length() < 0.025;
                }
            // Split short & straight lines
            } while ((length < m_simplifyPrecision || straight) && i < list->count()
                     && getSegmentType(list->at(i)) == getSegmentType(list->at(j)));
            i--;
        } else {
            list->at(i)->setVertexIndex(m_lines.count()); // Store vertex index
        }

        // Set color
        vertex.color = getSegmentColorVector(list->at(i));

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
    m_geometryUpdated = true;
    m_indexes.clear();
    return true;
}

bool GcodeDrawer::updateVectors()
{
    // Update vertices
    QList<LineSegment*> *list = m_viewParser->getLines();

    // Map buffer
    VertexData *data = (VertexData*)m_vbo.map(QOpenGLBuffer::WriteOnly);

    // Update vertices for each line segment
    int vertexIndex;
    foreach (int i, m_indexes) {
        // Update vertex pair
        if (i < 0 || i > list->count() - 1) continue;
        vertexIndex = list->at(i)->vertexIndex();
        if (vertexIndex >= 0) {
            // Update vertex array            
            if (data) {
                data[vertexIndex].color = getSegmentColorVector(list->at(i));
                data[vertexIndex + 1].color = data[vertexIndex].color;
            } else {
                m_lines[vertexIndex].color = getSegmentColorVector(list->at(i));
                m_lines[vertexIndex + 1].color = m_lines.at(vertexIndex).color;
            }
        }
    }

    m_indexes.clear();
    if (data) m_vbo.unmap();
    return !data;
}

bool GcodeDrawer::prepareRaster()
{
    const int maxImageSize = 8192;

    qDebug() << "preparing raster" << this;

    // Generate image
    QImage image;
    qDebug() << "image info" << m_viewParser->getResolution() << m_viewParser->getMinLength();

    if (m_viewParser->getResolution().width() <= maxImageSize && m_viewParser->getResolution().height() <= maxImageSize)
    {
        image = QImage(m_viewParser->getResolution(), QImage::Format_RGB888);
        image.fill(Qt::white);

        QList<LineSegment*> *list = m_viewParser->getLines();
        qDebug() << "lines count" << list->count();

        double pixelSize = m_viewParser->getMinLength();
        QVector3D origin = m_viewParser->getMinimumExtremes();

        for (int i = 0; i < list->count(); i++) {
            if (!qIsNaN(list->at(i)->getEnd().length())) {
                setImagePixelColor(image, (list->at(i)->getEnd().x() - origin.x()) / pixelSize,
                                   (list->at(i)->getEnd().y() - origin.y()) / pixelSize, getSegmentColor(list->at(i)).rgb());
            }
        }
    }

    // Create vertices array
    // Clear all vertex data
    m_lines.clear();
    m_points.clear();
    m_triangles.clear();

    if (m_texture) {
        m_texture->destroy();
        delete m_texture;
        m_texture = NULL;
    }

    QVector<VertexData> vertices;
    VertexData vertex;

    // Set color
    vertex.color = Util::colorToVector(Qt::red);

    // Rect
    vertex.start = QVector3D(sNan, 0, 0);
    vertex.position = QVector3D(getMinimumExtremes().x(), getMinimumExtremes().y(), 0);
    vertices.append(vertex);

    vertex.start = QVector3D(sNan, 1, 1);
    vertex.position = QVector3D(getMaximumExtremes().x(), getMaximumExtremes().y(), 0);
    vertices.append(vertex);

    vertex.start = QVector3D(sNan, 0, 1);
    vertex.position = QVector3D(getMinimumExtremes().x(), getMaximumExtremes().y(), 0);
    vertices.append(vertex);

    vertex.start = QVector3D(sNan, 0, 0);
    vertex.position = QVector3D(getMinimumExtremes().x(), getMinimumExtremes().y(), 0);
    vertices.append(vertex);

    vertex.start = QVector3D(sNan, 1, 0);
    vertex.position = QVector3D(getMaximumExtremes().x(), getMinimumExtremes().y(), 0);
    vertices.append(vertex);

    vertex.start = QVector3D(sNan, 1, 1);
    vertex.position = QVector3D(getMaximumExtremes().x(), getMaximumExtremes().y(), 0);
    vertices.append(vertex);

    if (!image.isNull()) {
        m_texture = new QOpenGLTexture(image);
        m_triangles += vertices;
        m_image = image;
    } else {
        for (int i = 0; i < vertices.count(); i++) vertices[i].start = QVector3D(sNan, sNan, sNan);
        m_lines += vertices;
        m_image = QImage();
    }

    m_geometryUpdated = true;
    m_indexes.clear();
    return true;
}

bool GcodeDrawer::updateRaster()
{
    if (!m_image.isNull()) {

        QList<LineSegment*> *list = m_viewParser->getLines();

        double pixelSize = m_viewParser->getMinLength();
        QVector3D origin = m_viewParser->getMinimumExtremes();

        foreach (int i, m_indexes) setImagePixelColor(m_image, (list->at(i)->getEnd().x() - origin.x()) / pixelSize,
                                                      (list->at(i)->getEnd().y() - origin.y()) / pixelSize, getSegmentColor(list->at(i)).rgb());

        if (m_texture) m_texture->setData(QOpenGLTexture::RGB, QOpenGLTexture::UInt8, m_image.bits());
    }

    m_indexes.clear();
    return false;
}

void GcodeDrawer::setImagePixelColor(QImage &image, double x, double y, QRgb color) const
{
    if (qIsNaN(x) || qIsNaN(y)) {
        qDebug() << "Error updating pixel" << x << y;
        return;
    };

    uchar* pixel = image.scanLine((int)y);

    *(pixel + (int)x * 3) = qRed(color);
    *(pixel + (int)x * 3 + 1) = qGreen(color);
    *(pixel + (int)x * 3 + 2) = qBlue(color);
}

QVector3D GcodeDrawer::getSegmentColorVector(LineSegment *segment)
{
    return Util::colorToVector(getSegmentColor(segment));
}

QColor GcodeDrawer::getSegmentColor(LineSegment *segment)
{
    if (segment->drawn()) return m_colorDrawn;//QVector3D(0.85, 0.85, 0.85);
    else if (segment->isHightlight()) return m_colorHighlight;//QVector3D(0.57, 0.51, 0.9);
    else if (segment->isFastTraverse()) return m_colorNormal;// QVector3D(0.0, 0.0, 0.0);
    else if (segment->isZMovement()) return m_colorZMovement;//QVector3D(1.0, 0.0, 0.0);
    else if (m_grayscaleSegments) switch (m_grayscaleCode) {
    case GrayscaleCode::S:
        return QColor::fromHsl(0, 0, qBound<int>(0, 255 - 255.0 / (m_grayscaleMax - m_grayscaleMin) * segment->getSpindleSpeed(), 255));
    case GrayscaleCode::Z:
        return QColor::fromHsl(0, 0, qBound<int>(0, 255 - 255.0 / (m_grayscaleMax - m_grayscaleMin) * segment->getStart().z(), 255));
    }
    return m_colorNormal;//QVector3D(0.0, 0.0, 0.0);
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
    QVector3D v = m_viewParser->getMinimumExtremes();
    if (m_ignoreZ) v.setZ(0);

    return v;
}

QVector3D GcodeDrawer::getMaximumExtremes()
{
    QVector3D v = m_viewParser->getMaximumExtremes();
    if (m_ignoreZ) v.setZ(0);

    return v;
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

void GcodeDrawer::onTimerVertexUpdate()
{
    if (!m_indexes.isEmpty()) ShaderDrawable::update();
}

GcodeDrawer::DrawMode GcodeDrawer::drawMode() const
{
    return m_drawMode;
}

void GcodeDrawer::setDrawMode(const DrawMode &drawMode)
{
    m_drawMode = drawMode;
}

int GcodeDrawer::grayscaleMax() const
{
    return m_grayscaleMax;
}

void GcodeDrawer::setGrayscaleMax(int grayscaleMax)
{
    m_grayscaleMax = grayscaleMax;
}

int GcodeDrawer::grayscaleMin() const
{
    return m_grayscaleMin;
}

void GcodeDrawer::setGrayscaleMin(int grayscaleMin)
{
    m_grayscaleMin = grayscaleMin;
}

GcodeDrawer::GrayscaleCode GcodeDrawer::grayscaleCode() const
{
    return m_grayscaleCode;
}

void GcodeDrawer::setGrayscaleCode(const GrayscaleCode &grayscaleCode)
{
    m_grayscaleCode = grayscaleCode;
}

bool GcodeDrawer::getGrayscaleSegments() const
{
    return m_grayscaleSegments;
}

void GcodeDrawer::setGrayscaleSegments(bool grayscaleSegments)
{
    m_grayscaleSegments = grayscaleSegments;
}









