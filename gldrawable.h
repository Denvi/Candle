#ifndef GLDRAWABLE_H
#define GLDRAWABLE_H

#include <QObject>
#include <QVector3D>
#include <QGLWidget>

class GLDrawable : public QObject
{
    Q_OBJECT
public:
    explicit GLDrawable(QObject *parent = 0);
    virtual void draw();
    virtual QVector3D getSizes();
    virtual QVector3D getMinimumExtremes();
    virtual QVector3D getMaximumExtremes();

signals:

public slots:

};

#endif // GLDRAWABLE_H
