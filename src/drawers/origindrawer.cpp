#include "origindrawer.h"

OriginDrawer::OriginDrawer()
{
}

bool OriginDrawer::updateData()
{
    m_lines = QVector<VertexData>()
        // X-axis
        << VertexData(QVector3D(0, 0, 0), QVector3D(1.0, 0.0, 0.0), QVector3D(sNan, sNan, sNan))
        << VertexData(QVector3D(9, 0, 0), QVector3D(1.0, 0.0, 0.0), QVector3D(sNan, sNan, sNan))
        << VertexData(QVector3D(10, 0, 0), QVector3D(1.0, 0.0, 0.0), QVector3D(sNan, sNan, sNan))
        << VertexData(QVector3D(8, 0.5, 0), QVector3D(1.0, 0.0, 0.0), QVector3D(sNan, sNan, sNan))
        << VertexData(QVector3D(8, 0.5, 0), QVector3D(1.0, 0.0, 0.0), QVector3D(sNan, sNan, sNan))
        << VertexData(QVector3D(8, -0.5, 0), QVector3D(1.0, 0.0, 0.0), QVector3D(sNan, sNan, sNan))
        << VertexData(QVector3D(8, -0.5, 0), QVector3D(1.0, 0.0, 0.0), QVector3D(sNan, sNan, sNan))
        << VertexData(QVector3D(10, 0, 0), QVector3D(1.0, 0.0, 0.0), QVector3D(sNan, sNan, sNan))

        // Y-axis
        << VertexData(QVector3D(0, 0, 0), QVector3D(0.0, 1.0, 0.0), QVector3D(sNan, sNan, sNan))
        << VertexData(QVector3D(0, 9, 0), QVector3D(0.0, 1.0, 0.0), QVector3D(sNan, sNan, sNan))
        << VertexData(QVector3D(0, 10, 0), QVector3D(0.0, 1.0, 0.0), QVector3D(sNan, sNan, sNan))
        << VertexData(QVector3D(0.5, 8, 0), QVector3D(0.0, 1.0, 0.0), QVector3D(sNan, sNan, sNan))
        << VertexData(QVector3D(0.5, 8, 0), QVector3D(0.0, 1.0, 0.0), QVector3D(sNan, sNan, sNan))
        << VertexData(QVector3D(-0.5, 8, 0), QVector3D(0.0, 1.0, 0.0), QVector3D(sNan, sNan, sNan))
        << VertexData(QVector3D(-0.5, 8, 0), QVector3D(0.0, 1.0, 0.0), QVector3D(sNan, sNan, sNan))
        << VertexData(QVector3D(0, 10, 0), QVector3D(0.0, 1.0, 0.0), QVector3D(sNan, sNan, sNan))

        // Z-axis
        << VertexData(QVector3D(0, 0, 0), QVector3D(0.0, 0.0, 1.0), QVector3D(sNan, sNan, sNan))
        << VertexData(QVector3D(0, 0, 9), QVector3D(0.0, 0.0, 1.0), QVector3D(sNan, sNan, sNan))
        << VertexData(QVector3D(0, 0, 10), QVector3D(0.0, 0.0, 1.0), QVector3D(sNan, sNan, sNan))
        << VertexData(QVector3D(0.5, 0, 8), QVector3D(0.0, 0.0, 1.0), QVector3D(sNan, sNan, sNan))
        << VertexData(QVector3D(0.5, 0, 8), QVector3D(0.0, 0.0, 1.0), QVector3D(sNan, sNan, sNan))
        << VertexData(QVector3D(-0.5, 0, 8), QVector3D(0.0, 0.0, 1.0), QVector3D(sNan, sNan, sNan))
        << VertexData(QVector3D(-0.5, 0, 8), QVector3D(0.0, 0.0, 1.0), QVector3D(sNan, sNan, sNan))
        << VertexData(QVector3D(0, 0, 10), QVector3D(0.0, 0.0, 1.0), QVector3D(sNan, sNan, sNan))

        // 2x2 rect
        << VertexData(QVector3D(1, 1, 0), QVector3D(1.0, 0.0, 0.0), QVector3D(sNan, sNan, sNan))
        << VertexData(QVector3D(-1, 1, 0), QVector3D(1.0, 0.0, 0.0), QVector3D(sNan, sNan, sNan))
        << VertexData(QVector3D(-1, 1, 0), QVector3D(1.0, 0.0, 0.0), QVector3D(sNan, sNan, sNan))
        << VertexData(QVector3D(-1, -1, 0), QVector3D(1.0, 0.0, 0.0), QVector3D(sNan, sNan, sNan))
        << VertexData(QVector3D(-1, -1, 0), QVector3D(1.0, 0.0, 0.0), QVector3D(sNan, sNan, sNan))
        << VertexData(QVector3D(1, -1, 0), QVector3D(1.0, 0.0, 0.0), QVector3D(sNan, sNan, sNan))
        << VertexData(QVector3D(1, -1, 0), QVector3D(1.0, 0.0, 0.0), QVector3D(sNan, sNan, sNan))
        << VertexData(QVector3D(1, 1, 0), QVector3D(1.0, 0.0, 0.0), QVector3D(sNan, sNan, sNan));

    return true;
}
