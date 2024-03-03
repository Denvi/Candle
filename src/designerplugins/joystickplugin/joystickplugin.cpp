#include "joystickplugin.h"
#include "joystickwidget.h"
#include <SFML/Graphics.hpp>

#include <QDebug>
#include <QTimer>

JoystickPlugin::JoystickPlugin(QObject *parent): QObject(parent), m_initialized(false)
{
    qDebug() << "Create!! aaa!";

//    QTimer::singleShot(100, Qt::PreciseTimer, this, SLOT(abc()));

    qDebug() << "Create OK?";
}

// void JoystickPlugin::abc()
// {
//     // this->window = new sf::RenderWindow(sf::VideoMode(400, 775), "Joystick", sf::Style::None);
//     // this->window->setVisible(false);

//     this->detectConnectedDevices();
//     this->runEventQueue();
// }

// void JoystickPlugin::processEvents()
// {
//     // sf::Event event;
//     // #pragma GCC diagnostic push
//     // #pragma GCC diagnostic ignored "-Wswitch"
//     // while (this->window->pollEvent(event)) {
//     //     switch (event.type) {
//     //         case sf::Event::JoystickMoved:
//     //             this->processMoveEvent(event.joystickMove);
//     //             break;
//     //         case sf::Event::JoystickButtonPressed:
//     //             this->processButtonEvent(event.joystickButton, true);
//     //             break;
//     //         case sf::Event::JoystickButtonReleased:
//     //             this->processButtonEvent(event.joystickButton, false);
//     //             break;
//     //         case sf::Event::JoystickConnected:
//     //             this->processConnectedEvent(event.joystickConnect);
//     //             break;
//     //         case sf::Event::JoystickDisconnected:
//     //             this->processDisconnectedEvent();
//     //             break;
//     //     };
//     // }
//     // #pragma GCC diagnostic pop

//     this->runEventQueue();
// }

void JoystickPlugin::initialize(QDesignerFormEditorInterface *core)
{
    if (m_initialized) return;

    qDebug() << "Initialize";

    m_initialized = true;
}

// void JoystickPlugin::runEventQueue()
// {
// //    QTimer::singleShot(10, Qt::PreciseTimer, this, SLOT(processEvents()));
// }

// void JoystickPlugin::processMoveEvent(sf::Event::JoystickMoveEvent event)
// {
//     qDebug() << event.joystickId << event.axis << event.position;
// }

// void JoystickPlugin::processButtonEvent(sf::Event::JoystickButtonEvent event, bool clicked)
// {
//     qDebug() << event.joystickId << event.button << clicked;
// }

// void JoystickPlugin::processConnectedEvent(sf::Event::JoystickConnectEvent event)
// {
//     qDebug() << event.joystickId;
// }

// void JoystickPlugin::processDisconnectedEvent()
// {
//     qDebug() << "disconnect";
// }

// void JoystickPlugin::detectConnectedDevices()
// {
//     for (unsigned int i = 0; i < sf::Joystick::Count; ++i)
//     {
//         // if (sf::Joystick::isConnected(i))
//         // {
//         //     qDebug() << "joy";
//         //     break;
//         // }
//     }
// }

bool JoystickPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *JoystickPlugin::createWidget(QWidget *parent)
{
    qDebug() << "Create widget";

    return new JoystickWidget(parent);
}

QString JoystickPlugin::includeFile() const
{
    return QStringLiteral("joystickwidget.h");
}

QString JoystickPlugin::name() const
{
    return QStringLiteral("JoystickWidget");
}

QString JoystickPlugin::group() const
{
    return QStringLiteral("Custom widgets");
}

QIcon JoystickPlugin::icon() const
{
    return QIcon();
}

QString JoystickPlugin::toolTip() const
{
    return QString();
}

QString JoystickPlugin::whatsThis() const
{
    return QString();
}

bool JoystickPlugin::isContainer() const
{
    return false;
}

QString JoystickPlugin::domXml() const
{
    return R"(
        <ui language="c++">
            <widget class="JoystickWidget" name="JoystickWidget">
                <property name="geometry">
                     <rect>
                         <x>0</x>
                         <y>0</y>
                         <width>0</width>
                         <height>0</height>
                     </rect>
                </property>
            </widget>
        </ui>
    )";
}
