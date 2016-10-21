// This file is a part of "Candle" application.
// Copyright 2015-2016 Hayrullin Denis Ravilevich

#ifndef DITHERDRAWER_H
#define DITHERDRAWER_H

#include <QObject>
#include <QVector3D>
#include "parser/linesegment.h"
#include "parser/gcodeviewparse.h"
#include "shaderdrawable.h"

class DitherDrawer : public QObject, public ShaderDrawable
{
    Q_OBJECT
public:
    enum GrayscaleCode { S, Z };

    explicit DitherDrawer();

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

    bool getIgnoreZ() const;
    void setIgnoreZ(bool ignoreZ);

    bool getGrayscaleSegments() const;
    void setGrayscaleSegments(bool grayscaleSegments);

    GrayscaleCode grayscaleCode() const;
    void setGrayscaleCode(const GrayscaleCode &grayscaleCode);

    int grayscaleMin() const;
    void setGrayscaleMin(int grayscaleMin);

    int grayscaleMax() const;
    void setGrayscaleMax(int grayscaleMax);

signals:

public slots:

private slots:
    void onTimerVertexUpdate();

private:
    GcodeViewParse *m_viewParser;
    bool m_simplify;
    double m_simplifyPrecision;

    bool m_ignoreZ;
    bool m_grayscaleSegments;
    GrayscaleCode m_grayscaleCode;
    int m_grayscaleMin;
    int m_grayscaleMax;

    bool m_geometryUpdated;

    QTimer m_timerVertexUpdate;

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

#endif // DITHERDRAWER_H
