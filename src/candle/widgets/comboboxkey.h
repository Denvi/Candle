#ifndef COMBOBOXKEY_H
#define COMBOBOXKEY_H

#include <QWidget>
#include <QComboBox>
#include <QKeyEvent>
#include <QDebug>

class ComboBoxKey : public QComboBox
{
public:
    explicit ComboBoxKey(QWidget *parent = 0);

    void setCurrentNext();
    void setCurrentPrevious();

    void setItems(QStringList items, bool keepCurrentText = false);
    QStringList items();

protected:
    void keyPressEvent(QKeyEvent *e);
    void keyReleaseEvent(QKeyEvent *e);

private:
    bool isBlockedKey(int key);
};

#endif // COMBOBOXKEY_H
