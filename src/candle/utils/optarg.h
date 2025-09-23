#pragma once

#include <QString>

inline QString optArg(QString prefix, double v, int width = 0, char fmt  = 'f', int prec  = 4)
{
    return qIsNaN(v)
        ? QString{}
        : QString(" %1%2").arg(prefix).arg(v, width, fmt, prec);
}

template <class T>
inline QString optArg(QString prefix, T v)
{
    return qIsNaN(v)
        ? QString{}
        : QString(" %1%2").arg(prefix).arg(v);
}