// This file is a part of "G-Pilot (formerly Candle)" application.
// Copyright 2015-2021 Hayrullin Denis Ravilevich
// Copyright 2025 BTS

#ifndef CURSORDRAWER_H
#define CURSORDRAWER_H

#include <QPropertyAnimation>
#include "shaderdrawable.h"

class CursorDrawer : public QObject, public ShaderDrawable
{
    Q_OBJECT
    Q_PROPERTY(float animation WRITE setAnimation)

public:
    explicit CursorDrawer();

    void setPosition(QPointF position);
    void setVisible(bool visible);

protected:
    bool updateData();
    double m_toolDiameter;
    double m_toolLength;
    double m_endLength;
    QVector3D m_position;
    double m_tipAngle;
    QColor m_color;
    float m_animation;

    double normalizeAngle(double angle);
    QVector<VertexData> createCircle(QVector3D center, double radius, int arcs, QVector3D color);


private:
    QPropertyAnimation *m_animator;

    void startAnimator();
    void setAnimation(float value);
};

#endif // CURSORDRAWER_H
