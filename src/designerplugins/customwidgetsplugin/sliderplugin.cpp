#include "sliderplugin.h"
#include "slider.h"

SliderPlugin::SliderPlugin(QObject *parent): QObject(parent), m_initialized(false)
{

}

void SliderPlugin::initialize(QDesignerFormEditorInterface *core)
{
    if (m_initialized) return;

    m_initialized = true;
}

bool SliderPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *SliderPlugin::createWidget(QWidget *parent)
{
    return new Slider(parent);
}

QString SliderPlugin::includeFile() const
{
    return QStringLiteral("slider.h");
}

QString SliderPlugin::name() const
{
    return QStringLiteral("Slider");
}

QString SliderPlugin::group() const
{
    return QStringLiteral("Custom widgets");
}

QIcon SliderPlugin::icon() const
{
    return QIcon();
}

QString SliderPlugin::toolTip() const
{
    return QString();
}

QString SliderPlugin::whatsThis() const
{
    return QString();
}

bool SliderPlugin::isContainer() const
{
    return false;
}

QString SliderPlugin::domXml() const
{
    return "<ui language=\"c++\">\n"
           " <widget class=\"Slider\" name=\"slider\">\n"
           "  <property name=\"geometry\">\n"
           "   <rect>\n"
           "    <x>0</x>\n"
           "    <y>0</y>\n"
           "    <width>100</width>\n"
           "    <height>100</height>\n"
           "   </rect>\n"
           "  </property>\n"
           " </widget>\n"
           "</ui>\n";    
}