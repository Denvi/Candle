#include "layoutentry.h"
#include <QDebug>

QDataStream &operator<<(QDataStream &out, const LayoutEntry &e) {
    out << e.name << e.devicePanels << e.modificationPanels << e.userPanels << e.hiddenPanels << e.collapsedPanels << e.windowState;
    return out;
}
QDataStream &operator>>(QDataStream &in, LayoutEntry &e) {
    in >> e.name >> e.devicePanels >> e.modificationPanels >> e.userPanels >> e.hiddenPanels >> e.collapsedPanels >> e.windowState;
    return in;
}

QDebug operator<<(QDebug dbg, const LayoutEntry &e)
{
    return dbg << QString("LayoutEntry{name:%1, devicePanels:[%2], modificationPanels:[%3], userPanels:[%4]}")
        .arg(e.name)
        .arg(e.devicePanels.join(", "))
        .arg(e.modificationPanels.join(", "))
        .arg(e.userPanels.join(", "));
}