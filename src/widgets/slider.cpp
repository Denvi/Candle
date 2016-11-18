#include "widgets/slider.h"

Slider::Slider(QWidget *parent) : QSlider(parent)
{
    m_currentValue = 250;
}

void Slider::paintEvent(QPaintEvent *ev)
{
    QSlider::paintEvent(ev);

    if (this->currentValue() != this->value()) {

        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);

        QPen pen(0x999999);
        pen.setWidth(3);

        QPolygon poly(QVector<QPoint>() << QPoint(0, 7) << QPoint(-5, 0) << QPoint(5, 0));
        int pos = ((double)this->width() - 18) / (this->maximum() - this->minimum()) * (this->m_currentValue - this->minimum()) + 9;
        poly.translate(pos, 2);

        QImage image(":/images/handle2s1.png");

        painter.setPen(pen);
        painter.setBrush(QBrush(0x999999));
    //    painter.drawPolygon(poly);
//        painter.drawLine(pos, 3, pos, this->height() - 3);
        painter.drawImage(pos - image.width() / 2, 2, image);
    }
}

int Slider::currentValue() const
{
    return m_currentValue;
}

void Slider::setCurrentValue(int currentValue)
{
    if (m_currentValue != currentValue) {
        m_currentValue = currentValue;
        this->repaint();
    }
}
