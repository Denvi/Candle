// This file is a part of "Candle" application.
// This file was originally ported from "LineSegment.java" class
// of "Universal GcodeSender" application written by Will Winder
// (https://github.com/winder/Universal-G-Code-Sender)

// Copyright 2015-2025 Hayrullin Denis Ravilevich

#include "linesegment.h"
#include <QDebug>

LineSegment::LineSegment()
{
    m_flags = {false};
    m_flags.isMetric = true;
    m_flags.isAbsolute = true;

    m_toolhead = 0;
    m_vertexIndex = -1;
    m_index = -1;
}

LineSegment::LineSegment(const QVector3D &start, const QVector3D &end, int lineNumber) : LineSegment()
{
    m_first = start;
    m_second = end;
    m_lineIndex = lineNumber;
}

LineSegment::LineSegment(LineSegment *initial)
{
    m_flags = initial->m_flags;
    m_toolhead = initial->m_toolhead;
    m_first = initial->m_first;
    m_second = initial->m_second;
    m_lineIndex = initial->m_lineIndex;
    m_speed = initial->m_speed;
    m_vertexIndex = initial->m_vertexIndex;
    m_axesStart = initial->m_axesStart;
    m_axesEnd = initial->m_axesEnd;
    m_modelStart = initial->m_modelStart;
    m_modelEnd = initial->m_modelEnd;
    m_index = initial->m_index;
    m_dwell = initial->m_dwell;
    m_spindleSpeed = initial->m_spindleSpeed;
}

LineSegment::~LineSegment()
{
}

int LineSegment::getLineNumber()
{
    return m_lineIndex;
}

QVector3D &LineSegment::getStart()
{
    return m_first;
}

void LineSegment::setStart(QVector3D vector)
{
    m_first = vector;
}

QVector3D &LineSegment::getEnd()
{
    return m_second;
}

void LineSegment::setEnd(QVector3D vector)
{
    m_second = vector;
}

const QVector3D &LineSegment::modelStart() const
{
    return m_modelStart;
}

void LineSegment::setModelStart(const QVector3D &modelStart)
{
    m_modelStart = modelStart;
}

const QVector3D &LineSegment::modelEnd() const
{
    return m_modelEnd;
}

void LineSegment::setModelEnd(const QVector3D &modelEnd)
{
    m_modelEnd = modelEnd;
}

const QVector3D &LineSegment::axesStart() const
{
    return m_axesStart;
}

void LineSegment::setAxesStart(const QVector3D &axesStart)
{
    m_axesStart = axesStart;
}

const QVector3D &LineSegment::axesEnd() const
{
    return m_axesEnd;
}

void LineSegment::setAxesEnd(const QVector3D &axesEnd)
{
    m_axesEnd = axesEnd;
}

void LineSegment::setToolHead(int head)
{
    m_toolhead = head;
}

int LineSegment::getToolhead()
{
    return m_toolhead;
}

void LineSegment::setSpeed(double s)
{
    m_speed = s;
}

double LineSegment::getSpeed() const
{
    return m_speed;
}

bool LineSegment::isAbsolute() const
{
    return m_flags.isAbsolute;
}

void LineSegment::setIsAbsolute(bool isAbsolute)
{
    m_flags.isAbsolute = isAbsolute;
}

bool LineSegment::isArc()
{
    return m_flags.isArc;
}

void LineSegment::setIsArc(bool isA)
{
    m_flags.isArc = isA;
}

bool LineSegment::isClockwise() const
{
    return m_flags.isClockwise;
}

void LineSegment::setIsClockwise(bool isClockwise)
{
    m_flags.isClockwise = isClockwise;
}

bool LineSegment::isDrawn() const
{
    return m_flags.isDrawn;
}

void LineSegment::setIsDrawn(bool drawn)
{
    m_flags.isDrawn = drawn;
}

bool LineSegment::isFastTraverse() const
{
    return m_flags.isFastTraverse;
}

void LineSegment::setIsFastTraverse(bool isF)
{
    m_flags.isFastTraverse = isF;
}

bool LineSegment::isHighlight() const
{
    return m_flags.isHighlight;
}

void LineSegment::setIsHighlight(bool isHighlight)
{
    m_flags.isHighlight = isHighlight;
}

bool LineSegment::isMetric() const
{
    return m_flags.isMetric;
}

void LineSegment::setIsMetric(bool isMetric)
{
    m_flags.isMetric = isMetric;
}

bool LineSegment::isSpline() const
{
    return m_flags.isSpline;
}

void LineSegment::setIsSpline(bool isSpline)
{
    m_flags.isSpline = isSpline;
}

bool LineSegment::isZMovement()
{
    return m_flags.isZMovement;
}

void LineSegment::setIsZMovement(bool isZ)
{
    m_flags.isZMovement = isZ;
}

int LineSegment::vertexIndex() const
{
    return m_vertexIndex;
}

void LineSegment::setVertexIndex(int vertexIndex)
{
    m_vertexIndex = vertexIndex;
}

double LineSegment::getSpindleSpeed() const
{
    return m_spindleSpeed;
}

void LineSegment::setSpindleSpeed(double spindleSpeed)
{
    m_spindleSpeed = spindleSpeed;
}

double LineSegment::getDwell() const
{
    return m_dwell;
}

void LineSegment::setDwell(double dwell)
{
    m_dwell = dwell;
}

PointSegment::planes LineSegment::plane() const
{
    return m_plane;
}

void LineSegment::setPlane(const PointSegment::planes &plane)
{
    m_plane = plane;
}

int LineSegment::index() const
{
    return m_index;
}

void LineSegment::setIndex(int index)
{
    m_index = index;
}

bool LineSegment::contains(const QVector3D &point)
{
    double delta;

    QVector3D line = m_second - m_first;
    QVector3D pt = point - m_first;

    delta = (line - pt).length() - (line.length() - pt.length());

    return delta < 0.01;
}