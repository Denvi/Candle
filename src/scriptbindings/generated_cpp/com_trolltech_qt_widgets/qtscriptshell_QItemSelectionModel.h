#ifndef QTSCRIPTSHELL_QITEMSELECTIONMODEL_H
#define QTSCRIPTSHELL_QITEMSELECTIONMODEL_H

#include <qitemselectionmodel.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QItemSelectionModel : public QItemSelectionModel
{
public:
    QtScriptShell_QItemSelectionModel(QAbstractItemModel*  model = 0);
    QtScriptShell_QItemSelectionModel(QAbstractItemModel*  model, QObject*  parent);
    ~QtScriptShell_QItemSelectionModel();

    void childEvent(QChildEvent*  event);
    void clear();
    void clearCurrentIndex();
    void customEvent(QEvent*  event);
    bool  event(QEvent*  event);
    bool  eventFilter(QObject*  watched, QEvent*  event);
    void reset();
    void select(const QItemSelection&  selection, QItemSelectionModel::SelectionFlags  command);
    void select(const QModelIndex&  index, QItemSelectionModel::SelectionFlags  command);
    void setCurrentIndex(const QModelIndex&  index, QItemSelectionModel::SelectionFlags  command);
    void timerEvent(QTimerEvent*  event);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QITEMSELECTIONMODEL_H
