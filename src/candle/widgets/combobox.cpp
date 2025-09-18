// This file is a part of "Candle" application.
// Copyright 2015-2021 Hayrullin Denis Ravilevich

#include <QDebug>
#include <QKeyEvent>
#include "combobox.h"

ComboBox::ComboBox(QWidget *parent) : QComboBox(parent)
{
}

void ComboBox::keyPressEvent(QKeyEvent *e)
{
    if (e->key() == Qt::Key_Return || e->key() == Qt::Key_Enter && !currentText().isEmpty()) {
        // Remove last item if new one entered
        if (count() == maxCount() && !items().contains(currentText()))
            removeItem(maxCount() - 1);

        // Force item add
        QComboBox::keyPressEvent(e);

        emit returnPressed();

        setCurrentIndex(-1);
        setCurrentText("");
    } else {
        QComboBox::keyPressEvent(e);
    }
}
