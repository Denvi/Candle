#include "settingsprofileentry.h"

QDataStream &operator<<(QDataStream &out, const SettingsProfileEntry &e)
{
    out  << e.name << e.settings;
    return out;
}

QDataStream &operator>>(QDataStream &in, SettingsProfileEntry &e)
{
    in  >> e.name >> e.settings;
    return in;
}