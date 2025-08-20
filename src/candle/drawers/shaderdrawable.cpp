// This file is a part of "Candle" application.
// Copyright 2015-2025 Hayrullin Denis Ravilevich

#include "shaderdrawable.h"

#ifdef GLES
#include <GLES/gl.h>
#endif

ShaderDrawable::ShaderDrawable()
{
    m_needsUpdateGeometry = true;
    m_visible = true;
    m_lineWidth = 1.0;
    m_pointSize = 1.0;
    m_texture = NULL;
    m_worldScale = 1.0;
    m_windowScaling = false;
    m_windowScale = 1.0;
}

ShaderDrawable::~ShaderDrawable()
{
    if (!m_vao.isCreated()) m_vao.destroy();
    if (!m_vbo.isCreated()) m_vbo.destroy();
}

void ShaderDrawable::init()
{
    // Init openGL functions
    initializeOpenGLFunctions();

    // Create buffers
    m_vao.create();
    m_vbo.create();
}

void ShaderDrawable::update()
{
    m_needsUpdateGeometry = true;
}

void ShaderDrawable::updateGeometry(QOpenGLShaderProgram *shaderProgram)
{
    // Init in context
    if (!m_vbo.isCreated()) init();

    if (m_vao.isCreated()) {
        // Prepare vao
        m_vao.bind();
    }

    // Prepare vbo
    m_vbo.bind();

    // Update vertex buffer
    if (updateData()) {
        // Fill vertices buffer
        QVector<VertexData> vertexData(m_triangles);
        vertexData += m_lines;
        vertexData += m_points;
        m_vbo.allocate(vertexData.constData(), vertexData.count() * sizeof(VertexData));
    } else {
        m_vbo.release();        
        if (m_vao.isCreated()) m_vao.release();
        m_needsUpdateGeometry = false;
        return;
    }

    if (m_vao.isCreated()) {
        // Offset for position
        quintptr offset = 0;

        // Tell OpenGL programmable pipeline how to locate vertex position data
        int vertexLocation = shaderProgram->attributeLocation("a_position");
        shaderProgram->enableAttributeArray(vertexLocation);
        shaderProgram->setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3, sizeof(VertexData));

        // Offset for color
        offset = sizeof(QVector3D);

        // Tell OpenGL programmable pipeline how to locate vertex color data
        int color = shaderProgram->attributeLocation("a_color");
        shaderProgram->enableAttributeArray(color);
        shaderProgram->setAttributeBuffer(color, GL_FLOAT, offset, 3, sizeof(VertexData));

        // Offset for line start point
        offset += sizeof(QVector3D);

        // Tell OpenGL programmable pipeline how to locate vertex line start point
        int data = shaderProgram->attributeLocation("a_data");
        shaderProgram->enableAttributeArray(data);
        shaderProgram->setAttributeBuffer(data, GL_FLOAT, offset, 3, sizeof(VertexData));

        offset += sizeof(QVector3D);

        int type = shaderProgram->attributeLocation("a_type");
        shaderProgram->enableAttributeArray(type);
        shaderProgram->setAttributeBuffer(type, GL_FLOAT, offset, 1, sizeof(VertexData));

        m_vao.release();
    }

    m_vbo.release();

    m_needsUpdateGeometry = false;
}

bool ShaderDrawable::updateData()
{
    // Test data
    m_lines = {
        {QVector3D(0, 0, 0), QVector3D(1, 0, 0), QVector3D(), VertexDataTypeLine},
        {QVector3D(10, 0, 0), QVector3D(1, 0, 0), QVector3D(), VertexDataTypeLine},
        {QVector3D(0, 0, 0), QVector3D(0, 1, 0), QVector3D(), VertexDataTypeLine},
        {QVector3D(0, 10, 0), QVector3D(0, 1, 0), QVector3D(), VertexDataTypeLine},
        {QVector3D(0, 0, 0), QVector3D(0, 0, 1), QVector3D(), VertexDataTypeLine},
        {QVector3D(0, 0, 10), QVector3D(0, 0, 1), QVector3D(), VertexDataTypeLine}
    };

    return true;
}

bool ShaderDrawable::needsUpdateGeometry() const
{
    return m_needsUpdateGeometry;
}

void ShaderDrawable::draw(QOpenGLShaderProgram *shaderProgram)
{
    if (!m_visible) return;

    if (m_vao.isCreated()) {
        // Prepare vao
        m_vao.bind();
    } else {
        // Prepare vbo
        m_vbo.bind();

        // Offset for position
        quintptr offset = 0;

        // Tell OpenGL programmable pipeline how to locate vertex position data
        int vertexLocation = shaderProgram->attributeLocation("a_position");
        shaderProgram->enableAttributeArray(vertexLocation);
        shaderProgram->setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3, sizeof(VertexData));

        // Offset for color
        offset = sizeof(QVector3D);

        // Tell OpenGL programmable pipeline how to locate vertex color data
        int color = shaderProgram->attributeLocation("a_color");
        shaderProgram->enableAttributeArray(color);
        shaderProgram->setAttributeBuffer(color, GL_FLOAT, offset, 3, sizeof(VertexData));

        // Offset for line start point
        offset += sizeof(QVector3D);

        // Tell OpenGL programmable pipeline how to locate vertex line start point
        int data = shaderProgram->attributeLocation("a_data");
        shaderProgram->enableAttributeArray(data);
        shaderProgram->setAttributeBuffer(data, GL_FLOAT, offset, 3, sizeof(VertexData));

        offset += sizeof(QVector3D);

        int type = shaderProgram->attributeLocation("a_type");
        shaderProgram->enableAttributeArray(type);
        shaderProgram->setAttributeBuffer(type, GL_FLOAT, offset, 1, sizeof(VertexData));
    }

    if (!m_triangles.isEmpty()) {
        if (m_texture) {
            m_texture->bind();
            shaderProgram->setUniformValue("texture", 0);
        }
        glDrawArrays(GL_TRIANGLES, 0, m_triangles.count());
    }

    if (!m_lines.isEmpty()) {
        glLineWidth(m_lineWidth);
        glDrawArrays(GL_LINES, m_triangles.count(), m_lines.count());
    }

    if (!m_points.isEmpty()) {
        glDrawArrays(GL_POINTS, m_triangles.count() + m_lines.count(), m_points.count());
    }

    if (m_vao.isCreated()) m_vao.release(); else m_vbo.release();
}

void ShaderDrawable::drawPainter(QPainter &painter, const QMatrix4x4 &projection, double ratio) {
}

QVector3D ShaderDrawable::getViewRanges()
{
    return Util::nAssign(getViewUpperBounds()) - Util::nAssign(getViewLowerBounds());
}

QVector3D ShaderDrawable::getViewLowerBounds()
{
    return QVector3D();
}

QVector3D ShaderDrawable::getViewUpperBounds()
{
    return QVector3D();
}

QVector3D ShaderDrawable::getModelRanges() {
    return Util::nAssign(getModelUpperBounds()) - Util::nAssign(getModelLowerBounds());
}

QVector3D ShaderDrawable::getModelLowerBounds() {
    return QVector3D();
}

QVector3D ShaderDrawable::getModelUpperBounds() {
    return QVector3D();
}

int ShaderDrawable::getVertexCount()
{
    return m_lines.count() + m_points.count() + m_triangles.count();
}

double ShaderDrawable::lineWidth() const
{
    return m_lineWidth;
}

void ShaderDrawable::setLineWidth(double lineWidth)
{
    m_lineWidth = lineWidth;
}

bool ShaderDrawable::visible() const
{
    return m_visible;
}

void ShaderDrawable::setVisible(bool visible)
{
    m_visible = visible;
}

double ShaderDrawable::pointSize() const
{
    return m_pointSize;
}

void ShaderDrawable::setPointSize(double pointSize)
{
    m_pointSize = pointSize;
}

QMatrix4x4 &ShaderDrawable::modelMatrix()
{
    return m_modelMatrix;
}

void ShaderDrawable::setModelMatrix(const QMatrix4x4 &modelMatrix)
{
    m_modelMatrix = modelMatrix;
}

const QMatrix4x4 &ShaderDrawable::rotation() {
    return m_rotationMatrix;
}

void ShaderDrawable::setRotation(const QMatrix4x4 &rotation) {
    m_rotationMatrix = rotation;
    m_modelMatrix = m_translationMatrix * m_rotationMatrix * m_scaleMatrix;
}

void ShaderDrawable::setRotation(double angle, const QVector3D &axis)
{
    m_rotationMatrix.setToIdentity();
    m_rotationMatrix.rotate(angle, axis);
    m_modelMatrix = m_translationMatrix * m_rotationMatrix * m_scaleMatrix;
}

const QMatrix4x4 &ShaderDrawable::translation()
{
    return m_translationMatrix;
}

void ShaderDrawable::setTranslation(const QMatrix4x4 &translation)
{
    m_translationMatrix = translation;
    m_modelMatrix = m_translationMatrix * m_rotationMatrix * m_scaleMatrix;
}

void ShaderDrawable::setTranslation(const QVector3D &translation)
{
    m_translationMatrix.setToIdentity();
    m_translationMatrix.translate(translation);
    m_modelMatrix = m_translationMatrix * m_rotationMatrix * m_scaleMatrix;
}

const QMatrix4x4 &ShaderDrawable::scale()
{
    return m_translationMatrix;
}

void ShaderDrawable::setScale(const QMatrix4x4 &scale)
{
    m_scaleMatrix = scale;
    m_modelMatrix = m_translationMatrix * m_rotationMatrix * m_scaleMatrix;
}

double ShaderDrawable::worldScale() {
    return m_worldScale;
}

void ShaderDrawable::setWorldScale(double scale) {
    m_worldScale = scale;
    m_scaleMatrix.setToIdentity();
    m_scaleMatrix.scale(scale);
    m_modelMatrix = m_translationMatrix * m_rotationMatrix * m_scaleMatrix;
}

bool ShaderDrawable::windowScaling() {
    return m_windowScaling;
}

void ShaderDrawable::setWindowScaling(bool windowScaling) {
    m_windowScaling = windowScaling;
}

double ShaderDrawable::windowScale() {
    return m_windowScale;
}

void ShaderDrawable::setWindowScale(double windowScale) {
    m_windowScale = windowScale;
}