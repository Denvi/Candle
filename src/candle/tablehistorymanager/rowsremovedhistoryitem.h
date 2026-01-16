#pragma once

#include "historyitem.h"
#include <QString>

class RowsRemovedHistoryItem : public HistoryItem
{
public:
    RowsRemovedHistoryItem(GCodeTableModel *model, int row, const QList<QString> &rows);

    void undo() const override;
    void redo() const override;

private:
    int m_row;
    QList<QString> m_rows;
};