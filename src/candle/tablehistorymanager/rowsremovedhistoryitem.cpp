#include "rowsremovedhistoryitem.h"

RowsRemovedHistoryItem::RowsRemovedHistoryItem(GCodeTableModel *model, int row, const QList<QString> &rows) : HistoryItem(model)
{
    m_row = row;
    m_rows = rows;
}

void RowsRemovedHistoryItem::undo() const
{
    for (auto i = 0; i < m_rows.count(); i++)
    {
        m_model->insertRow(m_row + i);
        m_model->setCommand(m_row + i, m_rows.at(i));
    }
}

void RowsRemovedHistoryItem::redo() const
{
    m_model->removeRows(m_row, m_rows.count());
}