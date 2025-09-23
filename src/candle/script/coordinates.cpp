#include "coordinates.h"
#include <QDebug>

Coordinates::Coordinates() : QObject(), m_x(0), m_y(0), m_z(0), m_a(0)
{

}

Coordinates::Coordinates(const Coordinates &other)
    : QObject(), m_x(other.m_x), m_y(other.m_y), m_z(other.m_z), m_a(other.m_a)
{

}

Coordinates::Coordinates(double x, double y, double z, double a) : QObject(), m_x(x), m_y(y), m_z(z), m_a(a)
{

}

double Coordinates::x() const
{
    return m_x;
}

void Coordinates::setX(double x)
{
    m_x = x;
}

double Coordinates::y() const
{
    return m_y;
}

void Coordinates::setY(double y)
{
    m_y = y;
}

double Coordinates::z() const
{
    return m_z;
}

void Coordinates::setZ(double z)
{
    m_z = z;
}

double Coordinates::a() const
{
    return m_a;
}

void Coordinates::setA(double a)
{
    m_a = a;
}

QString Coordinates::toString() const
{
    return QString("Coordinates(%1, %2, %3, %4)")
        .arg(m_x)
        .arg(m_y)
        .arg(m_z)
        .arg(m_a);
}

Coordinates &Coordinates::operator=(const Coordinates &other)
{
    m_x = other.m_x;
    m_y = other.m_y;
    m_z = other.m_z;
    m_a = other.m_a;

    return *this;
}

QDebug operator<<(QDebug debug, const Coordinates &coordinates)
{
    return debug << coordinates.toString();
}