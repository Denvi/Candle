#include "programitemdelegate.h"
#include <QEvent>
#include <QKeyEvent>
#include <QDebug>

ProgramItemDelegate::ProgramItemDelegate(QObject *parent) :
    QItemDelegate(parent)
{
}

bool ProgramItemDelegate::eventFilter(QObject *object, QEvent *event)
{
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
        qDebug() << keyEvent->key();
    }
    return object->eventFilter(object, event);
}
