#include "cameraplugin.h"
#include "camerawidget.h"

CameraPlugin::CameraPlugin(QObject *parent): QObject(parent), m_initialized(false)
{

}

void CameraPlugin::initialize(QDesignerFormEditorInterface *core)
{
    if (m_initialized) return;

    m_initialized = true;
}

bool CameraPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *CameraPlugin::createWidget(QWidget *parent)
{
    return new CameraWidget(parent);
}

QString CameraPlugin::includeFile() const
{
    return QStringLiteral("camerawidget.h");
}

QString CameraPlugin::name() const
{
    return QStringLiteral("CameraWidget");
}

QString CameraPlugin::group() const
{
    return QStringLiteral("Custom widgets");
}

QIcon CameraPlugin::icon() const
{
    return QIcon();
}

QString CameraPlugin::toolTip() const
{
    return QString();
}

QString CameraPlugin::whatsThis() const
{
    return QString();
}

bool CameraPlugin::isContainer() const
{
    return false;
}

QString CameraPlugin::domXml() const
{
    return "<ui language=\"c++\">\n"
           " <widget class=\"CameraWidget\" name=\"cameraWidget\">\n"
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