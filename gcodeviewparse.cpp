#include <QDebug>
#include "gcodeviewparse.h"

GcodeViewParse::GcodeViewParse(QObject *parent) :
    QObject(parent)
{
    absoluteMode = true;
    absoluteIJK = false;
    currentLine = 0;
    debug = true;
}

GcodeViewParse::~GcodeViewParse()
{
    foreach (LineSegment *ls, lines) delete ls;
}

QVector3D GcodeViewParse::getMinimumExtremes()
{
    return min;
}

QVector3D GcodeViewParse::getMaximumExtremes()
{
    return max;
}

void GcodeViewParse::testExtremes(QVector3D p3d)
{
    this->testExtremes(p3d.x(), p3d.y(), p3d.z());
}

void GcodeViewParse::testExtremes(double x, double y, double z)
{
    min.setX(qMin<double>(min.x(), x));
    min.setY(qMin<double>(min.y(), y));
    min.setZ(qMin<double>(min.z(), z));

    max.setX(qMax<double>(max.x(), x));
    max.setY(qMax<double>(max.y(), y));
    max.setZ(qMax<double>(max.z(), z));
}

QList<LineSegment*> GcodeViewParse::toObjRedux(QList<QString> gcode, double arcSegmentLength)
{
    GcodeParser gp;

    foreach (QString s, gcode) {
        gp.addCommand(s);
    }

    return getLinesFromParser(&gp, arcSegmentLength);
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
    min = QVector3D(0, 0, 0);
    max = QVector3D(0, 0, 0);
}

QList<LineSegment*> GcodeViewParse::getLinesFromParser(GcodeParser *gp, double arcSegmentLength)
{
    QList<PointSegment*> psl = gp->getPointSegmentList();
    // For a line segment list ALL arcs must be converted to lines.
    double minArcLength = 0;

//    Point3d start = null;
//    Point3d end = null;

    QVector3D *start, *end;
    start = NULL;
    end = NULL;
    LineSegment *ls;

    int num = 0;

    foreach (PointSegment *segment, psl) {
        PointSegment *ps = segment;
        ps->convertToMetric();

        end = ps->point();

        // start is null for the first iteration.
        if (start != NULL) {
            // Expand arc for graphics.
            if (ps->isArc()) {
                QList<QVector3D> points =
                    GcodePreprocessorUtils::generatePointsAlongArcBDring(
                    *start, *end, *ps->center(), ps->isClockwise(), ps->getRadius(), minArcLength, arcSegmentLength);
                // Create line segments from points.
                if (points.length() > 0) {
                    QVector3D startPoint = *start;
                    foreach (QVector3D nextPoint, points) {
                        if (nextPoint == startPoint) continue;
                        ls = new LineSegment(startPoint, nextPoint, num);
                        ls->setIsArc(ps->isArc());
                        ls->setIsFastTraverse(ps->isFastTraverse());
                        ls->setIsZMovement(ps->isZMovement());
                        this->testExtremes(nextPoint);
                        lines.append(ls);
                        startPoint = nextPoint;
                    }
                }
            // Line
            } else {
                ls = new LineSegment(*start, *end, num++);
                ls->setIsArc(ps->isArc());
                ls->setIsFastTraverse(ps->isFastTraverse());
                ls->setIsZMovement(ps->isZMovement());
                this->testExtremes(*end);
                lines.append(ls);
            }
        }
        start = end;
    }

    return lines;
}
