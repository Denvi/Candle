// This file is a part of "Candle" application.
// Copyright 2015-2022 Hayrullin Denis Ravilevich

#include "timeestimator.h"
#include <QDebug>
#include "math.h"

/**
 * Constructor
 * @param segments G-code program line segment list
 * @param steps Axes steps per mm
 * @param maxRates Axes maximum rates mm/min
 * @param accelerations Axes accelerations in mm/min^2
 * @param feedOverride Feed speed override flag
 * @param rapidOverride Rapid speed override flag
 * @param feedOverrideValue Feed speed ratio (0...1)
 * @param rapidOverrideValue Rapid speed ratio (0...1)
 * @param junctionDeviation Junction deviation in mm
 * @param plannerBufferSize Planner buffer size ('BLOCK_BUFFER_SIZE' Grbl parameter in 'planner.h')
 * @param minJunctionVelocity Minimum junction speed ('MINIMUM_JUNCTION_SPEED' Grbl parameter in 'config.h')
 */
TimeEstimator::TimeEstimator(const QList<LineSegment *> &segments, const QList<float> &steps,
                             const QList<int> &maxRates, const QList<int> &accelerations,
                             bool feedOverride, bool rapidOverride, float feedOverrideValue, float rapidOverrideValue,
                             bool laserMode, float spindleDelay, float junctionDeviation, int plannerBufferSize,
                             float minJunctionVelocity)
{
    m_segments = segments;
    m_feedOverride = feedOverride;
    m_rapidOverride = rapidOverride;
    m_feedOverrideValue = feedOverrideValue;
    m_rapidOverrideValue = rapidOverrideValue;
    m_laserMode = laserMode;
    m_spindleDelay = spindleDelay;

    m_junctionDeviation = updateWithDefault(junctionDeviation, m_junctionDeviation);
    m_plannerBufferSize = updateWithDefault(plannerBufferSize, m_plannerBufferSize);
    m_minJunctionVelocity = updateWithDefault(minJunctionVelocity, m_minJunctionVelocity);

    m_steps = updateWithDefault(steps, m_steps);
    m_maxRates = updateWithDefault(maxRates, m_maxRates);
    m_accelerations = updateWithDefault(accelerations, m_accelerations);

    m_cacheNominalVelocity.setCapacity(m_plannerBufferSize);
    m_cacheJunctionVelocity.setCapacity(m_plannerBufferSize);
    m_cacheAcceleration.setCapacity(m_plannerBufferSize);
    m_cacheLength.setCapacity(m_plannerBufferSize);
    m_cacheVector.setCapacity(m_plannerBufferSize);
    m_cacheRefineSegment.setCapacity(m_plannerBufferSize);
    m_segmentBuffer.setCapacity(m_plannerBufferSize);

    reset();
}

/**
 *
 * Resets advance state
 */
void TimeEstimator::reset()
{
    m_currentTime = 0;
    m_currentIndex = 0;
    m_bufferIndex = 0;
    m_currentVelocity = 0;
    m_previousLineNumber = -1;
    m_previousSpindleSpeed = 0;

    m_cacheNominalVelocity.clear();
    m_cacheJunctionVelocity.clear();
    m_cacheAcceleration.clear();
    m_cacheLength.clear();
    m_cacheVector.clear();
    m_cacheRefineSegment.clear();
    m_segmentBuffer.clear();
}

/**
 * Produces a partial time estimate
 * @return 'true' if can advance, 'false' if calculation completed
 */
bool TimeEstimator::advance()
{
    float t;
    const int batchSize = qMax(1, m_segments.count() / 100);
    int i = m_currentIndex;
    int j = m_bufferIndex;

    while ((i < (m_currentIndex + batchSize)) && (i < m_segments.count())) {
        // Current segment params
        LineSegment segment = m_segments.at(i);
        i += refineSegment(i, &segment);

        QVector4D vector = getVector(&segment);
        float acceleration = getAcceleration(&segment);

        // Prepare planner buffer segments
        if (m_segmentBuffer.isEmpty()) {
            j = i;
            m_segmentBuffer.append(segment);
            for (int k = 0; (k < m_plannerBufferSize - 1) && (j < m_segments.count()); k++) {
                LineSegment next = m_segments.at(j);
                j += refineSegment(j, &next);
                m_segmentBuffer.append(next);
            }
        } else if (j < m_segments.count()) {
            LineSegment last = m_segments.at(j);
            j += refineSegment(j, &last);
            m_segmentBuffer.append(last);
        }

        // Determine exit velocity with reverse pass
        float backwardEntryVelocity = 0;
        for (int k = m_segmentBuffer.lastIndex(); (k > m_segmentBuffer.firstIndex()) && (k > segment.index()); k--) {
            float backwardAccelerationVelocity = sqrt(backwardEntryVelocity * backwardEntryVelocity
                        + 2 * getAcceleration(&m_segmentBuffer.at(k)) * getLength(&m_segmentBuffer.at(k)));
            float backwardJunctionVelocity = getJunctionVelocity(&m_segmentBuffer.at(k - 1), &m_segmentBuffer.at(k));
            float backwardNominalVelocity = getNominalVelocity(&m_segmentBuffer.at(k));

            backwardEntryVelocity = qMin(backwardAccelerationVelocity, qMin(backwardJunctionVelocity,
                                                                            backwardNominalVelocity));
        }
        float exitVelocity = backwardEntryVelocity;

        // Forward time estimation
        float nominalVelocity = getNominalVelocity(&segment);
        float t0 = qAbs(nominalVelocity - m_currentVelocity) / acceleration;
        float t2 = qAbs(exitVelocity - nominalVelocity) / acceleration;
        float s1 = vector.length() - (m_currentVelocity + nominalVelocity) / 2 * t0
                   - (nominalVelocity + exitVelocity) / 2 * t2;
        float t1 = s1 / nominalVelocity;

        if (t1 >= 0) {
            // Trapezoid profile
            t = t0 + t1 + t2;
        } else {
            // Triangle or slope profile
            if (qAbs(exitVelocity * exitVelocity - m_currentVelocity * m_currentVelocity) / (2 * acceleration)
                    > vector.length()) {
                // Slope
                exitVelocity = sqrt(m_currentVelocity * m_currentVelocity + 2 * acceleration * vector.length()
                                    * (exitVelocity < m_currentVelocity ? -1.0 : 1.0));
                t = vector.length() / ((exitVelocity + m_currentVelocity) / 2);
            } else {
                // Triangle
                float peakVelocity = sqrt((2 * acceleration * vector.length() + m_currentVelocity * m_currentVelocity
                                           + exitVelocity * exitVelocity) / 2);
                t = (qAbs(peakVelocity - m_currentVelocity) + qAbs(exitVelocity - peakVelocity)) / acceleration;
            }
        }

        // Update time with dwell
        if (!qIsNull(segment.getDwell()) && (segment.getLineNumber() != m_previousLineNumber)) {
            m_previousLineNumber = segment.getLineNumber();
            m_currentTime += segment.getDwell() / 60.0;
        }

        // Update time with spindle speed change
        if (!m_laserMode && !qFuzzyCompare(segment.getSpindleSpeed(), m_previousSpindleSpeed)) {
            m_previousSpindleSpeed = segment.getSpindleSpeed();
            m_currentTime += m_spindleDelay / 60.0;
        }

        // Update time
        if (!qIsNaN(t) && !qIsInf(t)) {
            m_currentTime += t;
        }

        // Next entry velocity is current exit velocity
        m_currentVelocity = exitVelocity;
    }
    m_currentIndex = i;
    m_bufferIndex = j;

    return m_currentIndex < m_segments.count();
}

/**
 * Returns time estimation
 * @return Time estimation value in minutes
 */
float TimeEstimator::time() const
{
    return m_currentTime;
}

/**
 * Returns current calculation progress
 * @return Current calculation progress (0...100)
 */
int TimeEstimator::progress() const
{
    return m_currentIndex * 100 / m_segments.count();
}

/**
 * Calculates time synchronously
 * @return Time estimation value in minutes
 */
float TimeEstimator::calculateTime(std::function<bool()> isCancelled)
{
    reset();

    while (advance() && !(isCancelled && isCancelled()));

    return time();
}

/**
 * Returns nominal segment velocity
 * @param segment Segment
 * @return Nominal velocity in mm/min
 */
float TimeEstimator::getNominalVelocity(const LineSegment *segment)
{
    float result;

    if (m_cacheNominalVelocity.containsIndex(segment->index())) {
        result = m_cacheNominalVelocity.at(segment->index());
    } else {
        result = segment->getSpeed();
        if (m_feedOverride && !segment->isFastTraverse()) {
            result *= m_feedOverrideValue;
        } else if (m_rapidOverride && segment->isFastTraverse()) {
            result *= m_rapidOverrideValue;
        }
        result = qMin(result, limitByAxes(m_maxRates, getVector(segment).normalized()));
        m_cacheNominalVelocity.insert(segment->index(), result);
    }

    return result;
}

/**
 * Returns two segments maximum junction velocity
 * @param segment1 First segment
 * @param segment2 Second segment
 * @return Junction velocity in mm/min
 */
float TimeEstimator::getJunctionVelocity(const LineSegment *segment1, const LineSegment *segment2)
{
    float result;

    if (m_cacheJunctionVelocity.containsIndex(segment1->index())) {
        result = m_cacheJunctionVelocity.at(segment1->index());
    } else {
        QVector4D unit1 = getVector(segment1).normalized();
        QVector4D unit2 = getVector(segment2).normalized();
        QVector4D dot = unit1 * unit2;

        float cosTheta = 0 - (dot.x() + dot.y() + dot.z() + dot.w());

        if (cosTheta > 0.999999) {
            result = m_minJunctionVelocity;
        } else if (cosTheta < -0.999999) {
            result = qInf();
        } else {
            QVector4D junctionUnit = (unit2 - unit1).normalized();
            float sinTheta2 = sqrt(0.5 * (1 - cosTheta));
            result = qMax<float>(m_minJunctionVelocity, sqrt((limitByAxes(m_accelerations, junctionUnit)
                * m_junctionDeviation * sinTheta2) / (1.0 - sinTheta2)));
        }
        m_cacheJunctionVelocity.insert(segment1->index(), result);
    }

    return result;
}

/**
 * Calculates value with unit vector and axes limits
 * @param limits Axes limits
 * @param unit Unit vector
 * @return Output value
 */
float TimeEstimator::limitByAxes(const QList<int> &limits, const QVector4D &unit)
{
    float result = qInf();

    for (int i = 0; (i < limits.count()) && (i < 4); i++) {
        result = qMin(result, qAbs((float) limits.at(i) / unit[i]));
    }

    return result;
}

/**
 * Returns segment acceleration
 * @param segment Segment
 * @return Segment acceleration in mm/min^2
 */
float TimeEstimator::getAcceleration(const LineSegment *segment)
{
    float result;

    if (m_cacheAcceleration.containsIndex(segment->index())) {
        result = m_cacheAcceleration.at(segment->index());
    } else {
        result = limitByAxes(m_accelerations, getVector(segment).normalized());
        m_cacheAcceleration.insert(segment->index(), result);
    }

    return result;
}

/**
 * Returns segment length
 * @param segment Segment
 * @return Segment length in mm
 */
float TimeEstimator::getLength(const LineSegment *segment)
{
    float result;

    if (m_cacheLength.containsIndex(segment->index())) {
        result = m_cacheLength.at(segment->index());
    } else {
        result = getVector(segment).length();
        m_cacheLength.insert(segment->index(), result);
    }

    return result;
}

/**
 * Returns segment vector with values rounded by steps/mm parameters
 * @param segment Segment
 * @return Segment vector
 */
QVector4D TimeEstimator::getVector(const LineSegment *segment)
{
    QVector4D result;

    if (m_cacheVector.containsIndex(segment->index())) {
        result = m_cacheVector.at(segment->index());
    } else {
        QVector4D start(round(segment->modelStart().x() * m_steps.at(0)) / m_steps.at(0),
                        round(segment->modelStart().y() * m_steps.at(1)) / m_steps.at(1),
                        round(segment->modelStart().z() * m_steps.at(2)) / m_steps.at(2),
                        round(segment->axesStart().x() * m_steps.at(3)) / m_steps.at(3));

        QVector4D end(round(segment->modelEnd().x() * m_steps.at(0)) / m_steps.at(0),
                      round(segment->modelEnd().y() * m_steps.at(1)) / m_steps.at(1),
                      round(segment->modelEnd().z() * m_steps.at(2)) / m_steps.at(2),
                      round(segment->axesEnd().x() * m_steps.at(3)) / m_steps.at(3));

        result = end - start;
        if (qIsNaN(result.w())) {
            result.setW(0.0f);
        }
        m_cacheVector.insert(segment->index(), result);
    }

    return result;
}

/**
 * Refines segment by joining sequential segments started at specified list index
 * @param index Segment list index
 * @param segment Segment
 * @return Segment with updated parameters
 */
int TimeEstimator::refineSegment(int index, LineSegment *segment)
{
    int result = 1;

    if (m_cacheRefineSegment.containsIndex(segment->index())) {
        RefineSegmentData d = m_cacheRefineSegment.at(segment->index());

        segment->setEnd(d.end);
        segment->setModelEnd(d.modelEnd);
        segment->setAxesEnd(d.axesEnd);
        result = d.result;
    } else {
        for (int i = index + 1; i < m_segments.count(); i++) {
            if (m_segments.at(i)->index() != segment->index()) {
                segment->setEnd(m_segments.at(i - 1)->getEnd());
                segment->setModelEnd(m_segments.at(i - 1)->modelEnd());
                segment->setAxesEnd(m_segments.at(i - 1)->axesEnd());
                result = i - index;
                break;
            }
        }
        m_cacheRefineSegment.insert(segment->index(), {segment->getEnd(), segment->modelEnd(), segment->axesEnd(),
                                                       result});
    }

    return result;
}

/**
 * Updates parameter with new value
 * @tparam T Parameter type
 * @param value New value
 * @param defaultValue Default value
 * @return Updated parameter
 */
template<typename T>
T TimeEstimator::updateWithDefault(T value, T defaultValue)
{
    return value != 0 ? value : defaultValue;
}

/**
 * Updates parameter list with new values
 * @tparam T Parameter list type
 * @param value New values list
 * @param defaultValue Default values list
 * @return Updated parameter list
 */
template<typename T>
QList<T> TimeEstimator::updateWithDefault(const QList<T> &value, const QList<T> &defaultValue)
{
    QList<T> result = defaultValue;

    for (int i = 0; i < value.count(); i++) {
        if (value.at(i) != 0) {
            result[i] = value.at(i);
        }
    }
    return result;
}