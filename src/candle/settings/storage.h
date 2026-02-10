#pragma once

#include <QObject>
#include <QVariant>
#include <QHash>
#include <QByteArray>

class StorageGroup;

class Storage : public QObject
{
    Q_OBJECT

public:
    explicit Storage(QObject *parent = nullptr);
    QStringList keys() const;

    QByteArray save() const;
    bool restore(const QByteArray &data);

    void clear();

public slots:    
    StorageGroup *group(const QString &path = QString());
    void setValue(const QString &fullKey, const QVariant &value);
    QVariant value(const QString &fullKey, const QVariant &def) const;
    bool contains(const QString &fullKey) const;
    void remove(const QString &fullKey);

private:
    QHash<QString, QVariant> m_data;
};