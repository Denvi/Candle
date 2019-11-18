// This file is a part of "Candle" application.
// This file was originally ported from "GcodeViewParse.java" class
// of "Universal GcodeSender" application written by Will Winder
// (https://github.com/winder/Universal-G-Code-Sender)

// Copyright 2015-2016 Hayrullin Denis Ravilevich

#include <QDebug>
#include "gcodeviewparse.h"

GcodeViewParse::GcodeViewParse(QObject *parent) :
    QObject(parent)
{
    absoluteMode = true;
    absoluteIJK = false;
    currentLine = 0;
    debug = true;

    m_min = QVector3D(qQNaN(), qQNaN(), qQNaN());
    m_max = QVector3D(qQNaN(), qQNaN(), qQNaN());

    m_minLength = qQNaN();
}

GcodeViewParse::~GcodeViewParse()
{
    foreach (LineSegment *ls, m_lines) delete ls;
}

QVector3D &GcodeViewParse::getMinimumExtremes()
{
    return m_min;
}

QVector3D &GcodeViewParse::getMaximumExtremes()
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

void GcodeViewParse::testLength(const QVector3D &start, const QVector3D &end)
{
    double length = (start - end).length();
    if (!qIsNaN(length) && length != 0) m_minLength = qIsNaN(m_minLength) ? length : qMin<double>(m_minLength, length);
}

QList<LineSegment*> GcodeViewParse::toObjRedux(QList<QString> gcode, double arcPrecision, bool arcDegreeMode)
{
    GcodeParser gp;

    foreach (QString s, gcode) {
        gp.addCommand(s);
    }

    return getLinesFromParser(&gp, arcPrecision, arcDegreeMode);
}

QList<LineSegment*> GcodeViewParse::getLineSegmentList()
{
    return m_lines;
}

void GcodeViewParse::reset()
{
    foreach (LineSegment *ls, m_lines) delete ls;
    m_lines.clear();
    m_lineIndexes.clear();
    currentLine = 0;
    m_min = QVector3D(qQNaN(), qQNaN(), qQNaN());
    m_max = QVector3D(qQNaN(), qQNaN(), qQNaN());
    m_minLength = qQNaN();
}

double GcodeViewParse::getMinLength() const
{
    return m_minLength;
}

QSize GcodeViewParse::getResolution() const
{
    return QSize(((m_max.x() - m_min.x()) / m_minLength) + 1, ((m_max.y() - m_min.y()) / m_minLength) + 1);
}

QList<LineSegment*> GcodeViewParse::getLinesFromParser(GcodeParser *gp, double arcPrecision, bool arcDegreeMode)
{
    QList<PointSegment*> psl = gp->getPointSegmentList();
    // For a line segment list ALL arcs must be converted to lines.
    double minArcLength = 0.1;
    double length;

    QVector3D *start, *end;
    start = NULL;
    end = NULL;
    LineSegment *ls;

    // Prepare segments indexes
    m_lineIndexes.resize(psl.count());

    int lineIndex = 0;
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
                        ls = new LineSegment(startPoint, nextPoint, lineIndex);
                        ls->setIsArc(ps->isArc());
                        ls->setIsClockwise(ps->isClockwise());
                        ls->setPlane(ps->plane());
                        ls->setIsFastTraverse(ps->isFastTraverse());
                        ls->setIsZMovement(ps->isZMovement());
                        ls->setIsMetric(isMetric);
                        ls->setIsAbsolute(ps->isAbsolute());
                        ls->setSpeed(ps->getSpeed());
                        ls->setSpindleSpeed(ps->getSpindleSpeed());
                        ls->setDwell(ps->getDwell());
                        this->testExtremes(nextPoint);
                        m_lines.append(ls);
                        m_lineIndexes[ps->getLineNumber()].append(m_lines.count() - 1);
                        startPoint = nextPoint;
                    }
                    lineIndex++;
                }
            // Line
            } else {
                ls = new LineSegment(*start, *end, lineIndex++);
                ls->setIsArc(ps->isArc());
                ls->setIsFastTraverse(ps->isFastTraverse());
                ls->setIsZMovement(ps->isZMovement());
                ls->setIsMetric(isMetric);
                ls->setIsAbsolute(ps->isAbsolute());
                ls->setSpeed(ps->getSpeed());
                ls->setSpindleSpeed(ps->getSpindleSpeed());
                ls->setDwell(ps->getDwell());
                this->testExtremes(*end);
                this->testLength(*start, *end);
                m_lines.append(ls);
                m_lineIndexes[ps->getLineNumber()].append(m_lines.count() - 1);
            }
        }
        start = end;
    }

    return m_lines;
}

QList<LineSegment*> *GcodeViewParse::getLines()
{
    return &m_lines;
}

QVector<QList<int> > &GcodeViewParse::getLinesIndexes()
{
    return m_lineIndexes;
}
