// This file is a part of "Candle" application.
// Copyright 2015-2025 Hayrullin Denis Ravilevich

#include "origindrawer.h"

OriginDrawer::OriginDrawer()
{
    setWorldScale(10.0);
}

bool OriginDrawer::updateData()
{
    m_lines = {
        // X-axis
        {QVector3D(0, 0, 0), QVector3D(1.0f, 0, 0), QVector3D(), VertexDataTypeLine},
        {QVector3D(1.0f, 0, 0), QVector3D(1.0f, 0, 0), QVector3D(), VertexDataTypeLine},
        {QVector3D(0.8f, 0.05f, 0), QVector3D(1.0f, 0, 0), QVector3D(), VertexDataTypeLine},
        {QVector3D(0.8f, -0.05f, 0), QVector3D(1.0f, 0, 0), QVector3D(), VertexDataTypeLine},
        {QVector3D(1.0f, 0, 0), QVector3D(1.0f, 0, 0), QVector3D(), VertexDataTypeLine},
        {QVector3D(0.8f, 0.05f, 0), QVector3D(1.0f, 0, 0), QVector3D(), VertexDataTypeLine},
        {QVector3D(0.8f, -0.05f, 0), QVector3D(1.0f, 0, 0), QVector3D(), VertexDataTypeLine},
        {QVector3D(1.0f, 0, 0), QVector3D(1.0f, 0, 0), QVector3D(), VertexDataTypeLine},

        // Y-axis
        {QVector3D(0, 0, 0), QVector3D(0, 1.0f, 0), QVector3D(), VertexDataTypeLine},
        {QVector3D(0, 1.0f, 0), QVector3D(0, 1.0f, 0), QVector3D(), VertexDataTypeLine},
        {QVector3D(-0.05f, 0.8f, 0), QVector3D(0, 1.0f, 0), QVector3D(), VertexDataTypeLine},
        {QVector3D(0.05f, 0.8f, 0), QVector3D(0, 1.0f, 0), QVector3D(), VertexDataTypeLine},
        {QVector3D(0, 1.0f, 0), QVector3D(0, 1.0f, 0), QVector3D(), VertexDataTypeLine},
        {QVector3D(-0.05f, 0.8f, 0), QVector3D(0, 1.0f, 0), QVector3D(), VertexDataTypeLine},
        {QVector3D(0.05f, 0.8f, 0), QVector3D(0, 1.0f, 0), QVector3D(), VertexDataTypeLine},
        {QVector3D(0, 1.0f, 0), QVector3D(0, 1.0f, 0), QVector3D(), VertexDataTypeLine},

        // Z-axis
        {QVector3D(0, 0, 0), QVector3D(0, 0, 1.0f), QVector3D(), VertexDataTypeLine},
        {QVector3D(0, 0, 1.0f), QVector3D(0, 0, 1.0f), QVector3D(), VertexDataTypeLine},
        {QVector3D(0, 0, 1.0f), QVector3D(0, 0, 1.0f), QVector3D(), VertexDataTypeLine},
        {QVector3D(-0.05f, 0, 0.8f), QVector3D(0, 0, 1.0f), QVector3D(), VertexDataTypeLine},
        {QVector3D(-0.05f, 0, 0.8f), QVector3D(0, 0, 1.0f), QVector3D(), VertexDataTypeLine},
        {QVector3D(0.05f, 0, 0.8f), QVector3D(0, 0, 1.0f), QVector3D(), VertexDataTypeLine},
        {QVector3D(0.05f, 0, 0.8f), QVector3D(0, 0, 1.0f), QVector3D(), VertexDataTypeLine},
        {QVector3D(0, 0, 1.0f), QVector3D(0, 0, 1.0f), QVector3D(), VertexDataTypeLine},

        // 2x2 rect
        {QVector3D(0.1f, 0.1f, 0), QVector3D(1.0f, 0, 0), QVector3D(), VertexDataTypeLine},
        {QVector3D(-0.1f, 0.1f, 0), QVector3D(1.0f, 0, 0), QVector3D(), VertexDataTypeLine},
        {QVector3D(-0.1f, 0.1f, 0), QVector3D(1.0f, 0, 0), QVector3D(), VertexDataTypeLine},
        {QVector3D(-0.1f, -0.1f, 0), QVector3D(1.0f, 0, 0), QVector3D(), VertexDataTypeLine},
        {QVector3D(-0.1f, -0.1f, 0), QVector3D(1.0f, 0, 0), QVector3D(), VertexDataTypeLine},
        {QVector3D(0.1f, -0.1f, 0), QVector3D(1.0f, 0, 0), QVector3D(), VertexDataTypeLine},
        {QVector3D(0.1f, -0.1f, 0), QVector3D(1.0f, 0, 0), QVector3D(), VertexDataTypeLine},
        {QVector3D(0.1f, 0.1f, 0), QVector3D(1.0f, 0, 0), QVector3D(), VertexDataTypeLine}
    };

    return true;
}