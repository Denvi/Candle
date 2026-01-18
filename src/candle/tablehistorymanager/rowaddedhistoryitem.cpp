#include "rowaddedhistoryitem.h"

RowAddedHistoryItem::RowAddedHistoryItem(GCodeTableModel *model, int row) : HistoryItem(model)
{
    m_row = row;
}

void RowAddedHistoryItem::undo() const
{
    m_model->removeRow(m_row);
}

void RowAddedHistoryItem::redo() const
{
    m_model->insertRow(m_row);
}