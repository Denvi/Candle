// This file is a part of "Candle" application.
// G5/G5.1 spline support

// Copyright 2015-2025 kimstik
// Assisted by intelligence

#ifndef SPLINEPROPERTIES_H
#define SPLINEPROPERTIES_H

#include <QVector3D>

enum SplineType {
    CUBIC_SPLINE,      // G5
    QUADRATIC_SPLINE   // G5.1
};

class SplineProperties
{
public:
    explicit SplineProperties();
    SplineType type;
    QVector3D *controlPoint1;
    QVector3D *controlPoint2;  // NULL for quadratic
};

#endif // SPLINEPROPERTIES_H
