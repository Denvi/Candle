// This file is a part of "Candle" application.
// Copyright 2015-2025 Hayrullin Denis Ravilevich

#ifndef SHADERDRAWABLE_H
#define SHADERDRAWABLE_H

#include <QObject>
#include <QPainter>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLTexture>
#include "../utils/util.h"

enum VertexDataType {
    VertexDataTypeLine,
    VertexDataTypeDash,
    VertexDataTypeDashDot,
    VertexDataTypePoint,
    VertexDataTypeTriangle
};

struct VertexData
{
    QVector3D position;
    QVector3D color;
    QVector3D data;
    float type;
};

class ShaderDrawable : protected QOpenGLFunctions
{
public:
    explicit ShaderDrawable();
    void update();
    void draw(QOpenGLShaderProgram *shaderProgram);
    void dispose();

    /// @brief Draw 2D graphics for the object
    /// @param projection - world to the visualizer window transform matrix
    /// @param ratio - visualizer window pixels to the world units ratio
    virtual void drawPainter(QPainter &painter, const QMatrix4x4 &projection, double ratio);

    bool needsUpdateGeometry() const;
    void updateGeometry(QOpenGLShaderProgram *shaderProgram = 0);

    virtual QVector3D getViewRanges();
    virtual QVector3D getViewLowerBounds();
    virtual QVector3D getViewUpperBounds();

    virtual QVector3D getModelRanges();
    virtual QVector3D getModelLowerBounds();
    virtual QVector3D getModelUpperBounds();

    virtual int getVertexCount();

    double lineWidth() const;
    void setLineWidth(double lineWidth);

    bool visible() const;
    void setVisible(bool visible);

    double pointSize() const;
    void setPointSize(double pointSize);

    QMatrix4x4 &modelMatrix();
    void setModelMatrix(const QMatrix4x4 &modelMatrix);

    const QMatrix4x4 &rotation();
    void setRotation(const QMatrix4x4 &rotation);
    void setRotation(double angle, const QVector3D &axis);

    const QMatrix4x4 &translation();
    void setTranslation(const QMatrix4x4 &translation);
    void setTranslation(const QVector3D &translation);

    const QMatrix4x4 &scale();
    void setScale(const QMatrix4x4 &scale);

    double worldScale();
    /// @brief Set object world scale
    void setWorldScale(double scale);

    bool windowScaling();
    /// @brief Set object scaling relative to the visualizer window size
    void setWindowScaling(bool windowScaling);

    double windowScale();
    /// @brief Set object scale relative to the visualizer window size, 1.0 - minimum of the window height and width
    void setWindowScale(double windowScale);

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
    QMatrix4x4 m_modelMatrix;
    QMatrix4x4 m_translationMatrix;
    QMatrix4x4 m_rotationMatrix;
    QMatrix4x4 m_scaleMatrix;

    double m_worldScale;
    bool m_windowScaling;
    double m_windowScale;

    QOpenGLBuffer m_vbo; // Protected for direct vbo access

    virtual bool updateData();
    void init();

private:
    QOpenGLVertexArrayObject m_vao;

    bool m_needsUpdateGeometry;
};

#endif // SHADERDRAWABLE_H
