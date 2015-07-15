#include "gcodetablemodel.h"

GCodeItem::GCodeItem()
{
    this->command = "";
    this->state = "";
    this->status = "";
}

GCodeTableModel::GCodeTableModel(QObject *parent) :
    QAbstractTableModel(parent)
{
    m_headers << "Команда" << "Состояние" << "Статус";
}

QVariant GCodeTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) return QVariant();

    if (index.row() >= m_data.size()) return QVariant();

    if (role == Qt::DisplayRole || role == Qt::EditRole) {
        switch (index.column())
        {
        case 0: return m_data.at(index.row())->command;
        case 1: return m_data.at(index.row())->state;
        case 2: return m_data.at(index.row())->status;
        }
    }
    return QVariant();
}

bool GCodeTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && role == Qt::EditRole) {
        switch (index.column())
        {
        case 0: m_data.at(index.row())->command = value.toString(); break;
        case 1: m_data.at(index.row())->state = value.toString(); break;
        case 2: m_data.at(index.row())->status = value.toString(); break;
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
    m_data.insert(row, new GCodeItem());
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

void GCodeTableModel::clear()
{
    beginResetModel();
    m_data.clear();
    endResetModel();
}

int GCodeTableModel::rowCount(const QModelIndex &parent) const
{
    return m_data.size();
}

int GCodeTableModel::columnCount(const QModelIndex &parent) const
{
    return 3;
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
    if (index.column() == 0) return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
        else return QAbstractTableModel::flags(index);
}
