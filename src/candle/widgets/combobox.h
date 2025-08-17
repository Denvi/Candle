// This file is a part of "Candle" application.
// Copyright 2015-2021 Hayrullin Denis Ravilevich

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

public slots:
    void addItems(const QStringList &texts) {QComboBox::addItems(texts);}
    void setItems(const QStringList &texts) {QComboBox::clear(); addItems(texts);}
    QStringList items() {QStringList l; for (int i = 0; i < count(); i++) l << itemText(i); return l;};

signals:
    void returnPressed();

protected:
    void keyPressEvent(QKeyEvent *e);
};

#endif // COMBOBOX_H
