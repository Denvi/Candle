// This file is a part of "grblControl" application.
// Copyright 2015 Hayrullin Denis Ravilevich

#ifndef UTIL
#define UTIL

class Util
{
public:
    static double nMin(double v1, double v2)
    {
        if (!std::isnan(v1) && !std::isnan(v2)) return qMin<double>(v1, v2);
        else if (!std::isnan(v1)) return v1;
        else if (!std::isnan(v2)) return v2;
        else return std::numeric_limits<double>::quiet_NaN();
    }

    static double nMax(double v1, double v2)
    {
        if (!std::isnan(v1) && !std::isnan(v2)) return qMax<double>(v1, v2);
        else if (!std::isnan(v1)) return v1;
        else if (!std::isnan(v2)) return v2;
        else return std::numeric_limits<double>::quiet_NaN();
    }
};

#endif // UTIL

