// This file is a part of "Candle" application.
// Copyright 2015-2021 Hayrullin Denis Ravilevich

#ifndef GCODETABLEMODEL_H
#define GCODETABLEMODEL_H

#include <QAbstractTableModel>
#include <QString>

struct GCodeItem
{
    enum States { InQueue, Sent, Processed, Skipped };

    QByteArray command;
    char state;
    QByteArray response;
    int line = -1;
    QList<QByteArray> args;
};

class GCodeTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit GCodeTableModel(QObject *parent = 0);

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
    bool insertRow(int row, const QModelIndex &parent = QModelIndex());
    bool removeRow(int row, const QModelIndex &parent = QModelIndex());
    void clear();

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;

    QList<GCodeItem> &data();

    void setCommand(int row, const QByteArray &command);
    void insertCommands(int row, const QList<QByteArray> &commands);
    void addRow(int row);

signals:
    void commandChanged(int row, const QByteArray &oldValue, const QByteArray &newValue);
    void commandsInserted(int row, const QList<QByteArray> &commands);
    void rowAdded(int row);

public slots:

private:
    QList<GCodeItem> m_data;
    QStringList m_headers;
};

#endif // GCODETABLEMODEL_H
