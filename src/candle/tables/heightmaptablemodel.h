// This file is a part of "Candle" application.
// Copyright 2015-2016 Hayrullin Denis Ravilevich

#ifndef HEIGHTMAPTABLEMODEL_H
#define HEIGHTMAPTABLEMODEL_H

#include <QObject>
#include <QAbstractTableModel>

class HeightMapTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit HeightMapTableModel(QObject *parent = 0);

    void resize(int cols, int rows);

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
    bool insertRow(int row, const QModelIndex &parent = QModelIndex());
    bool removeRow(int row, const QModelIndex &parent = QModelIndex());
    void clear();

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;

    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;

signals:
    void dataChangedByUserInput();

private:
//    QList<QList<double>> m_data;
    QVector<QVector<double>> m_data;
    QList<QString> m_headers;
};

#endif // HEIGHTMAPTABLEMODEL_H
