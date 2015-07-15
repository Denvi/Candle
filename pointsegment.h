#ifndef POINTSEGMENT_H
#define POINTSEGMENT_H

#include <QObject>
#include <QVector3D>

#include "arcproperties.h"

class PointSegment : public QObject
{
    Q_OBJECT
public:
    PointSegment(QObject *parent = 0);
    PointSegment(PointSegment *ps);
    PointSegment(const QVector3D *b, int num);
    PointSegment(QVector3D *point, int num, QVector3D *center, double radius, bool clockwise);
    ~PointSegment();
    void setPoint(QVector3D m_point);
    QVector3D* point();

    QVector<double> points();
    void setToolHead(int head);
    int getToolhead();
    void setLineNumber(int num);
    int getLineNumber();
    void setSpeed(double s);
    double getSpeed();
    void setIsZMovement(bool isZ);
    bool isZMovement();
    void setIsMetric(bool m_isMetric);
    bool isMetric();
    void setIsArc(bool isA);
    bool isArc();
    void setIsFastTraverse(bool isF);
    bool isFastTraverse();
    void setArcCenter(QVector3D *center);
    QVector<double> centerPoints();
    QVector3D *center();
    void setIsClockwise(bool clockwise);
    bool isClockwise();
    void setRadius(double rad);
    double getRadius();
    void convertToMetric();

signals:

public slots:

private:
    ArcProperties *m_arcProperties;
    int m_toolhead;
    double m_speed;
    QVector3D *m_point;
    bool m_isMetric;
    bool m_isZMovement;
    bool m_isArc;
    bool m_isFastTraverse;
    int m_lineNumber;
};

#endif // POINTSEGMENT_H
