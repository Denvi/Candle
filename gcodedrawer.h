// This file is a part of "grblControl" application.
// Copyright 2015 Hayrullin Denis Ravilevich

#ifndef GCODEDRAWER_H
#define GCODEDRAWER_H

#include <QObject>
#include <QVector3D>
#include "linesegment.h"
#include "gcodeviewparse.h"
#include "shaderdrawable.h"

class GcodeDrawer : public ShaderDrawable
{
public:
    explicit GcodeDrawer();

    QVector3D getSizes();
    QVector3D getMinimumExtremes();
    QVector3D getMaximumExtremes();

    void setViewParser(GcodeViewParse* viewParser);
    GcodeViewParse* viewParser();

signals:

public slots:

private:
    GcodeViewParse *m_viewParser;

    void updateData();
};

#endif // GCODEDRAWER_H
