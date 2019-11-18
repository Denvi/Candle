#include "comboboxkey.h"

ComboBoxKey::ComboBoxKey(QWidget *parent) : QComboBox(parent)
{
}

void ComboBoxKey::setEditable(bool editable)
{
    if (!editable) {
        if (currentText() != itemText(currentIndex())) {
            // Remove user item if exist
            QString value = currentText();
            if (itemData(count() - 1) == 1) {
                removeItem(count() - 1);
                removeItem(count() - 1);
            }

            // Add user item to the end of list
            insertSeparator(count());
            addItem(value, 1);
            setCurrentIndex(count() - 1);
        }
    }

    QComboBox::setEditable(editable);
}

void ComboBoxKey::setCurrentNext()
{
    do {
        setCurrentIndex(qMin(currentIndex() + 1, count() - 1));
    } while (currentText().isEmpty());
}

void ComboBoxKey::setCurrentPrevious()
{
    do {
        setCurrentIndex(qMax(currentIndex() - 1, 0));
    } while (currentText().isEmpty());
}

void ComboBoxKey::setItems(QStringList items)
{
    if (items.isEmpty()) return;

    clear();

    bool userItem = false;
    foreach (QString item, items) {
        if (item.isEmpty()) {
            insertSeparator(count());
            userItem = true;
        } else {
            insertItem(count(), item, userItem ? 1 : QVariant());
        }
    }
}

QStringList ComboBoxKey::items()
{
    QStringList items;

    for (int i = 0; i < count(); i++) items.append(itemText(i));

    return items;
}

void ComboBoxKey::keyPressEvent(QKeyEvent *e)
{
    if (this->isEditable() || !isBlockedKey(e->key())) QComboBox::keyPressEvent(e);
}

void ComboBoxKey::keyReleaseEvent(QKeyEvent *e)
{
    if (this->isEditable() || !isBlockedKey(e->key())) QComboBox::keyReleaseEvent(e);
}

bool ComboBoxKey::isBlockedKey(int key)
{
    return key != Qt::Key_ScrollLock  && key != Qt::Key_Down && key != Qt::Key_Up;
}
