#include "colorpickerplugin.h"
#include "colorpicker.h"

ColorPickerPlugin::ColorPickerPlugin(QObject *parent): QObject(parent), m_initialized(false)
{

}

void ColorPickerPlugin::initialize(QDesignerFormEditorInterface *core)
{
    if (m_initialized) return;

    m_initialized = true;
}

bool ColorPickerPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *ColorPickerPlugin::createWidget(QWidget *parent)
{
    return new ColorPicker(parent);
}

QString ColorPickerPlugin::includeFile() const
{
    return QStringLiteral("colorpicker.h");
}

QString ColorPickerPlugin::name() const
{
    return QStringLiteral("ColorPicker");
}

QString ColorPickerPlugin::group() const
{
    return QStringLiteral("Custom widgets");
}

QIcon ColorPickerPlugin::icon() const
{
    return QIcon();
}

QString ColorPickerPlugin::toolTip() const
{
    return QString();
}

QString ColorPickerPlugin::whatsThis() const
{
    return QString();
}

bool ColorPickerPlugin::isContainer() const
{
    return false;
}

QString ColorPickerPlugin::domXml() const
{
    return "<ui language=\"c++\">\n"
           " <widget class=\"ColorPicker\" name=\"colorPicker\">\n"
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