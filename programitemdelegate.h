#ifndef PROGRAMITEMDELEGATE_H
#define PROGRAMITEMDELEGATE_H

#include <QItemDelegate>

class ProgramItemDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    explicit ProgramItemDelegate(QObject *parent = 0);
    bool eventFilter(QObject *object, QEvent *event);

signals:

public slots:

};

#endif // PROGRAMITEMDELEGATE_H
