// This file is a part of "grblControl" application.
// This file was originally ported from "LineSegment.java" class
// of "Universal GcodeSender" application written by Will Winder
// (https://github.com/winder/Universal-G-Code-Sender)

// Copyright 2015 Hayrullin Denis Ravilevich

#ifndef LINESEGMENT_H
#define LINESEGMENT_H

#include <QObject>
#include <QVector3D>

class LineSegment : public QObject
{
    Q_OBJECT
public:
    LineSegment(QObject *parent = 0);
    LineSegment(QVector3D a, QVector3D b, int num);
    LineSegment(LineSegment *initial);
    ~LineSegment();

    int getLineNumber();
    QList<QVector3D> getPointArray();
    QList<double> getPoints();

    QVector3D getStart();
    void setStart(QVector3D vector);

    QVector3D getEnd();
    void setEnd(QVector3D vector);

    void setToolHead(int head);
    int getToolhead();
    void setSpeed(double s);
    double getSpeed();
    void setIsZMovement(bool isZ);
    bool isZMovement();
    void setIsArc(bool isA);
    bool isArc();
    void setIsFastTraverse(bool isF);
    bool isFastTraverse();

    bool contains(QVector3D point);

    bool drawn() const;
    void setDrawn(bool drawn);

    bool isMetric() const;
    void setIsMetric(bool isMetric);

    bool isAbsolute() const;
    void setIsAbsolute(bool isAbsolute);

    bool isHightlight() const;
    void setIsHightlight(bool isHightlight);

    int vertexIndex() const;
    void setVertexIndex(int vertexIndex);

signals:

public slots:

private:
    int m_toolhead;
    double m_speed;
    QVector3D m_first, m_second;

    // Line properties
    bool m_isZMovement;
    bool m_isArc;
    bool m_isFastTraverse;
    int m_lineNumber;
    bool m_drawn;
    bool m_isMetric;
    bool m_isAbsolute;
    bool m_isHightlight;
    int m_vertexIndex;
};

#endif // LINESEGMENT_H
