// This file is a part of "Candle" application.
// This file was originally ported from "PointSegment.java" class
// of "Universal GcodeSender" application written by Will Winder
// (https://github.com/winder/Universal-G-Code-Sender)

// Copyright 2015-2016 Hayrullin Denis Ravilevich

#include <QVector>

#include "pointsegment.h"

PointSegment::PointSegment()
{
    m_toolhead = 0;
    m_isMetric = true;
    m_isAbsolute = true;
    m_isZMovement = false;
    m_isArc = false;
    m_isFastTraverse = false;
    m_lineNumber = -1;
    m_arcProperties = NULL;
    m_speed = 0;
    m_spindleSpeed = 0;
    m_dwell = 0;
    m_plane = XY;
}

PointSegment::PointSegment(PointSegment *ps) : PointSegment(ps->point(), ps->getLineNumber())
{
    this->m_toolhead = ps->getToolhead();
    this->m_speed = ps->getSpeed();
    this->m_isMetric = ps->isMetric();
    this->m_isZMovement = ps->isZMovement();
    this->m_isFastTraverse = ps->isFastTraverse();
    this->m_isAbsolute = ps->isAbsolute();

    if (ps->isArc()) {
        this->setArcCenter(ps->center());
        this->setRadius(ps->getRadius());
        this->setIsClockwise(ps->isClockwise());
        this->m_plane = ps->plane();
    }
}

PointSegment::PointSegment(const QVector3D *b, int num) : PointSegment()
{
    this->m_point = new QVector3D(b->x(), b->y(), b->z());
    this->m_lineNumber = num;
}

PointSegment::PointSegment(QVector3D *point, int num, QVector3D *center, double radius, bool clockwise) : PointSegment(point, num)
{
    this->m_isArc = true;
    this->m_arcProperties = new ArcProperties();
    this->m_arcProperties->center = new QVector3D(center->x(), center->y(), center->z());
    this->m_arcProperties->radius = radius;
    this->m_arcProperties->isClockwise = clockwise;
}

PointSegment::~PointSegment()
{
    if (this->m_arcProperties != NULL && this->m_arcProperties->center != NULL) delete this->m_arcProperties->center;
    if (this->m_arcProperties != NULL) delete this->m_arcProperties;
    if (this->m_point != NULL) delete this->m_point;
}

void PointSegment::setPoint(QVector3D point) {
    this->m_point = new QVector3D(point.x(), point.y(), point.z());
}

QVector3D *PointSegment::point()
{
    return m_point;
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


