// This file is a part of "Candle" application.
// Copyright 2015-2021 Hayrullin Denis Ravilevich

#ifndef DROPWIDGET_H
#define DROPWIDGET_H

#include <QWidget>

class DropWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DropWidget(QWidget *parent = 0);
    
    void restoreState(QObject* parent, QStringList panels);
    QStringList saveState();

protected:
    void dragEnterEvent(QDragEnterEvent *dee);
    void dragLeaveEvent(QDragLeaveEvent *dle);
    void dragMoveEvent(QDragMoveEvent *dme);
    void dropEvent(QDropEvent *de);

private:
    int m_layoutIndex;
};

#endif // WIDGET_H
