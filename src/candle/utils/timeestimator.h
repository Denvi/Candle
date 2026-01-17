// This file is a part of "Candle" application.
// Copyright 2015-2022 Hayrullin Denis Ravilevich

#ifndef TIMEESTIMATOR_H
#define TIMEESTIMATOR_H

#include "../parser/linesegment.h"
#include <QList>
#include <QContiguousCache>
#include <QVector4D>

class TimeEstimator
{
public:
    TimeEstimator(const QList<LineSegment *> &segments, const QList<float> &steps, const QList<int> &maxRates,
                  const QList<int> &accelerations, bool feedOverride = false, bool rapidOverride = false,
                  float feedOverrideValue = 1.0, float rapidOverrideValue = 1.0, bool laserMode = false,
                  float spindleDelay = 0.0, float junctionDeviation = 0.01, int plannerBufferSize = 15,
                  float minJunctionVelocity = 0.0);

    void reset();
    bool advance();
    float time() const;
    int progress() const;

    float calculateTime(std::function<bool()> isCancelled = nullptr);

private:
    struct RefineSegmentData {
        QVector3D end;
        QVector3D modelEnd;
        QVector3D axesEnd;
        int result;
    };

    QList<LineSegment*> m_segments;
    bool m_feedOverride;
    bool m_rapidOverride;
    float m_feedOverrideValue;
    float m_rapidOverrideValue;
    bool m_laserMode;
    float m_spindleDelay;
    float m_junctionDeviation = 0.01;
    int m_plannerBufferSize = 15;
    float m_minJunctionVelocity = 0.0;
    QList<float> m_steps = {200.0, 200.0, 200.0, 200.0};
    QList<int> m_maxRates = {1000, 1000, 1000, 1000};
    QList<int> m_accelerations = {400 * 3600, 400 * 3600, 400 * 3600, 400 * 3600};

    float m_currentTime;
    int m_currentIndex;
    int m_bufferIndex;
    float m_currentVelocity;
    int m_previousLineNumber;
    double m_previousSpindleSpeed;

    QContiguousCache<float> m_cacheNominalVelocity;
    QContiguousCache<float> m_cacheJunctionVelocity;
    QContiguousCache<float> m_cacheAcceleration;
    QContiguousCache<float> m_cacheLength;
    QContiguousCache<QVector4D> m_cacheVector;
    QContiguousCache<RefineSegmentData> m_cacheRefineSegment;
    QContiguousCache<LineSegment> m_segmentBuffer;

    float getNominalVelocity(const LineSegment *segment);
    float getJunctionVelocity(const LineSegment *segment1, const LineSegment *segment2);
    float limitByAxes(const QList<int> &limits, const QVector4D &unit);
    float getAcceleration(const LineSegment *segment);
    float getLength(const LineSegment *segment);
    QVector4D getVector(const LineSegment *segment);
    int refineSegment(int index, LineSegment *segment);

    template <typename T> T updateWithDefault(T value, T defaultValue);
    template <typename T> QList<T> updateWithDefault(const QList<T> &value, const QList<T> &defaultValue);
};

#endif
