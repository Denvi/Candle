#include "joystickknob.h"
#include <QStyleOption>
#include <QPainter>

JoystickKnob::JoystickKnob(QWidget *parent)
    : QWidget{parent}
{
    //this->setStyleSheet("background: green; border: 1px solid blue;");
    //this->resize(1000,1000);
}

//https://forum.qt.io/topic/149395/inherited-from-qwidget-class-does-not-render/4
//https://doc.qt.io/archives/qt-4.8/stylesheet-reference.html#list-of-stylable-widgets
//https://stackoverflow.com/questions/7276330/qt-stylesheet-for-custom-widget
void JoystickKnob::paintEvent(QPaintEvent *paintEvent)
{
    Q_UNUSED(paintEvent);
    QStyleOption opt;
    opt.init(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);

    painter.setRenderHint(QPainter::Antialiasing); // Opcjonalnie, aby uzyskać gładkie krawędzie
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(0, 255, 0)); // Ustaw kolor na czerwony (możesz zmienić na inny kolor)

    // Oblicz współrzędne początkowe lewego górnego rogu kwadratu, aby środek był na środku QWidget
    int x = (width() - 20) / 2;
    int y = (height() - 20) / 2;

    // Narysuj kółko o średnicy 20 pikseli na środku QWidget
    painter.drawEllipse(x, y, 20, 20);
}
