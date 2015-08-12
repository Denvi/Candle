// This file is a part of "grblControl" application.
// Copyright 2015 Hayrullin Denis Ravilevich

#ifndef GCODEDRAWER_H
#define GCODEDRAWER_H

#include <QObject>
#include <QVector3D>
#include "linesegment.h"
#include "gcodeviewparse.h"
#include "gldrawable.h"

class GcodeDrawer : public GLDrawable
{
    Q_OBJECT
public:
    explicit GcodeDrawer(QObject *parent = 0);
    void draw();
    QVector3D getSizes();
    QVector3D getMinimumExtremes();
    QVector3D getMaximumExtremes();
    void setViewParser(GcodeViewParse* viewParser);
    int getLinesCount();

    double lineWidth() const;
    void setLineWidth(double lineWidth);

signals:

public slots:

private:
    GcodeViewParse *m_viewParser;

    double m_lineWidth;
};

#endif // GCODEDRAWER_H
