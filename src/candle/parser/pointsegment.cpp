// This file is a part of "Candle" application.
// This file was originally ported from "PointSegment.java" class
// of "Universal GcodeSender" application written by Will Winder
// (https://github.com/winder/Universal-G-Code-Sender)

// Copyright 2015-2025 Hayrullin Denis Ravilevich

#include <QVector>

#include "pointsegment.h"

PointSegment::PointSegment()
{
    m_toolhead = 0;
    m_isMetric = true;
    m_isAbsolute = true;
    m_isZMovement = false;
    m_isArc = false;
    m_isSpline = false;
    m_isFastTraverse = false;
    m_lineNumber = -1;
    m_arcProperties = NULL;
    m_splineProperties = NULL;
    m_speed = 0;
    m_spindleSpeed = 0;
    m_dwell = 0;
    m_plane = XY;
}

PointSegment::PointSegment(PointSegment *ps) : PointSegment(ps->point(), ps->axes(), ps->getLineNumber())
{
    this->m_toolhead = ps->getToolhead();
    this->m_speed = ps->getSpeed();
    this->m_isMetric = ps->isMetric();
    this->m_isZMovement = ps->isZMovement();
    this->m_isFastTraverse = ps->isFastTraverse();
    this->m_isAbsolute = ps->isAbsolute();
    this->m_dwell = ps->getDwell();
    this->m_spindleSpeed = ps->getSpindleSpeed();

    if (ps->isArc()) {
        this->setArcCenter(ps->center());
        this->setRadius(ps->getRadius());
        this->setIsClockwise(ps->isClockwise());
        this->m_plane = ps->plane();
    }
}

PointSegment::PointSegment(const QVector3D *point, const QVector3D *axes, int num) : PointSegment()
{
    this->m_point = new QVector3D(point->x(), point->y(), point->z());
    this->m_axes = new QVector3D(*axes);
    this->m_lineNumber = num;
}

PointSegment::PointSegment(QVector3D *point, QVector3D *axes, int num, QVector3D *center, double radius,
    bool clockwise) : PointSegment(point, axes, num)
{
    this->m_isArc = true;
    this->m_arcProperties = new ArcProperties();
    this->m_arcProperties->center = new QVector3D(center->x(), center->y(), 
        center->z());
    this->m_arcProperties->radius = radius;
    this->m_arcProperties->isClockwise = clockwise;
}

PointSegment::~PointSegment()
{
    if (this->m_arcProperties != NULL && this->m_arcProperties->center != NULL) delete this->m_arcProperties->center;
    if (this->m_arcProperties != NULL) delete this->m_arcProperties;
    if (this->m_splineProperties != NULL) {
        if (this->m_splineProperties->controlPoint1 != NULL) delete this->m_splineProperties->controlPoint1;
        if (this->m_splineProperties->controlPoint2 != NULL) delete this->m_splineProperties->controlPoint2;
        delete this->m_splineProperties;
    }
    if (this->m_point != NULL) delete this->m_point;
    if (this->m_axes != NULL) delete this->m_axes;
}

void PointSegment::setPoint(QVector3D point) {
    this->m_point = new QVector3D(point.x(), point.y(), point.z());
}

QVector3D *PointSegment::point()
{
    return m_point;
}

void PointSegment::setAxes(QVector3D axes)
{
    this->m_axes = new QVector3D(axes);
}

QVector3D *PointSegment::axes()
{
    return m_axes;
}

QVector<double> PointSegment::points()
{
    QVector<double> points;
    points.append(m_point->x());
    points.append(m_point->y());
    return points;
}

void PointSegment::setToolHead(int head) {
    this->m_toolhead = head;
}

int PointSegment::getToolhead()
{
    return m_toolhead;
}

void PointSegment::setLineNumber(int num) {
    this->m_lineNumber = num;
}

int PointSegment::getLineNumber() {
    return m_lineNumber;
}

void PointSegment::setSpeed(double s) {
    this->m_speed = s;
}

double PointSegment::getSpeed()
{
    return m_speed;
}

void PointSegment::setIsZMovement(bool isZ) {
    this->m_isZMovement = isZ;
}

bool PointSegment::isZMovement() {
    return m_isZMovement;
}

void PointSegment::setIsMetric(bool isMetric) {
    this->m_isMetric = isMetric;
}

bool PointSegment::isMetric() {
    return m_isMetric;
}

void PointSegment::setIsArc(bool isA) {
    this->m_isArc = isA;
}

bool PointSegment::isArc() {
    return m_isArc;
}

void PointSegment::setIsFastTraverse(bool isF) {
    this->m_isFastTraverse = isF;
}

bool PointSegment::isFastTraverse() {
    return m_isFastTraverse;
}

// Arc properties.

void PointSegment::setArcCenter(QVector3D *center) {
    if (this->m_arcProperties == NULL) this->m_arcProperties = new ArcProperties();

    this->m_arcProperties->center = new QVector3D(center->x(), center->y(), center->z());
    this->setIsArc(true);
}

QVector<double> PointSegment::centerPoints()
{
    QVector<double> points;
    if (this->m_arcProperties != NULL && this->m_arcProperties->center != NULL) {
        points.append(m_arcProperties->center->x());
        points.append(m_arcProperties->center->y());
        points.append(m_arcProperties->center->z());
    }
    return points;
}

QVector3D *PointSegment::center() {
    if (this->m_arcProperties != NULL && this->m_arcProperties->center != NULL) return this->m_arcProperties->center;
    return NULL;
}

void PointSegment::setIsClockwise(bool clockwise) {
    if (this->m_arcProperties == NULL) this->m_arcProperties = new ArcProperties();
    this->m_arcProperties->isClockwise = clockwise;
}

bool PointSegment::isClockwise() {
    if (this->m_arcProperties != NULL && this->m_arcProperties->center != NULL) return this->m_arcProperties->isClockwise;
    return false;
}

void PointSegment::setRadius(double rad) {
    if (this->m_arcProperties == NULL) this->m_arcProperties = new ArcProperties();
    this->m_arcProperties->radius = rad;
}

double PointSegment::getRadius() {
    if (this->m_arcProperties != NULL && this->m_arcProperties->center != NULL) return this->m_arcProperties->radius;
    return 0;
}

void PointSegment::convertToMetric() {
    if (this->m_isMetric) {
        return;
    }

    this->m_isMetric = true;
    this->m_point->setX(this->m_point->x() * 25.4);
    this->m_point->setY(this->m_point->y() * 25.4);
    this->m_point->setZ(this->m_point->z() * 25.4);

    if (this->m_isArc && this->m_arcProperties != NULL) {
        this->m_arcProperties->center->setX(this->m_arcProperties->center->x() * 25.4);
        this->m_arcProperties->center->setY(this->m_arcProperties->center->y() * 25.4);
        this->m_arcProperties->center->setZ(this->m_arcProperties->center->z() * 25.4);
        this->m_arcProperties->radius *= 25.4;
    }
}
bool PointSegment::isAbsolute() const
{
    return m_isAbsolute;
}

void PointSegment::setIsAbsolute(bool isAbsolute)
{
    m_isAbsolute = isAbsolute;
}

PointSegment::planes PointSegment::plane() const
{
    return m_plane;
}

void PointSegment::setPlane(const planes &plane)
{
    m_plane = plane;
}

double PointSegment::getSpindleSpeed() const
{
    return m_spindleSpeed;
}

void PointSegment::setSpindleSpeed(double spindleSpeed)
{
    m_spindleSpeed = spindleSpeed;
}

double PointSegment::getDwell() const
{
    return m_dwell;
}

void PointSegment::setDwell(double dwell)
{
    m_dwell = dwell;
}

int PointSegment::getArcTurns() const
{
    if (this->m_arcProperties != NULL) return this->m_arcProperties->turns;
    return 1;
}

void PointSegment::setArcTurns(int turns)
{
    if (this->m_arcProperties == NULL) this->m_arcProperties = new ArcProperties();
    this->m_arcProperties->turns = turns > 0 ? turns : 1;
}

// Spline properties

bool PointSegment::isSpline() const
{
    return m_isSpline;
}

void PointSegment::setIsSpline(bool isSpline)
{
    m_isSpline = isSpline;
}

void PointSegment::setSplineControlPoints(const QVector3D *cp1, const QVector3D *cp2)
{
    if (this->m_splineProperties == NULL) this->m_splineProperties = new SplineProperties();
    this->m_splineProperties->controlPoint1 = new QVector3D(*cp1);
    if (cp2 != NULL) {
        this->m_splineProperties->controlPoint2 = new QVector3D(*cp2);
    }
    this->setIsSpline(true);
}

QVector3D* PointSegment::getSplineControlPoint1()
{
    if (this->m_splineProperties != NULL) return this->m_splineProperties->controlPoint1;
    return NULL;
}

QVector3D* PointSegment::getSplineControlPoint2()
{
    if (this->m_splineProperties != NULL) return this->m_splineProperties->controlPoint2;
    return NULL;
}

SplineType PointSegment::getSplineType() const
{
    if (this->m_splineProperties != NULL) return this->m_splineProperties->type;
    return CUBIC_SPLINE;
}

void PointSegment::setSplineType(SplineType type)
{
    if (this->m_splineProperties == NULL) this->m_splineProperties = new SplineProperties();
    this->m_splineProperties->type = type;
}
