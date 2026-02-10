#include "storage.h"
#include "storagegroup.h"
#include <QDataStream>

Storage::Storage(QObject *parent) : QObject(parent)
{
}

QStringList Storage::keys() const
{
    return m_data.keys();
}

StorageGroup *Storage::group(const QString &path)
{
    return new StorageGroup(this, path);
}

QByteArray Storage::save() const
{
    QByteArray ba;
    QDataStream ds(&ba, QIODevice::WriteOnly);
    ds << m_data;
    return ba;
}

bool Storage::restore(const QByteArray &data)
{
    if (data.isEmpty())
        return false;
    QDataStream ds(data);
    QHash<QString, QVariant> tmp;
    ds >> tmp;
    if (ds.status() != QDataStream::Ok)
        return false;
    m_data = tmp;
    return true;
}

void Storage::setValue(const QString &fullKey, const QVariant &value)
{
    m_data[fullKey] = value;
}

QVariant Storage::value(const QString &fullKey, const QVariant &def) const
{
    return m_data.value(fullKey, def);
}

bool Storage::contains(const QString &fullKey) const
{
    return m_data.contains(fullKey);
}

void Storage::remove(const QString &fullKey)
{
    m_data.remove(fullKey);
}

void Storage::clear()
{
    m_data.clear();
}