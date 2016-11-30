// This file is a part of "Candle" application.
// This file was originally ported from "LineSegment.java" class
// of "Universal GcodeSender" application written by Will Winder
// (https://github.com/winder/Universal-G-Code-Sender)

// Copyright 2015-2016 Hayrullin Denis Ravilevich

#include "linesegment.h"
#include <QDebug>

LineSegment::LineSegment()
{
    m_toolhead = 0; //DEFAULT TOOLHEAD ASSUMED TO BE 0!
    m_isZMovement = false;
    m_isArc = false;
    m_isFastTraverse = false;
    m_drawn = false;
    m_isMetric = true;
    m_isAbsolute = true;
    m_isHightlight = false;
    m_vertexIndex = -1;
}

LineSegment::LineSegment(QVector3D a, QVector3D b, int num) : LineSegment()
{
//    m_toolhead = 0; //DEFAULT TOOLHEAD ASSUMED TO BE 0!
//    m_isZMovement = false;
//    m_isArc = false;
//    m_isFastTraverse = false;

    m_first = a;
    m_second = b;
    m_lineNumber = num;
}

LineSegment::LineSegment(LineSegment* initial)
{
    m_toolhead = initial->getToolhead();
    m_isZMovement = initial->isZMovement();
    m_isArc = initial->isArc();
    m_isFastTraverse = initial->isFastTraverse();
    m_drawn = initial->drawn();
    m_first = initial->getStart();
    m_second = initial->getEnd();
    m_lineNumber = initial->getLineNumber();
    m_speed = initial->getSpeed();
    m_isMetric = initial->isMetric();
    m_isAbsolute = initial->isAbsolute();
    m_isHightlight = initial->isHightlight();
    m_vertexIndex = initial->vertexIndex();
}

LineSegment::~LineSegment()
{

}

int LineSegment::getLineNumber() {
    return m_lineNumber;
}

QList<QVector3D> LineSegment::getPointArray()
{
    QList<QVector3D> pointarr;
    pointarr.append(m_first);
    pointarr.append(m_second);
    return pointarr;
}

QList<double> LineSegment::getPoints()
{
    QList<double> points;
    points.append(m_first.x());
    points.append(m_first.y());
    points.append(m_first.z());
    points.append(m_second.x());
    points.append(m_second.y());
    points.append(m_second.z());
    return points;
}

QVector3D &LineSegment::getStart() {
    return this->m_first;
}

void LineSegment::setStart(QVector3D vector)
{
    m_first = vector;
}

QVector3D &LineSegment::getEnd() {
    return this->m_second;
}

void LineSegment::setEnd(QVector3D vector)
{
    m_second = vector;
}

void LineSegment::setToolHead(int head) {
    this->m_toolhead = head;
}

int LineSegment::getToolhead()
{
    return m_toolhead;
}

void LineSegment::setSpeed(double s) {
    this->m_speed = s;
}

double LineSegment::getSpeed()
{
    return m_speed;
}

void LineSegment::setIsZMovement(bool isZ) {
    this->m_isZMovement = isZ;
}

bool LineSegment::isZMovement() {
    return m_isZMovement;
}

void LineSegment::setIsArc(bool isA) {
    this->m_isArc = isA;
}

bool LineSegment::isArc() {
    return m_isArc;
}

void LineSegment::setIsFastTraverse(bool isF) {
    this->m_isFastTraverse = isF;
}

bool LineSegment::isFastTraverse() {
    return this->m_isFastTraverse;
}

bool LineSegment::contains(const QVector3D &point)
{
    double delta;
    QVector3D line = this->getEnd() - this->getStart();
    QVector3D pt = point - this->getStart();

    delta = (line - pt).length() - (line.length() - pt.length());

    return delta < 0.01;
}

bool LineSegment::drawn() const
{
    return m_drawn;
}

void LineSegment::setDrawn(bool drawn)
{
    m_drawn = drawn;
}
bool LineSegment::isMetric() const
{
    return m_isMetric;
}

void LineSegment::setIsMetric(bool isMetric)
{
    m_isMetric = isMetric;
}
bool LineSegment::isAbsolute() const
{
    return m_isAbsolute;
}

void LineSegment::setIsAbsolute(bool isAbsolute)
{
    m_isAbsolute = isAbsolute;
}
bool LineSegment::isHightlight() const
{
    return m_isHightlight;
}

void LineSegment::setIsHightlight(bool isHightlight)
{
    m_isHightlight = isHightlight;
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

bool LineSegment::isClockwise() const
{
    return m_isClockwise;
}

void LineSegment::setIsClockwise(bool isClockwise)
{
    m_isClockwise = isClockwise;
}

PointSegment::planes LineSegment::plane() const
{
    return m_plane;
}

void LineSegment::setPlane(const PointSegment::planes &plane)
{
    m_plane = plane;
}





