#ifndef SLIDER_H
#define SLIDER_H

#include <QWidget>
#include <QSlider>
#include <QPaintEvent>
#include <QPainter>
#include <QDebug>
#include "customwidgetsshared.h"

class CUSTOMWIDGETS_DLLSPEC Slider : public QSlider
{
    Q_OBJECT
    Q_PROPERTY(int currentValue READ currentValue WRITE setCurrentValue)
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
