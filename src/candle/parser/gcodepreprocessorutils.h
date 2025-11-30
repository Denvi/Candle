// This file is a part of "Candle" application.
// This file was originally ported from "GcodePreprocessorUtils.java" class
// of "Universal GcodeSender" application written by Will Winder
// (https://github.com/winder/Universal-G-Code-Sender)

// Copyright 2015-2025 Hayrullin Denis Ravilevich

#ifndef GCODEPREPROCESSORUTILS_H
#define GCODEPREPROCESSORUTILS_H

#include <QObject>
#include <QMatrix4x4>
#include <cmath>
#include "pointsegment.h"

class GcodePreprocessorUtils : public QObject
{
    Q_OBJECT
public:
    static QString overrideSpeed(QString command, double speed, double *original = NULL);
    static QString removeComment(QString command);
    static QString parseComment(QString command);
    static QString truncateDecimals(int length, QString command);
    static QString removeAllWhitespace(QString command);
    static QList<float> parseCodes(const QStringList &args, char code);
    static QList<int> parseGCodes(QString command);
    static QList<int> parseMCodes(QString command);
    static QStringList splitCommand(const QString &command);
    static double parseCoord(QStringList argList, char c);
    static QVector3D updatePointWithCommand(const QVector3D &initial, double x, double y, double z, bool absoluteMode);
    static QVector3D updatePointWithCommand(const QStringList &commandArgs, const QVector3D &initial, bool absoluteMode);
    static QVector3D updatePointWithCommand(const QString &command, const QVector3D &initial, bool absoluteMode);
    static QVector3D updateAxesWithCommand(const QStringList &commandArgs, const QVector3D &initial, bool absoluteMode);
    static QVector3D convertRToCenter(QVector3D start, QVector3D end, double radius, bool absoluteIJK, bool clockwise);
    static QVector3D updateCenterWithCommand(QStringList commandArgs, QVector3D initial, QVector3D nextPoint, bool absoluteIJKMode, bool clockwise);
    static QString generateG1FromPoints(QVector3D start, QVector3D end, bool absoluteMode, int precision);
    static double getAngle(QVector3D start, QVector3D end);
    static double calculateSweep(double startAngle, double endAngle, bool isCw, int turns = 1);
    static QList<QVector3D> generatePointsAlongArcBDring(PointSegment::planes plane, QVector3D start, QVector3D end, QVector3D center, bool clockwise, double R, double minArcLength, double arcPrecision, bool arcDegreeMode, int turns = 1);
    static QList<QVector3D> generatePointsAlongArcBDring(PointSegment::planes plane, QVector3D p1, QVector3D p2, QVector3D center, bool isCw, double radius, double startAngle, double sweep, int numPoints);
    static QVector3D lerp(const QVector3D &a, const QVector3D &b, double t);
    static QVector3D evalCubicBSpline(double t, const QVector3D &p0, const QVector3D &p1, const QVector3D &p2, const QVector3D &p3);
    static QVector3D evalQuadraticBSpline(double t, const QVector3D &p0, const QVector3D &p1, const QVector3D &p2);
    static QList<QVector3D> generatePointsAlongSpline(const QVector3D &start, const QVector3D &end, const QVector3D *cp1, const QVector3D *cp2, double tolerance = 0.1);
    static inline bool isDigit(char c);
    static inline bool isLetter(char c);
    static inline char toUpper(char c);
signals:

public slots:

private:

};

#endif // GCODEPREPROCESSORUTILS_H
