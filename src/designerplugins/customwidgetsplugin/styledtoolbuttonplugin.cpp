#include "styledtoolbuttonplugin.h"
#include "styledtoolbutton.h"

StyledToolButtonPlugin::StyledToolButtonPlugin(QObject *parent): QObject(parent), m_initialized(false)
{

}

void StyledToolButtonPlugin::initialize(QDesignerFormEditorInterface *core)
{
    if (m_initialized) return;

    m_initialized = true;
}

bool StyledToolButtonPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *StyledToolButtonPlugin::createWidget(QWidget *parent)
{
    return new StyledToolButton(parent);
}

QString StyledToolButtonPlugin::includeFile() const
{
    return QStringLiteral("styledtoolbutton.h");
}

QString StyledToolButtonPlugin::name() const
{
    return QStringLiteral("StyledToolButton");
}

QString StyledToolButtonPlugin::group() const
{
    return QStringLiteral("Custom widgets");
}

QIcon StyledToolButtonPlugin::icon() const
{
    return QIcon();
}

QString StyledToolButtonPlugin::toolTip() const
{
    return QString();
}

QString StyledToolButtonPlugin::whatsThis() const
{
    return QString();
}

bool StyledToolButtonPlugin::isContainer() const
{
    return false;
}

QString StyledToolButtonPlugin::domXml() const
{
    return "<ui language=\"c++\">\n"
           " <widget class=\"StyledToolButton\" name=\"styledToolButton\">\n"
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