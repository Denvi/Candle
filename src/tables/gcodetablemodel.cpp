// This file is a part of "Candle" application.
// Copyright 2015-2016 Hayrullin Denis Ravilevich

#include "gcodetablemodel.h"

GCodeTableModel::GCodeTableModel(QObject *parent) :
    QAbstractTableModel(parent)
{
    m_headers << tr("#") << tr("Command") << tr("State") << tr("Response") << tr("Line") << tr("Args");
}

QVariant GCodeTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) return QVariant();

    if (index.row() >= m_data.size()) return QVariant();

    if (role == Qt::DisplayRole || role == Qt::EditRole) {
        switch (index.column())
        {
        case 0: return index.row() == this->rowCount() - 1 ? QString() : QString::number(index.row() + 1);
        case 1: return m_data.at(index.row()).command;
        case 2:
            if (index.row() == this->rowCount() - 1) return QString();
            switch (m_data.at(index.row()).state) {
            case GCodeItem::InQueue: return tr("In queue");
            case GCodeItem::Sent: return tr("Sent");
            case GCodeItem::Processed: return tr("Processed");
            case GCodeItem::Skipped: return tr("Skipped");
            }
            return tr("Unknown");
        case 3: return m_data.at(index.row()).response;
        case 4: return m_data.at(index.row()).line;
        case 5: return QVariant(m_data.at(index.row()).args);
        }
    }

    if (role == Qt::TextAlignmentRole) {
        switch (index.column()) {
        case 0: return Qt::AlignCenter;
        default: return Qt::AlignVCenter;
        }
    }

    return QVariant();
}

bool GCodeTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && role == Qt::EditRole) {
        switch (index.column())
        {
        case 0: return false;
        case 1: m_data[index.row()].command = value.toString(); break;
        case 2: m_data[index.row()].state = value.toInt(); break;
        case 3: m_data[index.row()].response = value.toString(); break;
        case 4: m_data[index.row()].line = value.toInt(); break;
        case 5: m_data[index.row()].args = value.toStringList(); break;
        }
        emit dataChanged(index, index);
        return true;
    }
    return false;
}

bool GCodeTableModel::insertRow(int row, const QModelIndex &parent)
{
    if (row > rowCount()) return false;

    beginInsertRows(parent, row, row);
    m_data.insert(row, GCodeItem());
    endInsertRows();
    return true;
}

bool GCodeTableModel::removeRow(int row, const QModelIndex &parent)
{
    //if (!index(row, 0).isValid()) return false;

    beginRemoveRows(parent, row, row);
    m_data.removeAt(row);
    endRemoveRows();
    return true;
}

bool GCodeTableModel::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row + count - 1);
    m_data.erase(m_data.begin() + row, m_data.begin() + row + count);
    endRemoveRows();
    return true;
}

void GCodeTableModel::clear()
{
    beginResetModel();

//    foreach (GCodeItem* item, m_data) delete item;

    m_data.clear();
    endResetModel();
}

int GCodeTableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)

    return m_data.size();
}

int GCodeTableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)

    return 6;
}

QVariant GCodeTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole) return QVariant();
    if (orientation == Qt::Horizontal) return m_headers.at(section);
    else return QString::number(section + 1);
}

Qt::ItemFlags GCodeTableModel::flags(const QModelIndex &index) const
{
    if (!index.isValid()) return NULL;
    if (index.column() == 1) return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
    else return QAbstractTableModel::flags(index);
}

QList<GCodeItem> &GCodeTableModel::data()
{
    return m_data;
}
