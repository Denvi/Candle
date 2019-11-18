// This file is a part of "Candle" application.
// Copyright 2015-2016 Hayrullin Denis Ravilevich

#ifndef GCODETABLEMODEL_H
#define GCODETABLEMODEL_H

#include <QAbstractTableModel>
#include <QString>

struct GCodeItem
{
    enum States { InQueue, Sent, Processed, Skipped };

    QString command;
    char state;
    QString response;
    int line;
    QStringList args;
};

class GCodeTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit GCodeTableModel(QObject *parent = 0);

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
    bool insertRow(int row, const QModelIndex &parent = QModelIndex());
    bool removeRow(int row, const QModelIndex &parent = QModelIndex());
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex());
    void clear();

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;

    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;

    QList<GCodeItem> &data();

signals:

public slots:

private:
    QList<GCodeItem> m_data;
    QStringList m_headers;
};

#endif // GCODETABLEMODEL_H
