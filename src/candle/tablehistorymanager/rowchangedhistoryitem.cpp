#include "rowchangedhistoryitem.h"

RowChangedHistoryItem::RowChangedHistoryItem(GCodeTableModel *model, int row, QString oldValue, QString newValue) : HistoryItem(model)
{
    m_row = row;
    m_oldValue = oldValue;
    m_newValue = newValue;
}

void RowChangedHistoryItem::undo() const
{
    m_model->setCommand(m_row, m_oldValue);
}

void RowChangedHistoryItem::redo() const
{
    m_model->setCommand(m_row, m_newValue);
}