#pragma once

#include <QObject>

class Coordinates : public QObject
{
    Q_OBJECT
    Q_PROPERTY(double x READ x)
    Q_PROPERTY(double y READ y)
    Q_PROPERTY(double z READ z)
    Q_PROPERTY(double a READ a)

public slots:
    QString toString() const;

public:
    Coordinates();
    Coordinates(const Coordinates& other);
    Coordinates(double x, double y, double z, double a);

    double x() const;
    void setX(double x);

    double y() const;
    void setY(double y);

    double z() const;
    void setZ(double z);

    double a() const;
    void setA(double a);

    Coordinates &operator=(const Coordinates& other);
    friend QDebug operator<<(QDebug debug, const Coordinates &coordinates);

private:
    double m_x;
    double m_y;
    double m_z;
    double m_a;
};

QDebug operator<<(QDebug debug, const Coordinates &coordinates);

Q_DECLARE_METATYPE(Coordinates)
Q_DECLARE_METATYPE(Coordinates*)