// This file is a part of "Candle" application.
// Copyright 2015-2016 Hayrullin Denis Ravilevich

#ifndef INTERPOLATION
#define INTERPOLATION

#include <QVector>
#include <QRectF>
#include <QAbstractTableModel>
#include <cmath>

class Interpolation
{
public:
    static double cubicInterpolate(double p[4], double x)
    {
        return p[1] + 0.5 * x * (p[2] - p[0] + x *(2.0 * p[0] - 5.0 * p[1]
                + 4.0 * p[2] - p[3] + x * (3.0 * (p[1] - p[2]) + p[3] - p[0])));
    }

    static double bicubicInterpolate(double p[4][4], double x, double y)
    {
        double arr[4];
        arr[0] = cubicInterpolate(p[0], x);
        arr[1] = cubicInterpolate(p[1], x);
        arr[2] = cubicInterpolate(p[2], x);
        arr[3] = cubicInterpolate(p[3], x);
        return cubicInterpolate(arr, y);
    }

    static double bicubicInterpolate(QRectF borderRect, QAbstractTableModel *basePoints, double x, double y)
    {
        // Setup grid
        int gridPointsX = basePoints->columnCount();
        int gridPointsY = basePoints->rowCount();

        double gridStepX = gridPointsX > 1 ? borderRect.width() / (gridPointsX - 1) : 0;
        double gridStepY = gridPointsY > 1 ? borderRect.height() / (gridPointsY - 1) : 0;

        // Get 16 points
        x -= borderRect.x();
        y -= borderRect.y();

        int ix = trunc(x / gridStepX);
        int iy = trunc(y / gridStepY);

        if (ix > basePoints->columnCount() - 2) ix = basePoints->columnCount() - 2;
        if (iy > basePoints->rowCount() - 2) iy = basePoints->rowCount() - 2;

        double p[4][4];

        p[0][0] = basePoints->data(basePoints->index((iy > 0 ? iy - 1 : iy), (ix > 0 ? ix - 1 : ix)), Qt::UserRole).toDouble();
        p[0][1] = basePoints->data(basePoints->index((iy > 0 ? iy - 1 : iy), ix), Qt::UserRole).toDouble();
        p[0][2] = basePoints->data(basePoints->index((iy > 0 ? iy - 1 : iy), ix + 1), Qt::UserRole).toDouble();
        p[0][3] = basePoints->data(basePoints->index((iy > 0 ? iy - 1 : iy), (ix < basePoints->columnCount() - 2 ? ix + 2: ix + 1)), Qt::UserRole).toDouble();

        p[1][0] = basePoints->data(basePoints->index(iy, ix > 0 ? ix - 1 : ix), Qt::UserRole).toDouble();
        p[1][1] = basePoints->data(basePoints->index(iy, ix), Qt::UserRole).toDouble();
        p[1][2] = basePoints->data(basePoints->index(iy, ix + 1), Qt::UserRole).toDouble();
        p[1][3] = basePoints->data(basePoints->index(iy, ix < basePoints->columnCount() - 2 ? ix + 2: ix + 1), Qt::UserRole).toDouble();

        p[2][0] = basePoints->data(basePoints->index(iy + 1, ix > 0 ? ix - 1 : ix), Qt::UserRole).toDouble();
        p[2][1] = basePoints->data(basePoints->index(iy + 1, ix), Qt::UserRole).toDouble();
        p[2][2] = basePoints->data(basePoints->index(iy + 1, ix + 1), Qt::UserRole).toDouble();
        p[2][3] = basePoints->data(basePoints->index(iy + 1, ix < basePoints->columnCount() - 2 ? ix + 2 : ix + 1), Qt::UserRole).toDouble();

        p[3][0] = basePoints->data(basePoints->index(iy < basePoints->rowCount() - 2 ? iy + 2 : iy + 1, ix > 0 ? ix - 1 : ix), Qt::UserRole).toDouble();
        p[3][1] = basePoints->data(basePoints->index(iy < basePoints->rowCount() - 2 ? iy + 2 : iy + 1, ix), Qt::UserRole).toDouble();
        p[3][2] = basePoints->data(basePoints->index(iy < basePoints->rowCount() - 2 ? iy + 2 : iy + 1, ix + 1), Qt::UserRole).toDouble();
        p[3][3] = basePoints->data(basePoints->index(iy < basePoints->rowCount() - 2 ? iy + 2 : iy + 1, ix < basePoints->columnCount() - 2 ? ix + 2 : ix + 1), Qt::UserRole).toDouble();

        // Interpolate
        return Interpolation::bicubicInterpolate(p, x / gridStepX - ix, y / gridStepY - iy);
    }
};

#endif // INTERPOLATION

