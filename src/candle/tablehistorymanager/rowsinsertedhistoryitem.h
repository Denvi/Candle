#pragma once

#include "historyitem.h"
#include <QString>

class RowsInsertedHistoryItem : public HistoryItem
{
public:
    RowsInsertedHistoryItem(GCodeTableModel *model, int row, const QList<QString> &rows);

    void undo() const override;
    void redo() const override;

private:
    int m_row;
    QList<QString> m_rows;
};