#include "rowsinsertedhistoryitem.h"

RowsInsertedHistoryItem::RowsInsertedHistoryItem(GCodeTableModel *model, int row, const QList<QString> &rows) : HistoryItem(model)
{
    m_row = row;
    m_rows = rows;
}

void RowsInsertedHistoryItem::undo() const
{
    m_model->removeRows(m_row, m_rows.count());
}

void RowsInsertedHistoryItem::redo() const
{
    m_model->insertCommands(m_row, m_rows);
}