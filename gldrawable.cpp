// This file is a part of "grblControl" application.
// Copyright 2015 Hayrullin Denis Ravilevich

#include "gldrawable.h"

GLDrawable::GLDrawable(QObject *parent) :
    QObject(parent)
{
    m_lineWidth = 1;
}

void GLDrawable::draw()
{
}

QVector3D GLDrawable::getSizes()
{
    return QVector3D(0, 0, 0);
}

QVector3D GLDrawable::getMinimumExtremes()
{
    return QVector3D(0, 0, 0);
}

QVector3D GLDrawable::getMaximumExtremes()
{
    return QVector3D(0, 0, 0);
}

int GLDrawable::getLinesCount()
{
    return 0;
}
double GLDrawable::lineWidth() const
{
    return m_lineWidth;
}

void GLDrawable::setLineWidth(double lineWidth)
{
    m_lineWidth = lineWidth;
}

bool GLDrawable::visible() const
{
    return m_visible;
}

void GLDrawable::setVisible(bool visible)
{
    m_visible = visible;
}


