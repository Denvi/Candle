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

        QImage image(":/images/handle2s1.png");
        int pos = ((double)this->width() - 18) / (this->maximum() - this->minimum()) * (this->m_currentValue - this->minimum()) + 9;
        painter.drawImage(pos - image.width() / 2, (this->height() - image.height()) / 2, image);
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
