#ifndef JOYSTICKKNOB_H
#define JOYSTICKKNOB_H

#include <QWidget>

class JoystickKnob : public QWidget
{
    Q_OBJECT
public:
    explicit JoystickKnob(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *paintEvent) override;
signals:
};

#endif // JOYSTICKKNOB_H
