// This file is a part of "grblControl" application.
// Copyright 2015 Hayrullin Denis Ravilevich

#ifndef GCODEDRAWER_H
#define GCODEDRAWER_H

#include <QObject>
#include <QVector3D>
#include "parser/linesegment.h"
#include "parser/gcodeviewparse.h"
#include "shaderdrawable.h"

class GcodeDrawer : public ShaderDrawable
{
public:
    explicit GcodeDrawer();

    void update();
    void update(QList<int> indexes);
    bool updateData();

    QVector3D getSizes();
    QVector3D getMinimumExtremes();
    QVector3D getMaximumExtremes();

    void setViewParser(GcodeViewParse* viewParser);
    GcodeViewParse* viewParser();        

    bool simplify() const;
    void setSimplify(bool simplify);

    double simplifyPrecision() const;
    void setSimplifyPrecision(double simplifyPrecision);

    bool geometryUpdated();

    QColor colorNormal() const;
    void setColorNormal(const QColor &colorNormal);

    QColor colorHighlight() const;
    void setColorHighlight(const QColor &colorHighlight);

    QColor colorZMovement() const;
    void setColorZMovement(const QColor &colorZMovement);

    QColor colorDrawn() const;
    void setColorDrawn(const QColor &colorDrawn);

    QColor colorStart() const;
    void setColorStart(const QColor &colorStart);

    QColor colorEnd() const;
    void setColorEnd(const QColor &colorEnd);

signals:

public slots:

private:
    GcodeViewParse *m_viewParser;
    bool m_simplify;
    double m_simplifyPrecision;
    bool m_geometryUpdated;

    QColor m_colorNormal;
    QColor m_colorDrawn;
    QColor m_colorHighlight;
    QColor m_colorZMovement;
    QColor m_colorStart;
    QColor m_colorEnd;

    QList<int> m_indexes;

    int getSegmentType(LineSegment *segment);
    QVector3D getSegmentColor(LineSegment *segment);
};

#endif // GCODEDRAWER_H
