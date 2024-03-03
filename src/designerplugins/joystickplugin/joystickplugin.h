#include <QDesignerCustomWidgetInterface>
#include <SFML/Graphics.hpp>

class JoystickPlugin: public QObject, QDesignerCustomWidgetInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QDesignerCustomWidgetInterface")
    Q_INTERFACES(QDesignerCustomWidgetInterface)

public:
    explicit JoystickPlugin(QObject *parent = 0);

    bool isContainer() const override;
    bool isInitialized() const override;
    QIcon icon() const override;
    QString domXml() const override;
    QString group() const override;
    QString includeFile() const override;
    QString name() const override;
    QString toolTip() const override;
    QString whatsThis() const override;
    QWidget *createWidget(QWidget *parent) override;
    void initialize(QDesignerFormEditorInterface *core) override;

private:
    bool m_initialized;
    //sf::RenderWindow *window;
    //void runEventQueue();
    // void processMoveEvent(sf::Event::JoystickMoveEvent event);
    // void processButtonEvent(sf::Event::JoystickButtonEvent event, bool clicked);
    // void processConnectedEvent(sf::Event::JoystickConnectEvent event);
    // void processDisconnectedEvent();
    // void detectConnectedDevices();

private slots:
    //void abc();
    //void processEvents();

};
