// This file is a part of "grblControl" application.
// Copyright 2015 Hayrullin Denis Ravilevich

#include <QDebug>
#include <QKeyEvent>
#include "combobox.h"

ComboBox::ComboBox(QWidget *parent) : QComboBox(parent)
{
}

ComboBox::~ComboBox()
{
}

void ComboBox::storeText()
{
    if (this->count() == this->maxCount()) this->removeItem(this->maxCount() - 1);
    this->insertItem(0, this->currentText());
    this->setCurrentIndex(-1);
}

void ComboBox::keyPressEvent(QKeyEvent *e)
{
    if (e->key() == Qt::Key_Return) {
        if (this->count() == this->maxCount()) this->removeItem(this->maxCount() - 1);
    }
    QComboBox::keyPressEvent(e);

    if (e->key() == Qt::Key_Return) {
        emit returnPressed();
        this->setCurrentIndex(-1);
    }
}
