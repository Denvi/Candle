#include "settingsprofileentry.h"
#include <QDebug>

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

static void registerTypes()
{
    qRegisterMetaType<SettingsProfileEntry>();
    qRegisterMetaTypeStreamOperators<SettingsProfileEntry>("SettingsProfileEntry");
    QMetaType::registerDebugStreamOperator<SettingsProfileEntry>();
}
Q_CONSTRUCTOR_FUNCTION(registerTypes)