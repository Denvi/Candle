#include "rowsremovedhistoryitem.h"

RowsRemovedHistoryItem::RowsRemovedHistoryItem(GCodeTableModel *model, int row, const QList<QString> &rows) : HistoryItem(model)
{
    m_row = row;
    m_rows = rows;
}

void RowsRemovedHistoryItem::undo() const
{
    m_model->insertCommands(m_row, m_rows);
}

void RowsRemovedHistoryItem::redo() const
{
    m_model->removeRows(m_row, m_rows.count());
}