// This file is a part of "Candle" application.
// This file was originally ported from "ArcProperties.java" class
// of "Universal GcodeSender" application written by Will Winder
// (https://github.com/winder/Universal-G-Code-Sender)

// Copyright 2015-2016 Hayrullin Denis Ravilevich

#ifndef ARCPROPERTIES_H
#define ARCPROPERTIES_H

#include <QVector3D>

class ArcProperties
{
public:
    explicit ArcProperties();
    bool isClockwise;
    double radius;
    QVector3D *center;
};

#endif // ARCPROPERTIES_H
