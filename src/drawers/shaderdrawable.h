#ifndef SHADERDRAWABLE_H
#define SHADERDRAWABLE_H

#include <QObject>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLTexture>
#include "utils/util.h"

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
    void draw(QOpenGLShaderProgram *shaderProgram);

    bool needsUpdateGeometry() const;
    void updateGeometry(QOpenGLShaderProgram *shaderProgram = 0);

    virtual QVector3D getSizes();
    virtual QVector3D getMinimumExtremes();
    virtual QVector3D getMaximumExtremes();
    virtual int getVertexCount();

    double lineWidth() const;
    void setLineWidth(double lineWidth);

    bool visible() const;
    void setVisible(bool visible);

    double pointSize() const;
    void setPointSize(double pointSize);

signals:

public slots:

protected:
    double m_lineWidth;
    double m_pointSize;
    bool m_visible;
    QVector<VertexData> m_lines;
    QVector<VertexData> m_points;
    QVector<VertexData> m_triangles;
    QOpenGLTexture *m_texture;

    QOpenGLBuffer m_vbo; // Protected for direct vbo access

    virtual bool updateData();
    void init();

private:
    QOpenGLVertexArrayObject m_vao;

    bool m_needsUpdateGeometry;
};

#endif // SHADERDRAWABLE_H
