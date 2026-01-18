#pragma once

#include "../tables/gcodetablemodel.h"

class HistoryItem
{
public:
    virtual ~HistoryItem() = default;

    virtual void undo() const = 0;
    virtual void redo() const = 0;

protected:
    GCodeTableModel *m_model;

    explicit HistoryItem(GCodeTableModel *model) {
        m_model = model;
    }
};