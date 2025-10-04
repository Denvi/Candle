// This file is a part of "Candle" application.
// Copyright 2015-2025 Hayrullin Denis Ravilevich

#include <QFileSystemWatcher>
#include <QTextStream>
#include <QStandardPaths>
#include "frmchecklist.h"
#include "ui_frmchecklist.h"

frmCheckList::frmCheckList(QWidget *parent) : QDialog(parent), ui(new Ui::frmCheckList)
{
    ui->setupUi(this);
}

frmCheckList::~frmCheckList()
{
    delete ui;
}

void frmCheckList::setItems(const QStringList &items)
{
    ui->lstMain->clear();
    
    for (auto item : items)
    {
        auto listItem = new QListWidgetItem(item);
        listItem->setCheckState(Qt::Checked);
        ui->lstMain->addItem(listItem);
    }
}

QList<int> frmCheckList::checkedItemIndexes() const
{
    QList<int> checkedItemIndexes;

    for (auto i = 0; i < ui->lstMain->count(); i++)
    {
        if (ui->lstMain->item(i)->checkState() == Qt::Checked)
            checkedItemIndexes.append(i);
    }

    return checkedItemIndexes;
}