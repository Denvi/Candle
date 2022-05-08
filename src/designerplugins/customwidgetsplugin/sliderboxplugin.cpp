#include "sliderboxplugin.h"
#include "sliderbox.h"

SliderBoxPlugin::SliderBoxPlugin(QObject *parent): QObject(parent), m_initialized(false)
{

}

void SliderBoxPlugin::initialize(QDesignerFormEditorInterface *core)
{
    if (m_initialized) return;

    m_initialized = true;
}

bool SliderBoxPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *SliderBoxPlugin::createWidget(QWidget *parent)
{
    return new SliderBox(parent);
}

QString SliderBoxPlugin::includeFile() const
{
    return QStringLiteral("sliderbox.h");
}

QString SliderBoxPlugin::name() const
{
    return QStringLiteral("SliderBox");
}

QString SliderBoxPlugin::group() const
{
    return QStringLiteral("Custom widgets");
}

QIcon SliderBoxPlugin::icon() const
{
    return QIcon();
}

QString SliderBoxPlugin::toolTip() const
{
    return QString();
}

QString SliderBoxPlugin::whatsThis() const
{
    return QString();
}

bool SliderBoxPlugin::isContainer() const
{
    return false;
}

QString SliderBoxPlugin::domXml() const
{
    return "<ui language=\"c++\">\n"
           " <widget class=\"SliderBox\" name=\"sliderBox\">\n"
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