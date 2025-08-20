// This file is a part of "Candle" application.
// Copyright 2015-2025 Hayrullin Denis Ravilevich

#include "origindrawer.h"

OriginDrawer::OriginDrawer()
{
}

bool OriginDrawer::updateData()
{
    m_lines = {
        // X-axis
        {QVector3D(0, 0, 0), QVector3D(1.0, 0.0, 0.0), QVector3D(), VertexDataTypeLine},
        {QVector3D(9, 0, 0), QVector3D(1.0, 0.0, 0.0), QVector3D(), VertexDataTypeLine},
        {QVector3D(10, 0, 0), QVector3D(1.0, 0.0, 0.0), QVector3D(), VertexDataTypeLine},
        {QVector3D(8, 0.5, 0), QVector3D(1.0, 0.0, 0.0), QVector3D(), VertexDataTypeLine},
        {QVector3D(8, 0.5, 0), QVector3D(1.0, 0.0, 0.0), QVector3D(), VertexDataTypeLine},
        {QVector3D(8, -0.5, 0), QVector3D(1.0, 0.0, 0.0), QVector3D(), VertexDataTypeLine},
        {QVector3D(8, -0.5, 0), QVector3D(1.0, 0.0, 0.0), QVector3D(), VertexDataTypeLine},
        {QVector3D(10, 0, 0), QVector3D(1.0, 0.0, 0.0), QVector3D(), VertexDataTypeLine},

        // Y-axis
        {QVector3D(0, 0, 0), QVector3D(0.0, 1.0, 0.0), QVector3D(), VertexDataTypeLine},
        {QVector3D(0, 9, 0), QVector3D(0.0, 1.0, 0.0), QVector3D(), VertexDataTypeLine},
        {QVector3D(0, 10, 0), QVector3D(0.0, 1.0, 0.0), QVector3D(), VertexDataTypeLine},
        {QVector3D(0.5, 8, 0), QVector3D(0.0, 1.0, 0.0), QVector3D(), VertexDataTypeLine},
        {QVector3D(0.5, 8, 0), QVector3D(0.0, 1.0, 0.0), QVector3D(), VertexDataTypeLine},
        {QVector3D(-0.5, 8, 0), QVector3D(0.0, 1.0, 0.0), QVector3D(), VertexDataTypeLine},
        {QVector3D(-0.5, 8, 0), QVector3D(0.0, 1.0, 0.0), QVector3D(), VertexDataTypeLine},
        {QVector3D(0, 10, 0), QVector3D(0.0, 1.0, 0.0), QVector3D(), VertexDataTypeLine},

        // Z-axis
        {QVector3D(0, 0, 0), QVector3D(0.0, 0.0, 1.0), QVector3D(), VertexDataTypeLine},
        {QVector3D(0, 0, 9), QVector3D(0.0, 0.0, 1.0), QVector3D(), VertexDataTypeLine},
        {QVector3D(0, 0, 10), QVector3D(0.0, 0.0, 1.0), QVector3D(), VertexDataTypeLine},
        {QVector3D(0.5, 0, 8), QVector3D(0.0, 0.0, 1.0), QVector3D(), VertexDataTypeLine},
        {QVector3D(0.5, 0, 8), QVector3D(0.0, 0.0, 1.0), QVector3D(), VertexDataTypeLine},
        {QVector3D(-0.5, 0, 8), QVector3D(0.0, 0.0, 1.0), QVector3D(), VertexDataTypeLine},
        {QVector3D(-0.5, 0, 8), QVector3D(0.0, 0.0, 1.0), QVector3D(), VertexDataTypeLine},
        {QVector3D(0, 0, 10), QVector3D(0.0, 0.0, 1.0), QVector3D(), VertexDataTypeLine},

        // 2x2 rect
        {QVector3D(1, 1, 0), QVector3D(1.0, 0.0, 0.0), QVector3D(), VertexDataTypeLine},
        {QVector3D(-1, 1, 0), QVector3D(1.0, 0.0, 0.0), QVector3D(), VertexDataTypeLine},
        {QVector3D(-1, 1, 0), QVector3D(1.0, 0.0, 0.0), QVector3D(), VertexDataTypeLine},
        {QVector3D(-1, -1, 0), QVector3D(1.0, 0.0, 0.0), QVector3D(), VertexDataTypeLine},
        {QVector3D(-1, -1, 0), QVector3D(1.0, 0.0, 0.0), QVector3D(), VertexDataTypeLine},
        {QVector3D(1, -1, 0), QVector3D(1.0, 0.0, 0.0), QVector3D(), VertexDataTypeLine},
        {QVector3D(1, -1, 0), QVector3D(1.0, 0.0, 0.0), QVector3D(), VertexDataTypeLine},
        {QVector3D(1, 1, 0), QVector3D(1.0, 0.0, 0.0), QVector3D(), VertexDataTypeLine}        
      };
    return true;
}
