// This file is a part of "Candle" application.
// Copyright 2015-2025 Hayrullin Denis Ravilevich

#pragma once
#include <QDialog>

namespace Ui {
class frmCheckList;
}

class frmCheckList : public QDialog
{
    Q_OBJECT

public:
    explicit frmCheckList(QWidget *parent = 0);
    ~frmCheckList();

    void setItems(const QStringList &items);
    QList<int> checkedItemIndexes() const;

private:
    Ui::frmCheckList *ui;
};
