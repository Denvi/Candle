#include <QString>
#include <QVariant>
#include <QDataStream>
#include <QVector3D>

#include <QString>
#include <QVector3D>
#include <QList>
#include <QMap>

#include <QString>
#include <QStringList>
#include <QVariant>
#include <QSize>
#include <QMap>

struct SettingsProfileEntry
{
    QString name;
    QByteArray settings;

    operator QVariant() const {
        return QVariant::fromValue(*this);
    }
};

Q_DECLARE_METATYPE(SettingsProfileEntry)

QDataStream &operator<<(QDataStream &out, const SettingsProfileEntry &e);
QDataStream &operator>>(QDataStream &in,  SettingsProfileEntry &e);