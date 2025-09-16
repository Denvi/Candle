#include <QString>
#include <QVariant>
#include <QDataStream>

struct LayoutEntry {
    QString name;
    QStringList devicePanels;
    QStringList modificationPanels;
    QStringList userPanels;
    QStringList hiddenPanels;
    QStringList collapsedPanels;
    QByteArray windowState;

    operator QVariant() const {
        return QVariant::fromValue(*this);
    }
};
Q_DECLARE_METATYPE(LayoutEntry)

QDataStream &operator<<(QDataStream &out, const LayoutEntry &e);
QDataStream &operator>>(QDataStream &in,  LayoutEntry &e);

QDebug operator<<(QDebug dbg, const LayoutEntry &e);