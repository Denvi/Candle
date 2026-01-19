#pragma once

#include "historyitem.h"
#include <QString>

class RowChangedHistoryItem : public HistoryItem
{
public:
    RowChangedHistoryItem(GCodeTableModel *model, int row, const QByteArray &oldValue, const QByteArray &newValue);

    void undo() const override;
    void redo() const override;

private:
    int m_row;
    QByteArray m_oldValue;
    QByteArray m_newValue;
};