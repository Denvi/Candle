#ifndef HEIGHTMAPINTERPOLATIONDRAWER_H
#define HEIGHTMAPINTERPOLATIONDRAWER_H

#include <QObject>
#include <QVector>
#include <QVector3D>
#include "gldrawable.h"
#include "util.h"

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
    double Min(double v1, double v2);
    double Max(double v1, double v2);
};

#endif // HEIGHTMAPINTERPOLATIONDRAWER_H
