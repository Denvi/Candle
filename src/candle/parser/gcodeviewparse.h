// This file is a part of "Candle" application.
// This file was originally ported from "GcodeViewParse.java" class
// of "Universal GcodeSender" application written by Will Winder
// (https://github.com/winder/Universal-G-Code-Sender)

// Copyright 2015-2025 Hayrullin Denis Ravilevich

#ifndef GCODEVIEWPARSE_H
#define GCODEVIEWPARSE_H

#include <QObject>
#include <QVector3D>
#include <QVector2D>
#include "linesegment.h"
#include "gcodeparser.h"
#include "../utils/util.h"

class GcodeViewParse : public QObject
{
    Q_OBJECT
public:
    enum RotationAxis {
        RotationAxisA,
        RotationAxisB,
        RotationAxisC
    };

    explicit GcodeViewParse(QObject *parent = 0);
    ~GcodeViewParse();

    QVector3D &getViewLowerBounds();
    QVector3D &getViewUpperBounds();

    QVector3D &getModelLowerBounds();
    QVector3D &getModelUpperBounds();

    double getModelMinLineLength() const;
    QSize getModelResolution() const;

    void setAxisRotationVector(RotationAxis axis, const QVector3D &vector);
    const QVector3D &getAxisRotationVector(RotationAxis axis);

    bool axisRotationUsed(RotationAxis axis);

    QList<LineSegment*> toObjRedux(QList<QString> gcode, double arcPrecision, bool arcDegreeMode);
    QList<LineSegment*> getLineSegmentList();
    QList<LineSegment*> getLinesFromParser(GcodeParser *gp, double arcPrecision, bool arcDegreeMode);

    QList<LineSegment*> *getLines();
    QVector<QList<int>> &getLinesIndexes();

    void reset();

signals:

public slots:

private:
    bool absoluteMode;
    bool absoluteIJK;

    // Parsed object
    QVector3D m_viewLowerBounds;
    QVector3D m_viewUpperBounds;
    QVector3D m_modelLowerBounds;
    QVector3D m_modelUpperBounds;

    double m_modelMinLineLength;

    QList<LineSegment*> m_lines;
    QVector<QList<int>> m_lineIndexes;    

    // Parsing state.
    QVector3D lastPoint;
    int currentLine; // for assigning line numbers to segments.

    QMap<RotationAxis, QVector3D> m_axesRotationVectors;

    // Debug
    bool debug;
    void updateViewBounds(const QVector3D &point);
    void updateModelBounds(const QVector3D &point);

    void updateModelMinLineLength(const QVector3D &start, const QVector3D &end);
};

#endif // GCODEVIEWPARSE_H
