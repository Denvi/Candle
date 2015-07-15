#include "tablewidget.h"
#include <QEvent>
#include <QKeyEvent>
#include <QDebug>

TableWidget::TableWidget(QWidget *parent) :
    QTableWidget(parent)
{
}

void TableWidget::keyPressEvent(QKeyEvent *event)
{
//    qDebug() << "keyPressEvent: " << event->key();

    if (this->state() != this->EditingState) {
        switch (event->key())
        {
        case Qt::Key_Return:
            this->editItem(this->currentItem());
            break;
        case Qt::Key_Tab:
            if (this->currentRow() < (this->rowCount() - 1)) {
                this->setCurrentCell(this->currentRow() + 1, 0);
            }
            return;
        case Qt::Key_Backtab:
            if (this->currentRow() > 0) {
                this->setCurrentCell(this->currentRow() - 1, 0);
            }
            return;
        }
    }

    QTableWidget::keyPressEvent(event);
}
