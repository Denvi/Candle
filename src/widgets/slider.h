#ifndef SLIDER_H
#define SLIDER_H

#include <QWidget>
#include <QSlider>
#include <QPaintEvent>
#include <QPainter>
#include <QDebug>

class Slider : public QSlider
{
    Q_OBJECT
public:
    explicit Slider(QWidget *parent = 0);

    int currentValue() const;
    void setCurrentValue(int currentValue);

protected:
    void paintEvent(QPaintEvent *ev);

private:
    int m_currentValue;

};

#endif // SLIDER_H
