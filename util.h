// This file is a part of "grblControl" application.
// Copyright 2015 Hayrullin Denis Ravilevich

#ifndef UTIL
#define UTIL

#include <QColor>
#include <QVector3D>
#include <QEventLoop>
#include <QTimer>

class Util
{
public:
    static double nMin(double v1, double v2)
    {
        if (!std::isnan(v1) && !std::isnan(v2)) return qMin<double>(v1, v2);
        else if (!std::isnan(v1)) return v1;
        else if (!std::isnan(v2)) return v2;
        else return NAN;
    }

    static double nMax(double v1, double v2)
    {
        if (!std::isnan(v1) && !std::isnan(v2)) return qMax<double>(v1, v2);
        else if (!std::isnan(v1)) return v1;
        else if (!std::isnan(v2)) return v2;
        else return NAN;
    }

    static QVector3D colorToVector(QColor color)
    {
        return QVector3D(color.redF(), color.greenF(), color.blueF());
    }

    static void waitEvents(int ms)
    {
        QEventLoop loop;

        QTimer::singleShot(ms, &loop, SLOT(quit()));
        loop.exec();
    }
};

#endif // UTIL

