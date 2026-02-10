// This file is a part of "Candle" application.
// Copyright 2015-2021 Hayrullin Denis Ravilevich

#ifndef MACHINEBOUNDSDRAWER_H
#define MACHINEBOUNDSDRAWER_H

#include <QObject>
#include <QAbstractTableModel>
#include "shaderdrawable.h"

class MachineBoundsDrawer : public ShaderDrawable
{
public:
    MachineBoundsDrawer();

    QSizeF gridSize() const;
    void setGridSize(const QSizeF &gridSize);

    QRectF borderRect() const;
    void setBorderRect(const QRectF &borderRect);

    QVector3D getMinimumExtremes();
    QVector3D getMaximumExtremes();

protected:
    bool updateData();

private:
    QSizeF m_gridSize;
    QRectF m_borderRect;
};

#endif // MACHINEBOUNDSDRAWER_H