// This file is a part of "grblControl" application.
// This file was originally ported from "ArcProperties.java" class
// of "Universal GcodeSender" application written by Will Winder
// (https://github.com/winder/Universal-G-Code-Sender)

// Copyright 2015 Hayrullin Denis Ravilevich

#include "arcproperties.h"

ArcProperties::ArcProperties(QObject *parent) : QObject(parent)
{
    radius = 0;
    center = NULL;
}
