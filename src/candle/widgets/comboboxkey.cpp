#include "comboboxkey.h"

ComboBoxKey::ComboBoxKey(QWidget *parent) : QComboBox(parent)
{
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

void ComboBoxKey::setItems(QStringList items, bool keepCurrentText)
{
    auto storedText = this->currentText();

    clear();

    if (items.isEmpty()) return;

    foreach (QString item, items) {
        insertItem(count(), item);
    }

    if (keepCurrentText) {
        auto currentIndex = this->items().indexOf(storedText);
        if (currentIndex != -1)
            setCurrentIndex(currentIndex);

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
