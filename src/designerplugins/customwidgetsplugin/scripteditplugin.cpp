#include "scripteditplugin.h"
#include "scriptedit.h"

ScriptEditPlugin::ScriptEditPlugin(QObject *parent): QObject(parent), m_initialized(false)
{

}

void ScriptEditPlugin::initialize(QDesignerFormEditorInterface *core)
{
    if (m_initialized) return;

    m_initialized = true;
}

bool ScriptEditPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *ScriptEditPlugin::createWidget(QWidget *parent)
{
    return new ScriptEdit(parent);
}

QString ScriptEditPlugin::includeFile() const
{
    return QStringLiteral("scriptedit.h");
}

QString ScriptEditPlugin::name() const
{
    return QStringLiteral("ScriptEdit");
}

QString ScriptEditPlugin::group() const
{
    return QStringLiteral("Custom widgets");
}

QIcon ScriptEditPlugin::icon() const
{
    return QIcon();
}

QString ScriptEditPlugin::toolTip() const
{
    return QString();
}

QString ScriptEditPlugin::whatsThis() const
{
    return QString();
}

bool ScriptEditPlugin::isContainer() const
{
    return false;
}

QString ScriptEditPlugin::domXml() const
{
    return "<ui language=\"c++\">\n"
           " <widget class=\"ScriptEdit\" name=\"scriptEdit\">\n"
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