// This file is a part of "Candle" application.
// This file was originally ported from "LineSegment.java" class
// of "Universal GcodeSender" application written by Will Winder
// (https://github.com/winder/Universal-G-Code-Sender)

// Copyright 2015-2025 Hayrullin Denis Ravilevich

#ifndef LINESEGMENT_H
#define LINESEGMENT_H

#include <QVector3D>
#include "pointsegment.h"

class LineSegment
{
public:
    LineSegment();
    LineSegment(const QVector3D &start, const QVector3D &end, int lineIndex);
    LineSegment(LineSegment *initial);
    ~LineSegment();

    int getLineNumber();

    QVector3D &getStart();
    void setStart(QVector3D vector);

    QVector3D &getEnd();
    void setEnd(QVector3D vector);

    const QVector3D &modelStart() const;
    void setModelStart(const QVector3D &modelStart);

    const QVector3D &modelEnd() const;
    void setModelEnd(const QVector3D &modelEnd);

    const QVector3D &axesStart() const;
    void setAxesStart(const QVector3D &axesStart);

    const QVector3D &axesEnd() const;
    void setAxesEnd(const QVector3D &axesEnd);

    void setToolHead(int head);
    int getToolhead();

    void setSpeed(double s);
    double getSpeed() const;

    bool isAbsolute() const;
    void setIsAbsolute(bool isAbsolute);

    void setIsArc(bool isA);
    bool isArc();

    bool isClockwise() const;
    void setIsClockwise(bool isClockwise);

    bool isDrawn() const;
    void setIsDrawn(bool drawn);

    bool isFastTraverse() const;
    void setIsFastTraverse(bool isF);

    bool isHighlight() const;
    void setIsHighlight(bool isHighlight);

    bool isMetric() const;
    void setIsMetric(bool isMetric);

    bool isSpline() const;
    void setIsSpline(bool isSpline);

    bool isZMovement();
    void setIsZMovement(bool isZ);

    int vertexIndex() const;
    void setVertexIndex(int vertexIndex);

    double getSpindleSpeed() const;
    void setSpindleSpeed(double spindleSpeed);

    double getDwell() const;
    void setDwell(double dwell);

    PointSegment::planes plane() const;
    void setPlane(const PointSegment::planes &plane);

    int index() const;
    void setIndex(int index);

    bool contains(const QVector3D &point);

private:
    struct Flags
    {
        uint16_t isAbsolute : 1;
        uint16_t isArc : 1;
        uint16_t isClockwise : 1;
        uint16_t isDrawn : 1;
        uint16_t isFastTraverse : 1;
        uint16_t isHighlight : 1;
        uint16_t isMetric : 1;
        uint16_t isSpline : 1;
        uint16_t isZMovement : 1;
    };

    Flags m_flags;

    int m_toolhead;

    double m_speed;
    double m_spindleSpeed;
    double m_dwell;

    QVector3D m_first, m_second;
    QVector3D m_modelStart, m_modelEnd;
    QVector3D m_axesStart, m_axesEnd;

    // Segment index
    int m_index;

    // G-code program line index
    int m_lineIndex;

    int m_vertexIndex;

    PointSegment::planes m_plane;
};

#endif // LINESEGMENT_H
