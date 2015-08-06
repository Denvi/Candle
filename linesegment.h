#ifndef LINESEGMENT_H
#define LINESEGMENT_H

#include <QObject>
#include <QVector3D>

class LineSegment : public QObject
{
    Q_OBJECT
public:
    explicit LineSegment(QObject *parent = 0);
    LineSegment(QVector3D a, QVector3D b, int num);
    ~LineSegment();

    int getLineNumber();
    QList<QVector3D> getPointArray();
    QList<double> getPoints();
    QVector3D getStart();
    QVector3D getEnd();
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
};

#endif // LINESEGMENT_H
