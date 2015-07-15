#ifndef ARCPROPERTIES_H
#define ARCPROPERTIES_H

#include <QObject>
#include <QVector3D>

class ArcProperties : public QObject
{
    Q_OBJECT
public:
    explicit ArcProperties(QObject *parent = 0);
    bool isClockwise;
    double radius;
    QVector3D *center;

signals:

public slots:

};

#endif // ARCPROPERTIES_H
