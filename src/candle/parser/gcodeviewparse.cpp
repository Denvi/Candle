// This file is a part of "Candle" application.
// This file was originally ported from "GcodeViewParse.java" class
// of "Universal GcodeSender" application written by Will Winder
// (https://github.com/winder/Universal-G-Code-Sender)

// Copyright 2015-2025 Hayrullin Denis Ravilevich

#include <QDebug>
#include "gcodeviewparse.h"

GcodeViewParse::GcodeViewParse(QObject *parent) :
    QObject(parent)
{
    absoluteMode = true;
    absoluteIJK = false;
    currentLine = 0;
    debug = true;

    m_viewLowerBounds = Util::nVector();
    m_viewUpperBounds = Util::nVector();

    m_modelLowerBounds = Util::nVector();
    m_modelUpperBounds = Util::nVector();

    m_modelMinLineLength = qQNaN();
}

GcodeViewParse::~GcodeViewParse()
{
    foreach (LineSegment *ls, m_lines) delete ls;
}

QVector3D &GcodeViewParse::getViewLowerBounds()
{
    return m_viewLowerBounds;
}

QVector3D &GcodeViewParse::getViewUpperBounds()
{
    return m_viewUpperBounds;
}

QVector3D &GcodeViewParse::getModelLowerBounds() {
    return m_modelLowerBounds;
}

QVector3D &GcodeViewParse::getModelUpperBounds() {
    return m_modelUpperBounds;
}

void GcodeViewParse::updateViewBounds(const QVector3D &point)
{
    m_viewLowerBounds = Util::nMin(m_viewLowerBounds, point);
    m_viewUpperBounds = Util::nMax(m_viewUpperBounds, point);
}

void GcodeViewParse::updateModelBounds(const QVector3D &point)
{
    m_modelLowerBounds = Util::nMin(m_modelLowerBounds, point);
    m_modelUpperBounds = Util::nMax(m_modelUpperBounds, point);
}

void GcodeViewParse::updateModelMinLineLength(const QVector3D &start, const QVector3D &end)
{
    double length = (start - end).length();
    if (!qIsNaN(length) && length != 0) m_modelMinLineLength = qIsNaN(m_modelMinLineLength) ? length : qMin<double>(m_modelMinLineLength, length);
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
    m_viewLowerBounds = Util::nVector();
    m_viewUpperBounds = Util::nVector();
    
    m_modelLowerBounds = Util::nVector();
    m_modelUpperBounds = Util::nVector();
    
    m_modelMinLineLength = qQNaN();
}

double GcodeViewParse::getModelMinLineLength() const
{
    return m_modelMinLineLength;
}

QSize GcodeViewParse::getModelResolution() const
{
    return QSize(((m_modelUpperBounds.x() - m_modelLowerBounds.x()) / m_modelMinLineLength) + 1,
                 ((m_modelUpperBounds.y() - m_modelLowerBounds.y()) / m_modelMinLineLength) + 1);
}

QList<LineSegment*> GcodeViewParse::getLinesFromParser(GcodeParser *gp, double arcPrecision, bool arcDegreeMode)
{
    QList<PointSegment*> psl = gp->getPointSegmentList();
    // For a line segment list ALL arcs must be converted to lines.
    const double minArcLength = 0.1;
    const double rotationDelta = 5.0;

    QVector3D *start, *end;
    start = NULL;
    end = NULL;
    LineSegment *ls;
    int index = 0;
    int lineIndex = 0;

    // Prepare segments indexes
    m_lineIndexes.resize(psl.count());

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
                    GcodePreprocessorUtils::generatePointsAlongArcBDring(
                        ps->plane(), *start, *end, 
                        *ps->center(), ps->isClockwise(), ps->getRadius(), 
                        minArcLength, arcPrecision, arcDegreeMode);

                // Create line segments from points.
                int segments = points.length();
                if (segments > 0) {
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
                        ls->setModelStart(startPoint);
                        ls->setModelEnd(nextPoint);
                        ls->setIndex(index++);

                        this->updateViewBounds(ls->getEnd());
                        this->updateModelBounds(nextPoint);

                        m_lines.append(ls);
                        m_lineIndexes[ps->getLineNumber()].append(
                            m_lines.count() - 1);

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
                this->updateViewBounds(*end);
                this->updateModelBounds(*end);
                this->updateModelMinLineLength(*start, *end);
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
