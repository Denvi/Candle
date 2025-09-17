#pragma once

#include <QObject>
#include <QVariant>

class Storage;

class StorageGroup : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString path READ path)
    Q_PROPERTY(QStringList childKeys READ childKeys)
    Q_PROPERTY(QStringList childGroups READ childGroups)

public:
    StorageGroup(Storage *store, const QString &prefix, QObject *parent = nullptr);
    QString path() const { return m_prefix; }

public slots:
    void setValue(const QString &key, const QVariant &value);
    QVariant value(const QString &key, const QVariant &def = QVariant()) const;
    bool contains(const QString &key) const;
    void remove(const QString &key);

    StorageGroup *group(const QString &subPath);

    QStringList childKeys() const;
    QStringList childGroups() const;

private:
    QString fullKey(const QString &key) const;
    Storage *m_store;
    QString m_prefix;
};