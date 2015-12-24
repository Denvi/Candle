// This file is a part of "grblControl" application.
// This file was originally ported from "ArcProperties.java" class
// of "Universal GcodeSender" application written by Will Winder
// (https://github.com/winder/Universal-G-Code-Sender)

// Copyright 2015 Hayrullin Denis Ravilevich

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
