// This file is a part of "grblControl" application.
// This file was originally ported from "GcodeParser.java" class
// of "Universal GcodeSender" application written by Will Winder
// (https://github.com/winder/Universal-G-Code-Sender)

// Copyright 2015 Hayrullin Denis Ravilevich

#include <QListIterator>
#include <QDebug>
#include "gcodeparser.h"
#include "math.h"

GcodeParser::GcodeParser(QObject *parent) : QObject(parent)
{
    m_isMetric = true;
    m_inAbsoluteMode = true;
    m_inAbsoluteIJKMode = false;
    m_lastGcodeCommand = "";
    m_commandNumber = 0;

    // Settings
    m_speedOverride = -1;
    m_truncateDecimalLength = 40;
    m_removeAllWhitespace = true;
    m_convertArcsToLines = false;
    m_smallArcThreshold = 1.0;
    // Not configurable outside, but maybe it should be.
    m_smallArcSegmentLength = 0.3;
    m_lastSpeed = 0;
    m_traverseSpeed = 300;

    reset();
}

GcodeParser::~GcodeParser()
{
    foreach (PointSegment *ps, this->m_points) delete ps;
}

bool GcodeParser::getConvertArcsToLines() {
    return m_convertArcsToLines;
}

void GcodeParser::setConvertArcsToLines(bool convertArcsToLines) {
    this->m_convertArcsToLines = convertArcsToLines;
}

bool GcodeParser::getRemoveAllWhitespace() {
    return m_removeAllWhitespace;
}

void GcodeParser::setRemoveAllWhitespace(bool removeAllWhitespace) {
    this->m_removeAllWhitespace = removeAllWhitespace;
}

double GcodeParser::getSmallArcSegmentLength() {
    return m_smallArcSegmentLength;
}

void GcodeParser::setSmallArcSegmentLength(double smallArcSegmentLength) {
    this->m_smallArcSegmentLength = smallArcSegmentLength;
}

double GcodeParser::getSmallArcThreshold() {
    return m_smallArcThreshold;
}

void GcodeParser::setSmallArcThreshold(double smallArcThreshold) {
    this->m_smallArcThreshold = smallArcThreshold;
}

double GcodeParser::getSpeedOverride() {
    return m_speedOverride;
}

void GcodeParser::setSpeedOverride(double speedOverride) {
    this->m_speedOverride = speedOverride;
}

int GcodeParser::getTruncateDecimalLength() {
    return m_truncateDecimalLength;
}

void GcodeParser::setTruncateDecimalLength(int truncateDecimalLength) {
    this->m_truncateDecimalLength = truncateDecimalLength;
}

// Resets the current state.
void GcodeParser::reset()
{
    foreach (PointSegment *ps, this->m_points) delete ps;
    this->m_points.clear();
    // The unspoken home location.
    m_currentPoint.setX(NAN);
    m_currentPoint.setY(NAN);
    m_currentPoint.setZ(NAN);
    this->m_points.append(new PointSegment(&this->m_currentPoint, -1));
}

/**
* Add a command to be processed.
*/
PointSegment* GcodeParser::addCommand(QString command)
{
    QString stripped = GcodePreprocessorUtils::removeComment(command);
    QList<QString> args = GcodePreprocessorUtils::splitCommand(stripped);
    return this->addCommand(args);
}

/**
* Add a command which has already been broken up into its arguments.
*/
PointSegment* GcodeParser::addCommand(QList<QString> args)
{
    if (args.isEmpty()) {
        return NULL;
    }
    return processCommand(args);
}

/**
* Warning, this should only be used when modifying live gcode, such as when
* expanding an arc or canned cycle into line segments.
*/
void GcodeParser::setLastGcodeCommand(QString num) {
    this->m_lastGcodeCommand = num;
}

/**
* Gets the point at the end of the list.
*/
QVector3D *GcodeParser::getCurrentPoint() {
    return &m_currentPoint;
}

/**
* Expands the last point in the list if it is an arc according to the
* the parsers settings.
*/
QList<PointSegment*> GcodeParser::expandArc()
{
    PointSegment *startSegment = this->m_points[this->m_points.size() - 2];
    PointSegment *lastSegment = this->m_points[this->m_points.size() - 1];

    QList<PointSegment*> empty;

    // Can only expand arcs.
    if (!lastSegment->isArc()) {
        return empty;
    }

    // Get precalculated stuff.
    QVector3D *start = startSegment->point();
    QVector3D *end = lastSegment->point();
    QVector3D *center = lastSegment->center();
    double radius = lastSegment->getRadius();
    bool clockwise = lastSegment->isClockwise();
    PointSegment::planes plane = startSegment->plane();

    //
    // Start expansion.
    //

    QList<QVector3D> expandedPoints = GcodePreprocessorUtils::generatePointsAlongArcBDring(plane, *start, *end, *center, clockwise, radius, m_smallArcThreshold, m_smallArcSegmentLength, false);

    // Validate output of expansion.
    if (expandedPoints.length() == 0) {
        return empty;
    }

    // Remove the last point now that we're about to expand it.
    this->m_points.removeLast();
    m_commandNumber--;

    // Initialize return value
    QList<PointSegment*> psl;

    // Create line segments from points.
    PointSegment *temp;

    QListIterator<QVector3D> psi(expandedPoints);
    // skip first element.
    if (psi.hasNext()) psi.next();

    while (psi.hasNext()) {
        temp = new PointSegment(&psi.next(), m_commandNumber++);
        temp->setIsMetric(lastSegment->isMetric());
        this->m_points.append(temp);
        psl.append(temp);
    }

    // Update the new endpoint.
    this->m_currentPoint.setX(this->m_points.last()->point()->x());
    this->m_currentPoint.setY(this->m_points.last()->point()->y());
    this->m_currentPoint.setZ(this->m_points.last()->point()->z());

    return psl;
}

QList<PointSegment*> GcodeParser::getPointSegmentList() {
    return this->m_points;
}
double GcodeParser::getTraverseSpeed() const
{
    return m_traverseSpeed;
}

void GcodeParser::setTraverseSpeed(double traverseSpeed)
{
    m_traverseSpeed = traverseSpeed;
}
int GcodeParser::getCommandNumber() const
{
    return m_commandNumber - 1;
}



PointSegment *GcodeParser::processCommand(QList<QString> args)
{
    QList<QString> gCodes;
    PointSegment *ps = NULL;

    // handle M codes.
    //codes = GcodePreprocessorUtils.parseCodes(args, 'M');
    //handleMCode(for each codes);

    // handle F code.
//    QList<QString> fCodes = GcodePreprocessorUtils::parseCodes(args, 'F');

//    foreach (QString code, fCodes) {
//        double speed = GcodePreprocessorUtils::parseCoord(QList<QString>() << code, 'F');
//        if (!std::isnan(speed)) this->m_lastSpeed = speed;
//    }

    // handle G codes.
    gCodes = GcodePreprocessorUtils::parseCodes(args, 'G');

    // If there was no command, add the implicit one to the party.
    if (gCodes.isEmpty() && m_lastGcodeCommand != "") {
        gCodes.append(m_lastGcodeCommand);
    }

    foreach (QString i, gCodes) {
        ps = handleGCode(i, args);
    }

    return ps;
}

PointSegment *GcodeParser::addLinearPointSegment(QVector3D nextPoint, bool fastTraverse)
{    
    PointSegment *ps = new PointSegment(&nextPoint, m_commandNumber++);

    bool zOnly = false;

    // Check for z-only
    if ((this->m_currentPoint.x() == nextPoint.x()) &&
            (this->m_currentPoint.y() == nextPoint.y()) &&
            (this->m_currentPoint.z() != nextPoint.z())) {
        zOnly = true;
    }

    ps->setIsMetric(this->m_isMetric);
    ps->setIsZMovement(zOnly);
    ps->setIsFastTraverse(fastTraverse);
    ps->setIsAbsolute(this->m_inAbsoluteMode);
    ps->setSpeed(fastTraverse ? this->m_traverseSpeed : this->m_lastSpeed);
    this->m_points.append(ps);

    // Save off the endpoint.
    this->m_currentPoint = nextPoint;

    return ps;
}

PointSegment *GcodeParser::addArcPointSegment(QVector3D nextPoint, bool clockwise, QList<QString> args)
{
    PointSegment *ps = new PointSegment(&nextPoint, m_commandNumber++);

    QVector3D center = GcodePreprocessorUtils::updateCenterWithCommand(args, this->m_currentPoint, nextPoint, this->m_inAbsoluteIJKMode, clockwise);
    double radius = GcodePreprocessorUtils::parseCoord(args, 'R');

    // Calculate radius if necessary.    
    if (std::isnan(radius)) {

        QMatrix4x4 m;
        m.setToIdentity();
        switch (m_currentPlane) {
        case PointSegment::XY:
            break;
        case PointSegment::ZX:
            m.rotate(90, 1.0, 0.0, 0.0);
            break;
        case PointSegment::YZ:
            m.rotate(-90, 0.0, 1.0, 0.0);
            break;
        }

        radius = sqrt(pow((double)((m * this->m_currentPoint).x() - (m * center).x()), 2.0)
                        + pow((double)((m * this->m_currentPoint).y() - (m * center).y()), 2.0));
    }

    ps->setIsMetric(this->m_isMetric);
    ps->setArcCenter(&center);
    ps->setIsArc(true);
    ps->setRadius(radius);
    ps->setIsClockwise(clockwise);
    ps->setIsAbsolute(this->m_inAbsoluteMode);
    ps->setSpeed(this->m_lastSpeed);
    ps->setPlane(m_currentPlane);
    this->m_points.append(ps);

    // Save off the endpoint.
    this->m_currentPoint = nextPoint;
    return ps;
}

PointSegment * GcodeParser::handleGCode(QString code, QList<QString> &args) {
    PointSegment *ps = NULL;

    QVector3D nextPoint = GcodePreprocessorUtils::updatePointWithCommand(args, this->m_currentPoint, this->m_inAbsoluteMode);  

    if (code.length() > 1 && code.startsWith("0"))
        code = code.mid(1);

    double speed = GcodePreprocessorUtils::parseCoord(args, 'F');
    if (!std::isnan(speed)) this->m_lastSpeed = this->m_isMetric ? speed : speed * 25.4;

    if (code == "0") ps = addLinearPointSegment(nextPoint, true);
    else if (code == "1") ps = addLinearPointSegment(nextPoint, false);
    else if (code == "38.2") ps = addLinearPointSegment(nextPoint, false);
    else if (code == "2") ps = addArcPointSegment(nextPoint, true, args);
    else if (code == "3") ps = addArcPointSegment(nextPoint, false, args);
    else if (code == "17") this->m_currentPlane = PointSegment::XY;
    else if (code == "18") this->m_currentPlane = PointSegment::ZX;
    else if (code == "19") this->m_currentPlane = PointSegment::YZ;
    else if (code == "20") this->m_isMetric = false;
    else if (code == "21") this->m_isMetric = true;
    else if (code == "90") this->m_inAbsoluteMode = true;
    else if (code == "90.1") this->m_inAbsoluteIJKMode = true;
    else if (code == "91") this->m_inAbsoluteMode = false;
    else if (code == "91.1") this->m_inAbsoluteIJKMode = false;

    if (code.indexOf(QRegExp("0|1|2|3|38.2")) != -1) this->m_lastGcodeCommand = code;

    return ps;
}

QList<QString> GcodeParser::preprocessCommands(QList<QString> commands) {

    QList<QString> result;

    foreach (QString command, commands) {
        result.append(preprocessCommand(command));
    }

    return result;
}

QList<QString> GcodeParser::preprocessCommand(QString command) {

    QList<QString> result;
    bool hasComment = false;

    // Remove comments from command.
    QString newCommand = GcodePreprocessorUtils::removeComment(command);
    QString rawCommand = newCommand;
    hasComment = (newCommand.length() != command.length());

    if (m_removeAllWhitespace) {
        newCommand = GcodePreprocessorUtils::removeAllWhitespace(newCommand);
    }

    if (newCommand.length() > 0) {

        // Override feed speed
        if (m_speedOverride > 0) {
            newCommand = GcodePreprocessorUtils::overrideSpeed(newCommand, m_speedOverride);
        }

        if (m_truncateDecimalLength > 0) {
            newCommand = GcodePreprocessorUtils::truncateDecimals(m_truncateDecimalLength, newCommand);
        }

        // If this is enabled we need to parse the gcode as we go along.
        if (m_convertArcsToLines) { // || this.expandCannedCycles) {
            QList<QString> arcLines = convertArcsToLines(newCommand);
            if (arcLines.length() > 0) {
                result.append(arcLines);
            } else {
                result.append(newCommand);
            }
        } else if (hasComment) {
            // Maintain line level comment.
            result.append(command.replace(rawCommand, newCommand));
        } else {
            result.append(newCommand);
        }
    } else if (hasComment) {
        // Reinsert comment-only lines.
        result.append(command);
    }

    return result;
}

QList<QString> GcodeParser::convertArcsToLines(QString command) {

    QList<QString> result;

    QVector3D start = this->m_currentPoint;

    PointSegment *ps = addCommand(command);

    if (ps == NULL || !ps->isArc()) {
        return result;
    }

    QList<PointSegment*> psl = expandArc();

    if (psl.length() == 0) {
        return result;
    }

    // Create an array of new commands out of the of the segments in psl.
    // Don't add them to the gcode parser since it is who expanded them.
    foreach (PointSegment* segment, psl) {
        //Point3d end = segment.point();
        QVector3D end = *segment->point();
        result.append(GcodePreprocessorUtils::generateG1FromPoints(start, end, this->m_inAbsoluteMode, m_truncateDecimalLength));
        start = *segment->point();
    }

    return result;

}
