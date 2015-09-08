#ifndef SHADERDRAWABLE_H
#define SHADERDRAWABLE_H

#include <QObject>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>

struct VertexData
{
    QVector3D position;
    QVector3D color;
    QVector3D start;
};

class ShaderDrawable : protected QOpenGLFunctions
{
public:
    explicit ShaderDrawable();
    ~ShaderDrawable();
    void update();
    void draw();

    bool needsUpdateGeometry() const;
    void updateGeometry(QOpenGLShaderProgram *shaderProgram = 0);

    virtual QVector3D getSizes();
    virtual QVector3D getMinimumExtremes();
    virtual QVector3D getMaximumExtremes();
    virtual int getLinesCount();

    double lineWidth() const;
    void setLineWidth(double lineWidth);

    bool visible() const;
    void setVisible(bool visible);

signals:

public slots:

protected:
    double m_lineWidth;
    bool m_visible;
    QVector<VertexData> m_vertexData;

    virtual void updateData();

private:
    QOpenGLBuffer m_vbo;
    QOpenGLVertexArrayObject m_vao;

    bool m_needsUpdateGeometry;

    void init();
};

#endif // SHADERDRAWABLE_H
