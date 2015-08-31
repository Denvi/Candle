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
    GcodeViewParse* viewParser();

    int getLinesCount();

signals:

public slots:

private:
    GcodeViewParse *m_viewParser;
};

#endif // GCODEDRAWER_H
