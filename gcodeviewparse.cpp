// This file is a part of "grblControl" application.
// This file was originally ported from "GcodeViewParse.java" class
// of "Universal GcodeSender" application written by Will Winder
// (https://github.com/winder/Universal-G-Code-Sender)

// Copyright 2015 Hayrullin Denis Ravilevich

#include <QDebug>
#include "gcodeviewparse.h"

GcodeViewParse::GcodeViewParse(QObject *parent) :
    QObject(parent)
{
    absoluteMode = true;
    absoluteIJK = false;
    currentLine = 0;
    debug = true;

    m_min = QVector3D(NAN, NAN, NAN);
    m_max = QVector3D(NAN, NAN, NAN);
}

GcodeViewParse::~GcodeViewParse()
{
    foreach (LineSegment *ls, lines) delete ls;
}

QVector3D GcodeViewParse::getMinimumExtremes()
{
    return m_min;
}

QVector3D GcodeViewParse::getMaximumExtremes()
{
    return m_max;
}

void GcodeViewParse::testExtremes(QVector3D p3d)
{
    this->testExtremes(p3d.x(), p3d.y(), p3d.z());
}

void GcodeViewParse::testExtremes(double x, double y, double z)
{
    m_min.setX(Util::nMin(m_min.x(), x));
    m_min.setY(Util::nMin(m_min.y(), y));
    m_min.setZ(Util::nMin(m_min.z(), z));

    m_max.setX(Util::nMax(m_max.x(), x));
    m_max.setY(Util::nMax(m_max.y(), y));
    m_max.setZ(Util::nMax(m_max.z(), z));
}

QList<LineSegment*> GcodeViewParse::toObjRedux(QList<QString> gcode, double arcPrecision, bool arcDegreeMode)
{
    GcodeParser gp;

    foreach (QString s, gcode) {
        gp.addCommand(s);
    }

    return getLinesFromParser(&gp, arcPrecision, arcDegreeMode);
}

QList<LineSegment *> GcodeViewParse::getLineSegmentList()
{
    return lines;
}

void GcodeViewParse::reset()
{
    foreach (LineSegment *ls, lines) delete ls;
    lines.clear();
    currentLine = 0;
    m_min = QVector3D(NAN, NAN, NAN);
    m_max = QVector3D(NAN, NAN, NAN);
}

QList<LineSegment *> GcodeViewParse::getLinesFromParser(GcodeParser *gp, double arcPrecision, bool arcDegreeMode)
{
    QList<PointSegment*> psl = gp->getPointSegmentList();
    // For a line segment list ALL arcs must be converted to lines.
    double minArcLength = 0.1;

//    Point3d start = null;
//    Point3d end = null;

    QVector3D *start, *end;
    start = NULL;
    end = NULL;
    LineSegment *ls;

    int num = 0;

    foreach (PointSegment *segment, psl) {
        PointSegment *ps = segment;
        bool isMetric = ps->isMetric();
        ps->convertToMetric();

        end = ps->point();

        // start is null for the first iteration.
        if (start != NULL) {
            // Expand arc for graphics.
            if (ps->isArc()) {
                QList<QVector3D> points =
                    GcodePreprocessorUtils::generatePointsAlongArcBDring(ps->plane(),
                    *start, *end, *ps->center(), ps->isClockwise(), ps->getRadius(), minArcLength, arcPrecision, arcDegreeMode);
                // Create line segments from points.
                if (points.length() > 0) {
                    QVector3D startPoint = *start;
                    foreach (QVector3D nextPoint, points) {
                        if (nextPoint == startPoint) continue;
                        ls = new LineSegment(startPoint, nextPoint, num);
                        ls->setIsArc(ps->isArc());
                        ls->setIsFastTraverse(ps->isFastTraverse());
                        ls->setIsZMovement(ps->isZMovement());
                        ls->setIsMetric(isMetric);
                        ls->setIsAbsolute(ps->isAbsolute());
                        ls->setSpeed(ps->getSpeed());
                        this->testExtremes(nextPoint);
                        lines.append(ls);
                        startPoint = nextPoint;
                    }
                    num++;
                }
            // Line
            } else {
                ls = new LineSegment(*start, *end, num++);
                ls->setIsArc(ps->isArc());
                ls->setIsFastTraverse(ps->isFastTraverse());
                ls->setIsZMovement(ps->isZMovement());
                ls->setIsMetric(isMetric);
                ls->setIsAbsolute(ps->isAbsolute());
                ls->setSpeed(ps->getSpeed());
                this->testExtremes(*end);
                lines.append(ls);
            }
        }
        start = end;
    }

    return lines;
}

QList<LineSegment *> *GcodeViewParse::getLines()
{
    return &lines;
}
