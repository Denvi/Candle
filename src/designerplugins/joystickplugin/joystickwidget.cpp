#include "joystickwidget.h"

#include <QScrollBar>
#include <QMouseEvent>
#include <QPainter>
#include <QVBoxLayout>
#include <QDebug>
#include <QTimer>
#include <QStyleOption>
#include <QDateTime>

JoystickWidget::JoystickWidget(QWidget *parent): QWidget(parent), updateViewTimer(nullptr), lastViewUpdate(0)
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    this->setLayout(layout);

    QTimer::singleShot(100, Qt::PreciseTimer, this, SLOT(iniatializeSFML()));
}

//https://forum.qt.io/topic/149395/inherited-from-qwidget-class-does-not-render/4
//https://doc.qt.io/archives/qt-4.8/stylesheet-reference.html#list-of-stylable-widgets
//https://stackoverflow.com/questions/7276330/qt-stylesheet-for-custom-widget
void JoystickWidget::paintEvent(QPaintEvent *paintEvent)
{
    Q_UNUSED(paintEvent);
    // QStyleOption opt;
    // opt.init(this);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);

    painter.setPen(Qt::NoPen);

    painter.setBrush(QColor(170, 170, 170));
    painter.drawEllipse(1, 1, width() - 2, height() - 2);

    const float WIDTH = width();
    const float HEIGHT = height();
    const float KNOB_SIZE = 20;

    /*
     * -100 = 0
     * 100 = WIDTH - KNOB_SIZE
     * 0 = WIDTH / 2 - KNOB_SIZE / 2
     * POS = (WIDTH - KNOB_SIZE) / 200 * POS
     *
     * 0 = 0
     * 200 = WIDTH - KNOB_SIZE
     * POS = (WIDTH - KNOB_SIZE) / 200 * POS
     *
     * 200 = 200
     *
     */

    int x = (WIDTH - KNOB_SIZE) / 200.0 * (this->posx + 100);
    int y = (HEIGHT - KNOB_SIZE) / 200.0 * (this->posy + 100);

    painter.setBrush(QColor(0, 255, 0));
    painter.drawEllipse(x, y, KNOB_SIZE, KNOB_SIZE);

    int z = (HEIGHT - KNOB_SIZE) / 200 * (this->posz + 100);

    painter.setBrush(QColor(0, 0, 255));
    painter.drawEllipse(WIDTH - KNOB_SIZE, z, KNOB_SIZE, KNOB_SIZE);

    //

    painter.setPen(Qt::black);
    QFont font = painter.font();
    font.setPointSize(12);
    painter.setFont(font);

    QString text = QString("WH: %1 %2\nX: %3 (%4)\nY: %5 (%6)\nZ: %7 (%8)\n")
                    .arg(WIDTH)
                    .arg(HEIGHT)
                    .arg(this->posx).arg(x)
                    .arg(this->posy).arg(y)
                    .arg(this->posz).arg(z);

    painter.drawText(this->rect(), Qt::AlignRight, text);
}

void JoystickWidget::iniatializeSFML()
{
    this->window = new sf::RenderWindow(sf::VideoMode(400, 775), "Joystick", sf::Style::None);
    this->window->setVisible(false);

    this->detectConnectedDevices();
    this->runEventQueue();
}

void JoystickWidget::processEvents()
{
    sf::Event event;

    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wswitch"
    while (this->window->pollEvent(event)) {
        switch (event.type) {
            case sf::Event::JoystickMoved:
                this->processMoveEvent(event.joystickMove);
                break;
            case sf::Event::JoystickButtonPressed:
                this->processButtonEvent(event.joystickButton, true);
                break;
            case sf::Event::JoystickButtonReleased:
                this->processButtonEvent(event.joystickButton, false);
                break;
            case sf::Event::JoystickConnected:
                this->processConnectedEvent(event.joystickConnect);
                break;
            case sf::Event::JoystickDisconnected:
                this->processDisconnectedEvent();
                break;
        };
    }
    #pragma GCC diagnostic pop

    this->runEventQueue();
}

void JoystickWidget::runEventQueue()
{
    QTimer::singleShot(10, Qt::PreciseTimer, this, SLOT(processEvents()));
}

void JoystickWidget::deleteUpdateViewTimer()
{
    this->updateViewTimer->stop();
    this->updateViewTimer->deleteLater();
    this->updateViewTimer = nullptr;
}

int JoystickWidget::filterPosition(sf::Event::JoystickMoveEvent event, const int deadZone)
{
    int pos = event.position;
    if (abs(pos) < deadZone) {
        pos = 0;
    }
    if (pos > 98) {
        return 100;
    }
    if (pos < -98) {
        return -100;
    }
    pos = ((int)(pos / 20)) * 20;

    return pos;
}

void JoystickWidget::processMoveEvent(sf::Event::JoystickMoveEvent event)
{
    const int msBetweenUpdates = 10;
    const int deadZone = 25;

    switch (event.axis) {
        case sf::Joystick::Axis::X:
            this->posx = filterPosition(event, deadZone);
            break;
        case sf::Joystick::Axis::Y:
            this->posy = filterPosition(event, deadZone);
            break;
        case sf::Joystick::Axis::Z:
            this->posz = filterPosition(event, deadZone);
            break;
        default:
            return;
    };

    emit posChanged(this->posx, this->posy, this->posz);

    const qint64 now = QDateTime::currentMSecsSinceEpoch();
    if (now - this->lastViewUpdate > msBetweenUpdates) {
        this->repaint();
        this->lastViewUpdate = now;

        if (this->updateViewTimer != nullptr) {
            this->deleteUpdateViewTimer();
        }

        return;
    }

    if (this->updateViewTimer != nullptr) {
        this->deleteUpdateViewTimer();
    }

    this->updateViewTimer = new QTimer(this);
    this->updateViewTimer->setSingleShot(true);
    this->updateViewTimer->setInterval(msBetweenUpdates);
    this->connect(this->updateViewTimer, &QTimer::timeout, this, &JoystickWidget::updateView);
    this->updateViewTimer->start();
}

void JoystickWidget::updateView()
{
    this->updateViewTimer = nullptr;

    QTimer *sender = qobject_cast<QTimer*>(this->sender());
    sender->deleteLater();

    this->repaint();
}

void JoystickWidget::processButtonEvent(sf::Event::JoystickButtonEvent event, bool clicked)
{
    qDebug() << event.joystickId << event.button << clicked;

    emit buttonPushed(event.button);
}

void JoystickWidget::processConnectedEvent(sf::Event::JoystickConnectEvent event)
{
    qDebug() << event.joystickId;
}

void JoystickWidget::processDisconnectedEvent()
{
    qDebug() << "disconnect";
}

void JoystickWidget::detectConnectedDevices()
{
    for (unsigned int i = 0; i < sf::Joystick::Count; ++i)
    {
        if (sf::Joystick::isConnected(i))
        {
            qDebug() << "joy";
            break;
        }
    }
}

void JoystickWidget::setPosX(int pos)
{
    this->posx = pos;
}

int JoystickWidget::posX() const
{
    return this->posx;
}

void JoystickWidget::setPosY(int pos)
{
    this->posy = pos;
}

int JoystickWidget::posY() const
{
    return this->posy;
}

void JoystickWidget::setPosZ(int pos)
{
    this->posz = pos;
}

int JoystickWidget::posZ() const
{
    return this->posz;
}

void JoystickWidget::start()
{

}

void JoystickWidget::stop()
{

}

void JoystickWidget::resizeEvent(QResizeEvent *e)
{
    QWidget::resizeEvent(e);

    emit resized(e->size().width(), e->size().height());
}

void JoystickWidget::updateSize()
{
}

// void JoystickWidget::hideEvent(QHideEvent *e)
// {
//     QWidget::hideEvent(e);
// }

// void JoystickWidget::showEvent(QShowEvent *e)
// {
//     QWidget::showEvent(e);
// }
