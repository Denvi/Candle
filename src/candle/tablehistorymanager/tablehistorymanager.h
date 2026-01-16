#pragma once

#include "historyitem.h"
#include <QObject>
#include <QList>
#include <QSharedPointer>
#include <QStringList>

class GCodeTableModel;

class TableHistoryManager : public QObject
{
    Q_OBJECT

public:
    TableHistoryManager(GCodeTableModel *model, QObject *parent = nullptr);

    bool undo();
    bool redo();
    void clear();

public slots:
    void onCommandChanged(int row, QString oldValue, QString newValue);
    void onCommandsInserted(int row, const QList<QString> &commands);
    void onRowAdded(int row);
    void onRowsAboutToBeRemoved(const QModelIndex &parent, int first, int last);
    void onRowsRemoved(const QModelIndex &parent, int first, int last);

signals:
    void historyChanged(QStringList history, int currentIndex);

private:
    GCodeTableModel *m_model;
    QList<QSharedPointer<HistoryItem>> m_items;
    int m_currentIndex;
    bool m_blockUpdates;
    QList<QString> m_rowsAboutToBeRemoved;

    void addItem(QSharedPointer<HistoryItem> item);
    void emitHistory();
};