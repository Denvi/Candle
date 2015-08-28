// This file is a part of "grblControl" application.
// Copyright 2015 Hayrullin Denis Ravilevich

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
    virtual int getLinesCount();

    double lineWidth() const;
    void setLineWidth(double lineWidth);

    bool visible() const;
    void setVisible(bool visible);

signals:

public slots:   

protected:
    double m_lineWidth;
    bool m_visible;

};

#endif // GLDRAWABLE_H
