#ifndef TEACHPOINT_H
#define TEACHPOINT_H

#include <QString>

// A single recorded position in "teach mode". Coordinates are work
// coordinates (same frame as the WPos readout), in the unit Candle is
// currently displaying (mm or inch).
struct TeachPoint
{
    QString label;
    double x = 0;
    double y = 0;
    double z = 0;
    double a = 0;
    bool axisAEnabled = false;
    double feed = 500;
    bool pauseAfter = false;
};

#endif // TEACHPOINT_H
