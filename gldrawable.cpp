#include "gldrawable.h"

GLDrawable::GLDrawable(QObject *parent) :
    QObject(parent)
{
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
