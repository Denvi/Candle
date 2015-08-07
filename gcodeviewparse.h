#ifndef GCODEVIEWPARSE_H
#define GCODEVIEWPARSE_H

#include <QObject>
#include <QVector3D>
#include "linesegment.h"
#include "gcodeparser.h"

class GcodeViewParse : public QObject
{
    Q_OBJECT
public:
    explicit GcodeViewParse(QObject *parent = 0);
    ~GcodeViewParse();

    QVector3D getMinimumExtremes();
    QVector3D getMaximumExtremes();
    QList<LineSegment *> toObjRedux(QList<QString> gcode, double arcSegmentLength);
    QList<LineSegment *> getLineSegmentList();
    QList<LineSegment *> getLinesFromParser(GcodeParser *gp, double arcSegmentLength);
    void reset();
signals:

public slots:

private:
    bool absoluteMode;
    bool absoluteIJK;

    // Parsed object
    QVector3D min, max;
    QList<LineSegment*> lines;

    // Parsing state.
    QVector3D lastPoint;
    int currentLine; // for assigning line numbers to segments.

    // Debug
    bool debug;
    void testExtremes(QVector3D p3d);
    void testExtremes(double x, double y, double z);
};

#endif // GCODEVIEWPARSE_H
