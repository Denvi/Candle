#pragma once

#include "historyitem.h"
#include <QString>

class RowChangedHistoryItem : public HistoryItem
{
public:
    RowChangedHistoryItem(GCodeTableModel *model, int row, QString oldValue, QString newValue);

    void undo() const override;
    void redo() const override;

private:
    int m_row;
    QString m_oldValue;
    QString m_newValue;
};