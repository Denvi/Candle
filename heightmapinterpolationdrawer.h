#ifndef HEIGHTMAPINTERPOLATIONDRAWER_H
#define HEIGHTMAPINTERPOLATIONDRAWER_H

#include <QObject>
#include <QVector>
#include <QVector3D>
#include "gldrawable.h"

class HeightMapInterpolationDrawer : public GLDrawable
{
public:
    explicit HeightMapInterpolationDrawer(QObject *parent = 0);
    void draw();

    QVector<QVector<double> > *data() const;
    void setData(QVector<QVector<double> > *data);

    QRectF borderRect() const;
    void setBorderRect(const QRectF &borderRect);

private:
    QRectF m_borderRect;
    double m_gridSize;
    QVector<QVector<double>> *m_data;
};

#endif // HEIGHTMAPINTERPOLATIONDRAWER_H
