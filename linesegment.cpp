// This file is a part of "grblControl" application.
// This file was originally ported from "LineSegment.java" class
// of "Universal GcodeSender" application written by Will Winder
// (https://github.com/winder/Universal-G-Code-Sender)

// Copyright 2015 Hayrullin Denis Ravilevich

#include "linesegment.h"
#include <QDebug>

LineSegment::LineSegment(QObject *parent) :
    QObject(parent)
{
    m_toolhead = 0; //DEFAULT TOOLHEAD ASSUMED TO BE 0!
    m_isZMovement = false;
    m_isArc = false;
    m_isFastTraverse = false;
    m_drawn = false;
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

QVector3D LineSegment::getStart() {
    return this->m_first;
}

QVector3D LineSegment::getEnd() {
    return this->m_second;
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

bool LineSegment::contains(QVector3D point)
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

