// This file is a part of "Candle" application.
// Copyright 2015-2016 Hayrullin Denis Ravilevich

#ifndef GCODETABLEMODEL_H
#define GCODETABLEMODEL_H

#include <QAbstractTableModel>
#include <QString>

struct GCodeArg
{
    enum Codes { G, X, Y, Z };
    char code;
    float value;
};

struct GCodeItem
{
    enum States { InQueue, Sent, Processed };

    QString command;
    QString state;
    QString status;
    int line;
    QStringList args;
};

struct GCodeItemLight
{
    enum States { InQueue, Sent, Processed };

    QString comment;
    QString status;

    char state;
    int line;

//    GCodeArg *args;
//    char argsLength;
    QVector<GCodeArg> args;
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
    void clear();

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;

    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;

signals:

public slots:

private:
    QList<GCodeItem*> m_data;
    QList<QString> m_headers;
};

#endif // GCODETABLEMODEL_H
