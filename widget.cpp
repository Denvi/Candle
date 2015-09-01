#include <QResizeEvent>
#include "widget.h"

Widget::Widget(QWidget *parent) : QWidget(parent)
{

}

void Widget::resizeEvent(QResizeEvent *re)
{
    emit sizeChanged(re->size());
}

