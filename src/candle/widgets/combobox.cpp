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
    if ((e->key() == Qt::Key_Return || e->key() == Qt::Key_Enter) && !currentText().isEmpty())
    {
        auto text = currentText();
        auto index = findText(text);

        // If item exists, remove it to prepare for moving to top
        if (index != -1)
        {
            removeItem(index);
        }
        // If item doesn't exist and we're at max capacity, remove last item
        else if (count() == maxCount())
        {
            removeItem(maxCount() - 1);
        }

        insertItem(0, text);
        setCurrentIndex(0);

        emit returnPressed();

        setCurrentText("");
        setCurrentIndex(-1);
    }
    else
    {
        QComboBox::keyPressEvent(e);
    }
}
