// This file is a part of "Candle" application.
// Copyright 2015-2025 Hayrullin Denis Ravilevich

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

    connect(&m_timerVertexUpdate, &QTimer::timeout, this, &GcodeDrawer::onTimerVertexUpdate);
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
    default:
        return true;
    }
}

bool GcodeDrawer::prepareVectors()
{
    // Clear all vertex data
    m_lines.clear();
    m_points.clear();
    m_triangles.clear();

    // Delete texture on mode change
    if (m_texture)
    {
        m_texture->destroy();
        delete m_texture;
        m_texture = nullptr;
    }

    const auto &lineSegments = m_viewParser->getLineSegments();
    bool isFirstPointAdded = false;
    int lineSegmentsCount = lineSegments->count();
    VertexData vertex;

    for (int i = 0; i < lineSegmentsCount; i++)
    {
        const auto &lineSegmentBegin = lineSegments->at(i);
        auto lineSegmentEnd = lineSegmentBegin;

        // Find first point of toolpath
        if (!isFirstPointAdded)
        {
            if (qIsNaN(lineSegmentBegin->getEnd().x()) || qIsNaN(lineSegmentBegin->getEnd().y()))
                continue;

            // Draw first toolpath point
            vertex.color = Util::colorToVector(m_colorStart);
            vertex.position = lineSegmentBegin->getStart();
            vertex.type = VertexDataTypePoint;
            if (m_ignoreZ || qIsNaN(vertex.position.z()))
                vertex.position.setZ(0);
            vertex.data = QVector3D(m_pointSize, 0, 0);
            m_points.append(vertex);

            isFirstPointAdded = true;
            // Don't continue - draw the first segment too!
        }

        // Prepare vertices
        if (lineSegmentBegin->isFastTraverse())
        {
            vertex.type = VertexDataTypeDash;
            vertex.data = lineSegmentBegin->getStart();
        }
        else
        {
            vertex.type = VertexDataTypeLine;
        }

        // Store vertex index
        lineSegmentBegin->setVertexIndex(m_lines.count());

        // Simplify geometry
        auto lineSegmentType = getSegmentType(lineSegmentBegin);

        if (m_simplify && i < lineSegmentsCount - 1)
        {
            double length = getSegmentLength(lineSegmentBegin);
            LineSegment *lineSegment;

            for (auto j = i + 1; j < lineSegmentsCount; j++)
            {
                lineSegment = lineSegments->at(j);
                if (getSegmentType(lineSegment) != lineSegmentType)
                    break;

                length += getSegmentLength(lineSegment);
                if (length > m_simplifyPrecision)
                    break;

                lineSegmentEnd = lineSegment;
                lineSegmentEnd->setVertexIndex(m_lines.count());
                i = j;
            }
        }

        // Set color
        vertex.color = getSegmentColorVector(lineSegmentEnd);

        // Line start
        vertex.position = lineSegmentBegin->getStart();
        if (m_ignoreZ || qIsNaN(vertex.position.z()))
            vertex.position.setZ(0);
        m_lines.append(vertex);

        // Line end
        vertex.position = lineSegmentEnd->getEnd();
        if (m_ignoreZ || qIsNaN(vertex.position.z()))
            vertex.position.setZ(0);
        m_lines.append(vertex);

        // Draw last toolpath point
        if (i == lineSegmentsCount - 1)
        {
            vertex.type = VertexDataTypePoint;
            vertex.color = Util::colorToVector(m_colorEnd);
            vertex.position = lineSegmentEnd->getEnd();
            if (m_ignoreZ || qIsNaN(vertex.position.z()))
                vertex.position.setZ(0);
            vertex.data = QVector3D(m_pointSize, 0, 0);
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
    QList<LineSegment*> *list = m_viewParser->getLineSegments();

    auto isVbo = m_vbo.isCreated();
    auto firstVertexIndex = -1;
    auto lastVertexIndex = -1;

    // Remove duplicates and sort
    std::sort(m_indexes.begin(), m_indexes.end());
    auto last = std::unique(m_indexes.begin(), m_indexes.end());
    m_indexes.erase(last, m_indexes.end());

    // Update vertices for each line segment
    foreach (int i, m_indexes)
    {
        // Update vertex pair
        if (i < 0 || i > list->count() - 1)
            continue;

        auto vertexIndex = list->at(i)->vertexIndex();

        if (vertexIndex >= 0)
        {
            // Update vertex data
            auto color = getSegmentColorVector(list->at(i));
            m_lines[vertexIndex].color = color;
            m_lines[vertexIndex + 1].color = color;

            // Prepare vertex indexes
            if (firstVertexIndex == -1)
            {
                firstVertexIndex = vertexIndex;
                lastVertexIndex = vertexIndex;
            }
            else
            {
                firstVertexIndex = qMin(firstVertexIndex, vertexIndex);
                lastVertexIndex = qMax(lastVertexIndex, vertexIndex);            
            }
        }
    }

    if (isVbo && firstVertexIndex != -1)
    {
        glBufferSubData(GL_ARRAY_BUFFER,
            firstVertexIndex * sizeof(VertexData),
            (lastVertexIndex - firstVertexIndex + 2) * sizeof(VertexData),
            m_lines.data() + firstVertexIndex
        );
    }

    m_indexes.clear();

    return !isVbo;
}

bool GcodeDrawer::prepareRaster()
{
    const int maxImageSize = 8192;

    // Generate image
    QImage image;

    if (m_viewParser->getModelResolution().width() <= maxImageSize &&
            m_viewParser->getModelResolution().height() <= maxImageSize)
    {
        image = QImage(m_viewParser->getModelResolution(), QImage::Format_RGB888);
        image.fill(Qt::white);

        QList<LineSegment*> *list = m_viewParser->getLineSegments();

        double pixelSize = m_viewParser->getModelMinLineLength();
        QVector3D origin = m_viewParser->getViewLowerBounds();

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

    // Set data type
    vertex.type = VertexDataTypeTriangle;

    // Rect
    vertex.data = QVector3D(0, 0, 0);
    vertex.position = QVector3D(getViewLowerBounds().x(), getViewLowerBounds().y(), 0);
    vertices.append(vertex);

    vertex.data = QVector3D(0, 1, 1);
    vertex.position = QVector3D(getViewUpperBounds().x(), getViewUpperBounds().y(), 0);
    vertices.append(vertex);

    vertex.data = QVector3D(0, 0, 1);
    vertex.position = QVector3D(getViewLowerBounds().x(), getViewUpperBounds().y(), 0);
    vertices.append(vertex);

    vertex.data = QVector3D(0, 0, 0);
    vertex.position = QVector3D(getViewLowerBounds().x(), getViewLowerBounds().y(), 0);
    vertices.append(vertex);

    vertex.data = QVector3D(0, 1, 0);
    vertex.position = QVector3D(getViewUpperBounds().x(), getViewLowerBounds().y(), 0);
    vertices.append(vertex);

    vertex.data = QVector3D(0, 1, 1);
    vertex.position = QVector3D(getViewUpperBounds().x(), getViewUpperBounds().y(), 0);
    vertices.append(vertex);

    if (!image.isNull()) {
        m_texture = new QOpenGLTexture(image);
        m_triangles += vertices;
        m_image = image;
    } else {
        for (int i = 0; i < vertices.count(); i++) vertices[i].data = QVector3D();
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

        QList<LineSegment*> *list = m_viewParser->getLineSegments();

        double pixelSize = m_viewParser->getModelMinLineLength();
        QVector3D origin = m_viewParser->getViewLowerBounds();

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
    if (segment->isDrawn()) return m_colorDrawn;//QVector3D(0.85, 0.85, 0.85);
    else if (segment->isHighlight()) return m_colorHighlight;//QVector3D(0.57, 0.51, 0.9);
    else if (segment->isFastTraverse()) return m_colorNormal;// QVector3D(0.0, 0.0, 0.0);
    else if (segment->isZMovement()) return m_colorZMovement;//QVector3D(1.0, 0.0, 0.0);
    else if (m_grayscaleSegments) switch (m_grayscaleCode) {
    case GcodeDrawer::S:
        return QColor::fromHsl(0, 0, qBound<int>(0, 255 - 255.0 / (m_grayscaleMax - m_grayscaleMin) * segment->getSpindleSpeed(), 255));
    case GcodeDrawer::Z:
        return QColor::fromHsl(0, 0, qBound<int>(0, 255 - 255.0 / (m_grayscaleMax - m_grayscaleMin) * segment->getStart().z(), 255));
    }
    return m_colorNormal;//QVector3D(0.0, 0.0, 0.0);
}

int GcodeDrawer::getSegmentType(LineSegment* segment)
{
    return segment->isFastTraverse() + segment->isZMovement() * 2;
}

float GcodeDrawer::getSegmentLength(LineSegment* segment)
{
    return (segment->getEnd() - segment->getStart()).length();
}

QVector3D GcodeDrawer::getViewLowerBounds()
{
    QVector3D v = m_viewParser->getViewLowerBounds();
    if (m_ignoreZ) v.setZ(0);

    return v;
}

QVector3D GcodeDrawer::getViewUpperBounds()
{
    QVector3D v = m_viewParser->getViewUpperBounds();
    if (m_ignoreZ) v.setZ(0);

    return v;
}

QVector3D GcodeDrawer::getModelLowerBounds() {
    return m_viewParser->getModelLowerBounds();
}

QVector3D GcodeDrawer::getModelUpperBounds() {
    return m_viewParser->getModelUpperBounds();
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








