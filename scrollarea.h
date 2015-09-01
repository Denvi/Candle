#ifndef SCROLLAREA_H
#define SCROLLAREA_H

#include <QWidget>
#include <QScrollArea>
#include "widget.h"
#include "groupbox.h"

class ScrollArea : public QScrollArea
{
    Q_OBJECT

public:
    explicit ScrollArea(QWidget *parent = 0);

    QSize sizeHint() const;
    void setWidget(QWidget *widget);

public slots:

signals:
    void sizeHintRequest();

protected:
    void resizeEvent(QResizeEvent *re);
    void mouseMoveEvent(QMouseEvent *me);

private slots:
    void onContentSizeChanged(QSize newSize);
    void onVerticalScrollBarValueChanged(int newValue);
    void onVerticalScrollBarRangeChanged(int, int);
    void onScroll(int dx, int dy);

private:
    bool m_update;

    void updateBorders();
};

#endif // SCROLLAREA_H
