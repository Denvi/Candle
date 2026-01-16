#include "tablehistorymanager.h"
#include "rowchangedhistoryitem.h"
#include "rowsinsertedhistoryitem.h"
#include "rowsremovedhistoryitem.h"
#include "rowaddedhistoryitem.h"

TableHistoryManager::TableHistoryManager(GCodeTableModel *model)
{
    m_model = model;
    m_currentIndex = -1;
    m_blockUpdates = false;

    connect(m_model, &GCodeTableModel::commandChanged, this, &TableHistoryManager::onCommandChanged);
    connect(m_model, &GCodeTableModel::rowAdded, this, &TableHistoryManager::onRowAdded);
    connect(m_model, &GCodeTableModel::commandsInserted, this, &TableHistoryManager::onCommandsInserted);
    connect(m_model, &GCodeTableModel::rowsAboutToBeRemoved, this, &TableHistoryManager::onRowsAboutToBeRemoved);
    connect(m_model, &GCodeTableModel::rowsRemoved, this, &TableHistoryManager::onRowsRemoved);
}

bool TableHistoryManager::undo()
{
    if (m_currentIndex == -1)
        return false;

    m_blockUpdates = true;

    m_items.at(m_currentIndex)->undo();
    m_currentIndex--;

    m_blockUpdates = false;

    return true;
}

bool TableHistoryManager::redo()
{
    if (m_currentIndex == m_items.count() - 1)
        return false;

    m_blockUpdates = true;

    m_currentIndex++;
    m_items.at(m_currentIndex)->redo();

    m_blockUpdates = false;

    return true;
}

void TableHistoryManager::clear()
{
    m_items.clear();
    m_currentIndex = -1;
}

void TableHistoryManager::addItem(QSharedPointer<HistoryItem> item)
{
    m_currentIndex++;

    if (m_currentIndex < m_items.count()) {
        m_items = m_items.mid(0, m_currentIndex);
    }

    m_items.append(std::move(item));
}

void TableHistoryManager::onCommandChanged(int row, QString oldValue, QString newValue)
{
    if (m_blockUpdates || oldValue == newValue)
        return;

    if (row == m_model->rowCount() - 1)
    {
        addItem(QSharedPointer<RowsInsertedHistoryItem>::create(m_model, row, QList<QString> { newValue }));
    }
    else
    {
        addItem(QSharedPointer<RowChangedHistoryItem>::create(m_model, row, oldValue, newValue));
    }
}

void TableHistoryManager::onCommandsInserted(int row, const QList<QString> &commands)
{
    if (m_blockUpdates)
        return;

    addItem(QSharedPointer<RowsInsertedHistoryItem>::create(m_model, row, commands));
}

void TableHistoryManager::onRowAdded(int row)
{
    if (m_blockUpdates)
        return;

    addItem(QSharedPointer<RowAddedHistoryItem>::create(m_model, row));
}

void TableHistoryManager::onRowsAboutToBeRemoved(const QModelIndex &parent, int first, int last)
{
    if (m_blockUpdates)
        return;

    m_rowsAboutToBeRemoved.clear();

    for (auto i = first; i <= last; i++)
        m_rowsAboutToBeRemoved.append(m_model->data(m_model->index(i, 1)).toString());
}

void TableHistoryManager::onRowsRemoved(const QModelIndex &parent, int first, int last)
{
    if (m_blockUpdates)
        return;

    addItem(QSharedPointer<RowsRemovedHistoryItem>::create(m_model, first, m_rowsAboutToBeRemoved));
}