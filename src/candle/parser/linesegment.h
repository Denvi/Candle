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
    LineSegment(QVector3D a, QVector3D b, int num);
    LineSegment(LineSegment *initial);
    ~LineSegment();

    int getLineNumber();
    QList<QVector3D> getPointArray();
    QList<double> getPoints();

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
    void setIsZMovement(bool isZ);
    bool isZMovement();
    void setIsArc(bool isA);
    bool isArc();
    void setIsSpline(bool isSpline);
    bool isSpline() const;
    void setIsFastTraverse(bool isF);
    bool isFastTraverse() const;

    bool contains(const QVector3D &point);

    bool drawn() const;
    void setDrawn(bool drawn);

    bool isMetric() const;
    void setIsMetric(bool isMetric);

    bool isAbsolute() const;
    void setIsAbsolute(bool isAbsolute);

    bool isHightlight() const;
    void setIsHightlight(bool isHightlight);

    int vertexIndex() const;
    void setVertexIndex(int vertexIndex);

    double getSpindleSpeed() const;
    void setSpindleSpeed(double spindleSpeed);

    double getDwell() const;
    void setDwell(double dwell);

    bool isClockwise() const;
    void setIsClockwise(bool isClockwise);

    PointSegment::planes plane() const;
    void setPlane(const PointSegment::planes &plane);

    int index() const;
    void setIndex(int index);

private:
    int m_toolhead;
    double m_speed;
    double m_spindleSpeed;
    double m_dwell;
    QVector3D m_first, m_second;
    QVector3D m_modelStart, m_modelEnd;
    QVector3D m_axesStart, m_axesEnd;

    // Line properties
    bool m_isZMovement;
    bool m_isArc;
    bool m_isSpline;
    bool m_isClockwise;
    bool m_isFastTraverse;
    int m_lineNumber;
    bool m_drawn;
    bool m_isMetric;
    bool m_isAbsolute;
    bool m_isHightlight;
    int m_vertexIndex;
    int m_index;

    PointSegment::planes m_plane;
};

#endif // LINESEGMENT_H
