#include "slider.h"

Slider::Slider(QWidget *parent) : QSlider(parent)
{
    m_currentValue = 250;
}

void Slider::paintEvent(QPaintEvent *ev)
{
    QSlider::paintEvent(ev);
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
