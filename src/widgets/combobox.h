// This file is a part of "Candle" application.
// Copyright 2015-2016 Hayrullin Denis Ravilevich

#ifndef COMBOBOX_H
#define COMBOBOX_H

#include <QWidget>
#include <QComboBox>

class ComboBox : public QComboBox
{
    Q_OBJECT
public:
    explicit ComboBox(QWidget *parent = 0);
    ~ComboBox();

    void storeText();

signals:
    void returnPressed();

protected:
    void keyPressEvent(QKeyEvent *e);
};

#endif // COMBOBOX_H
