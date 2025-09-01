// This file is a part of "Candle" application.
// Copyright 2015-2025 Hayrullin Denis Ravilevich

#include "tooldrawer.h"

ToolDrawer::ToolDrawer()
{
    m_toolDiameter = 3;
    m_toolLength = 15;
    m_toolPosition = QVector3D(0, 0, 0);
    m_spinAngle = 0;
}

bool ToolDrawer::updateData()
{
    const int arcs = 4;

    // Clear data
    m_lines.clear();
    m_points.clear();

    // Prepare vertex
    VertexData vertex;
    vertex.type = VertexDataTypeLine;
    vertex.color = Util::colorToVector(m_color);//QVector3D(1.0, 0.6, 0.0);

    // Draw circles
    // Bottom
    m_lines += createCircle(QVector3D(m_toolPosition.x(), m_toolPosition.y(), m_toolPosition.z() + m_endLength),
                            m_toolDiameter / 2, 20, vertex.color);

    // Top
    m_lines += createCircle(QVector3D(m_toolPosition.x(), m_toolPosition.y(), m_toolPosition.z() + m_toolLength),
                            m_toolDiameter / 2, 20, vertex.color);

    // Zero Z circle
    if (m_endLength == 0) {
        m_lines += createCircle(QVector3D(m_toolPosition.x(), m_toolPosition.y(), 0),
                                m_toolDiameter / 2, 20, vertex.color);
    }

    // Draw lines
    for (int i = 0; i < arcs; i++) {
         double x = m_toolPosition.x() + m_toolDiameter / 2 * cos(m_spinAngle / 180 * M_PI + (2 * M_PI / arcs) * i);
         double y = m_toolPosition.y() + m_toolDiameter / 2 * sin(m_spinAngle / 180 * M_PI + (2 * M_PI / arcs) * i);

        // Side lines
        vertex.position = QVector3D(x, y, m_toolPosition.z() + m_endLength);
        m_lines.append(vertex);
        vertex.position = QVector3D(x, y, m_toolPosition.z() + m_toolLength);
        m_lines.append(vertex);

        // Bottom lines
        vertex.position = QVector3D(m_toolPosition.x(), m_toolPosition.y(), m_toolPosition.z());
        m_lines.append(vertex);
        vertex.position = QVector3D(x, y, m_toolPosition.z() + m_endLength);
        m_lines.append(vertex);

        // Top lines
        vertex.position = QVector3D(m_toolPosition.x(), m_toolPosition.y(), m_toolPosition.z() + m_toolLength);
        m_lines.append(vertex);
        vertex.position = QVector3D(x, y, m_toolPosition.z() + m_toolLength);
        m_lines.append(vertex);
    }

    for (int i = 0; i < arcs; i++) {
        // Zero Z lines
        double x = m_toolPosition.x() + m_toolDiameter / 2 * cos(m_spinAngle / 180 * M_PI + (2 * M_PI / arcs) * i);
        double y = m_toolPosition.y() + m_toolDiameter / 2 * sin(m_spinAngle / 180 * M_PI + (2 * M_PI / arcs) * i);

        vertex.position = QVector3D(m_toolPosition.x(), m_toolPosition.y(), 0);
        m_lines.append(vertex);
        vertex.position = QVector3D(x, y, 0);
        m_lines.append(vertex);
    }

    return true;
}
QColor ToolDrawer::color() const
{
    return m_color;
}

void ToolDrawer::setColor(const QColor &color)
{
    m_color = color;
}


QVector<VertexData> ToolDrawer::createCircle(QVector3D center, double radius, int arcs, QVector3D color)
{
    // Vertices
    QVector<VertexData> circle;

    // Prepare vertex
    VertexData vertex;
    vertex.type = VertexDataTypeLine;
    vertex.color = color;

    // Create line loop
    for (int i = 0; i <= arcs; i++) {
        double angle = 2 * M_PI * i / arcs;
        double x = center.x() + radius * cos(angle);
        double y = center.y() + radius * sin(angle);

        if (i > 1) {
            circle.append(circle.last());
        }
        else if (i == arcs) circle.append(circle.first());

        vertex.position = QVector3D(x, y, center.z());
        circle.append(vertex);
    }

    return circle;
}

double ToolDrawer::toolDiameter() const
{
    return m_toolDiameter;
}

void ToolDrawer::setToolDiameter(double toolDiameter)
{
    if (m_toolDiameter != toolDiameter) {
        m_toolDiameter = toolDiameter;
        update();
    }
}
double ToolDrawer::toolLength() const
{
    return m_toolLength;
}

void ToolDrawer::setToolLength(double toolLength)
{
    if (m_toolLength != toolLength) {
        m_toolLength = toolLength;
        update();
    }
}
QVector3D ToolDrawer::toolPosition() const
{
    return m_toolPosition;
}

void ToolDrawer::setToolPosition(const QVector3D &toolPosition)
{
    if (m_toolPosition != toolPosition) {
        m_toolPosition = toolPosition;
        update();
    }
}

double ToolDrawer::spinAngle() const
{
    return m_spinAngle;
}

void ToolDrawer::setSpinAngle(double rotationAngle)
{
    if (m_spinAngle != rotationAngle) {
        m_spinAngle = rotationAngle;
        update();
    }
}

void ToolDrawer::spin(double angle)
{
    setSpinAngle(normalizeAngle(m_spinAngle + angle));
}

double ToolDrawer::toolAngle() const
{
    return m_toolAngle;
}

void ToolDrawer::setToolAngle(double toolAngle)
{
    if (m_toolAngle != toolAngle) {
        m_toolAngle = toolAngle;

        m_endLength = m_toolAngle > 0 && m_toolAngle < 180 ? m_toolDiameter / 2 / tan(m_toolAngle / 180 * M_PI / 2) : 0;
        if (m_toolLength < m_endLength) m_toolLength = m_endLength;

        update();
    }
}

double ToolDrawer::normalizeAngle(double angle)
{
    while (angle < 0) angle += 360;
    while (angle > 360) angle -= 360;
    
    return angle;
}