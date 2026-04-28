#include "storage.h"
#include "storagegroup.h"
#include <QStringList>
#include <QRegularExpression>

StorageGroup::StorageGroup(Storage *store, const QString &prefix, QObject *parent)
    : QObject(parent), m_store(store), m_prefix(prefix)
{
    m_prefix = m_prefix.remove(QRegularExpression("^/|/$"));
}

void StorageGroup::setValue(const QString &key, const QVariant &value)
{
    m_store->setValue(fullKey(key), value);
}

QVariant StorageGroup::value(const QString &key, const QVariant &def) const
{
    return m_store->value(fullKey(key), def);
}

bool StorageGroup::contains(const QString &key) const
{
    return m_store->contains(fullKey(key));
}

void StorageGroup::remove(const QString &key)
{
    m_store->remove(fullKey(key));
}

StorageGroup *StorageGroup::group(const QString &subPath)
{
    QString sub = subPath;
    sub = sub.remove(QRegularExpression("^/|/*$"));
    QString newPath = m_prefix.isEmpty() ? sub : (m_prefix + QLatin1Char('/') + sub);

    return new StorageGroup(m_store, newPath, this);
}

QStringList StorageGroup::childKeys() const
{
    const QString prefix = m_prefix.isEmpty() ? QString() : (m_prefix + QLatin1Char('/'));
    const int len = prefix.length();
    QStringList result;
    const QStringList all = m_store->keys();

    for (const QString &k : all)
    {
        if (!k.startsWith(prefix))
            continue;
        const QString tail = k.mid(len);
        if (!tail.contains(QLatin1Char('/')))
            result.append(tail);
    }

    return result;
}

QStringList StorageGroup::childGroups() const
{
    const QString prefix = m_prefix.isEmpty() ? QString() : (m_prefix + QLatin1Char('/'));
    const int len = prefix.length();
    const QStringList all = m_store->keys();
    QStringList groups;

    for (const QString &k : all)
    {
        if (!k.startsWith(prefix))
            continue;
        QString tail = k.mid(len);
        int idx = tail.indexOf(QLatin1Char('/'));
        if (idx <= 0)
            continue;
        QString g = tail.left(idx);
        if (!groups.contains(g))
            groups.append(g);
    }

    return groups;
}

QString StorageGroup::fullKey(const QString &key) const
{
    if (m_prefix.isEmpty())
        return key;

    return m_prefix + QLatin1Char('/') + key;
}