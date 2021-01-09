// This file is a part of "Candle" application.
// Copyright 2015-2021 Hayrullin Denis Ravilevich

#include <QDebug>
#include <QDragEnterEvent>
#include <QFrame>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QApplication>
#include "dropwidget.h"
#include "widgetmimedata.h"

DropWidget::DropWidget(QWidget *parent) : QWidget(parent)
{
}

void DropWidget::restoreState(QObject* parent, QStringList panels)
{
    QVBoxLayout *lo = static_cast<QVBoxLayout*>(layout());
    int i = 0;

    foreach (QString s, panels) {
        QGroupBox *b = parent->findChild<QGroupBox*>(s);
        if (b) lo->insertWidget(i++, b);
    }
}

QStringList DropWidget::saveState()
{
    QStringList sl;
    QVBoxLayout *lo = static_cast<QVBoxLayout*>(layout());

    for (int i = 0; i < lo->count(); i++) {
        QString n = lo->itemAt(i)->widget()->objectName();
        if (n.startsWith("grp")) sl << n;
    }

    return sl;
}

void DropWidget::dragEnterEvent(QDragEnterEvent *dee)
{
    if (dee->mimeData()->hasFormat(WidgetMimeData::mimeType())) {
        m_layoutIndex = -2;
        dee->acceptProposedAction();

    }

    QWidget::dragEnterEvent(dee);
}

void DropWidget::dragLeaveEvent(QDragLeaveEvent *dle)
{
    QFrame *f = findChild<QFrame*>(QString(), Qt::FindDirectChildrenOnly);
    if (f) f->setVisible(false);
    // m_layoutIndex = -2;

    QWidget::dragLeaveEvent(dle);
}

void DropWidget::dragMoveEvent(QDragMoveEvent *dme)
{
    if (dme->mimeData()->hasFormat(WidgetMimeData::mimeType())) {

        QFrame *f = findChild<QFrame*>(QString(), Qt::FindDirectChildrenOnly);

        if (f) {
            int y = dme->pos().y();
            QList<QGroupBox*> bl = findChildren<QGroupBox*>(QString(), Qt::FindDirectChildrenOnly);

            QList<int> yl;
            foreach (QGroupBox* b, bl) yl << b->pos().y();
            qSort(yl.begin(), yl.end());

            int i = 0;
            while (y >= yl.at(i) && i < yl.count()) i++;

            if (i != m_layoutIndex) {
                static_cast<QVBoxLayout*>(layout())->insertWidget(i - 1, f);
                if (!f->isVisible()) f->setVisible(true);
                f->update();
            }
            m_layoutIndex = i;
        }
    }

    QWidget::dragMoveEvent(dme);
}

void DropWidget::dropEvent(QDropEvent *de)
{
    if (de->mimeData()->hasFormat(WidgetMimeData::mimeType())) {
        QFrame *f = findChild<QFrame*>(QString(), Qt::FindDirectChildrenOnly);
        if (f) {
            const WidgetMimeData *md = static_cast<const WidgetMimeData*>(de->mimeData());
            f->setVisible(false);
            f->update();
            static_cast<QVBoxLayout*>(layout())->insertWidget(m_layoutIndex - 1, md->widget());
            md->widget()->update();
        }
    }
}