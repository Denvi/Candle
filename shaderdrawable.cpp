//#define NAN std::numeric_limits<double>::quiet_NaN();

#include "shaderdrawable.h"

ShaderDrawable::ShaderDrawable() :
    m_needsUpdateGeometry(true), m_visible(true)
{
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
    qDebug() << "Updating geometry";

    // Init in context
    if (!m_vao.isCreated()) init();

    // Update data
    updateData();

    // Prepare vao
    m_vao.bind();

    // Prepare vbo
    m_vbo.bind();
    m_vbo.allocate(m_vertexData.constData(), m_vertexData.count() * sizeof(VertexData));

    // Tell OpenGL which VBOs to use
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo.bufferId());

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
    int start = shaderProgram->attributeLocation("a_start");
    shaderProgram->enableAttributeArray(start);
    shaderProgram->setAttributeBuffer(start, GL_FLOAT, offset, 3, sizeof(VertexData));

    m_vao.release();
    m_vbo.release();

    m_needsUpdateGeometry = false;
}

void ShaderDrawable::updateData()
{
    // Test data
    m_vertexData = {
        {QVector3D(0, 0, 0), QVector3D(1, 0, 0), QVector3D(NAN, 0, 0)},
        {QVector3D(10, 0, 0), QVector3D(1, 0, 0), QVector3D(NAN, 0, 0)},
        {QVector3D(0, 0, 0), QVector3D(0, 1, 0), QVector3D(NAN, 0, 0)},
        {QVector3D(0, 10, 0), QVector3D(0, 1, 0), QVector3D(NAN, 0, 0)},
        {QVector3D(0, 0, 0), QVector3D(0, 0, 1), QVector3D(NAN, 0, 0)},
        {QVector3D(0, 0, 10), QVector3D(0, 0, 1), QVector3D(NAN, 0, 0)}

        // Test cube
//        {QVector3D(-1, -1, -1), QVector3D(0, 0, 0), QVector3D(-1, -1, -1)},
//        {QVector3D(1, -1, -1), QVector3D(0, 0, 0), QVector3D(-1, -1, -1)},
//        {QVector3D(1, -1, -1), QVector3D(0, 0, 0), QVector3D(1, -1, -1)},
//        {QVector3D(1, 1, -1), QVector3D(0, 0, 0), QVector3D(1, -1, -1)},
//        {QVector3D(1, 1, -1), QVector3D(0, 0, 0), QVector3D(1, 1, -1)},
//        {QVector3D(-1, 1, -1), QVector3D(0, 0, 0), QVector3D(1, 1, -1)},
//        {QVector3D(-1, 1, -1), QVector3D(0, 0, 0), QVector3D(-1, 1, -1)},
//        {QVector3D(-1, -1, -1), QVector3D(0, 0, 0), QVector3D(-1, 1, -1)},

//        {QVector3D(-1, -1, 1), QVector3D(0, 0, 0), QVector3D(-1, -1, 1)},
//        {QVector3D(1, -1, 1), QVector3D(0, 0, 0), QVector3D(-1, -1, 1)},
//        {QVector3D(1, -1, 1), QVector3D(0, 0, 0), QVector3D(1, -1, 1)},
//        {QVector3D(1, 1, 1), QVector3D(0, 0, 0), QVector3D(1, -1, 1)},
//        {QVector3D(1, 1, 1), QVector3D(0, 0, 0), QVector3D(1, 1, 1)},
//        {QVector3D(-1, 1, 1), QVector3D(0, 0, 0), QVector3D(1, 1, 1)},
//        {QVector3D(-1, 1, 1), QVector3D(0, 0, 0), QVector3D(-1, 1, 1)},
//        {QVector3D(-1, -1, 1), QVector3D(0, 0, 0), QVector3D(-1, 1, 1)},

//        {QVector3D(-1, -1, -1), QVector3D(0, 0, 0), QVector3D(-1, -1, -1)},
//        {QVector3D(-1, -1, 1), QVector3D(0, 0, 0), QVector3D(-1, -1, -1)},
//        {QVector3D(1, -1, -1), QVector3D(0, 0, 0), QVector3D(1, -1, -1)},
//        {QVector3D(1, -1, 1), QVector3D(0, 0, 0), QVector3D(1, -1, -1)},
//        {QVector3D(1, 1, -1), QVector3D(0, 0, 0), QVector3D(1, 1, -1)},
//        {QVector3D(1, 1, 1), QVector3D(0, 0, 0), QVector3D(1, 1, -1)},
//        {QVector3D(-1, 1, -1), QVector3D(0, 0, 0), QVector3D(-1, 1, -1)},
//        {QVector3D(-1, 1, 1), QVector3D(0, 0, 0), QVector3D(-1, 1, -1)}
    };
}

bool ShaderDrawable::needsUpdateGeometry() const
{
    return m_needsUpdateGeometry;
}

void ShaderDrawable::draw()
{
    if (!m_visible) return;

    m_vao.bind();
    glLineWidth(m_lineWidth);
    glDrawArrays(GL_LINES, 0, m_vertexData.count());
    m_vao.release();
}

QVector3D ShaderDrawable::getSizes()
{
    return QVector3D(0, 0, 0);
}

QVector3D ShaderDrawable::getMinimumExtremes()
{
    return QVector3D(0, 0, 0);
}

QVector3D ShaderDrawable::getMaximumExtremes()
{
    return QVector3D(0, 0, 0);
}

int ShaderDrawable::getLinesCount()
{
    return 0;
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

