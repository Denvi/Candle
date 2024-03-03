#ifndef JOYSTICKWIDGET_H
#define JOYSTICKWIDGET_H

#include <QScrollArea>
#include <SFML/Graphics.hpp>

class JoystickWidget: public QWidget
{
    Q_OBJECT
    Q_PROPERTY(int posx READ posX WRITE setPosX);
    Q_PROPERTY(int posy READ posY WRITE setPosY);
    Q_PROPERTY(int posz READ posZ WRITE setPosZ);

public:
    JoystickWidget(QWidget *parent = 0);

    QStringList availableCameras() const;
    QStringList availableResolutions() const;

    void setPosX(int pos);
    int posX() const;

    void setPosY(int pos);
    int posY() const;

    void setPosZ(int pos);
    int posZ() const;

    void paintEvent(QPaintEvent *) override;
signals:
    void posChanged(int x, int y, int z);
    void resized(int w, int h);
    void buttonPushed(int btn);

public slots:

    void start();
    void stop();

private slots:
    void iniatializeSFML();
    void updateView();
    void processEvents();

private:
    QScrollArea *m_scrollArea;
    QTimer* updateViewTimer;
    qint64 lastViewUpdate;
    sf::RenderWindow *window;
    int posx = 0;
    int posy = 0;
    int posz = 0;

    QPoint m_pos;

    void resizeEvent(QResizeEvent *e) override;
    void updateSize();
    void runEventQueue();
    void processMoveEvent(sf::Event::JoystickMoveEvent event);
    void processButtonEvent(sf::Event::JoystickButtonEvent event, bool clicked);
    void processConnectedEvent(sf::Event::JoystickConnectEvent event);
    void processDisconnectedEvent();
    void detectConnectedDevices();

    // void hideEvent(QHideEvent *e) override;
    // void showEvent(QShowEvent *e) override;
    void deleteUpdateViewTimer();
    int filterPosition(sf::Event::JoystickMoveEvent event, const int deadZone);
};

#endif
