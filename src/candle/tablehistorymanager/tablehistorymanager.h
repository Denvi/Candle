#pragma once

#include "historyitem.h"
#include <QObject>
#include <QList>
#include <QSharedPointer>

class GCodeTableModel;

class TableHistoryManager : public QObject
{
    Q_OBJECT

public:
    TableHistoryManager(GCodeTableModel *model);

    bool undo();
    bool redo();
    void clear();

public slots:
    void onCommandChanged(int row, QString oldValue, QString newValue);
    void onCommandsInserted(int row, const QList<QString> &commands);
    void onRowAdded(int row);
    void onRowsAboutToBeRemoved(const QModelIndex &parent, int first, int last);
    void onRowsRemoved(const QModelIndex &parent, int first, int last);

private:
    GCodeTableModel *m_model;
    QList<QSharedPointer<HistoryItem>> m_items;
    int m_currentIndex;
    bool m_blockUpdates;
    QList<QString> m_rowsAboutToBeRemoved;

    void addItem(QSharedPointer<HistoryItem> item);
};