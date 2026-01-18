#pragma once

#include "historyitem.h"
#include <QString>

class RowAddedHistoryItem : public HistoryItem
{
public:
    RowAddedHistoryItem(GCodeTableModel *model, int row);

    void undo() const override;
    void redo() const override;

private:
    int m_row;
};