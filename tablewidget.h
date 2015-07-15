#ifndef TABLEWIDGET_H
#define TABLEWIDGET_H

#include <QTableWidget>

class TableWidget : public QTableWidget
{
    Q_OBJECT
public:
    explicit TableWidget(QWidget *parent = 0);

signals:

public slots:

protected:
    virtual void keyPressEvent(QKeyEvent *event);

};

#endif // TABLEWIDGET_H
