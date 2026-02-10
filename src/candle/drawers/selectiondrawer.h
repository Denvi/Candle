// This file is a part of "Candle" application.
// Copyright 2015-2025 Hayrullin Denis Ravilevich

#ifndef SELECTIONDRAWER_H
#define SELECTIONDRAWER_H

#include "shaderdrawable.h"

class SelectionDrawer : public ShaderDrawable
{        
public:
    SelectionDrawer();

    QColor color() const;
    void setColor(const QColor &color);

    const QVector3D &position();
    void setPosition(const QVector3D &position);

    void drawPainter(QPainter &painter, const QMatrix4x4 &projection, double ratio) override;

private:
    QColor m_color;
    QVector3D m_position;
};

#endif // SELECTIONDRAWER_H