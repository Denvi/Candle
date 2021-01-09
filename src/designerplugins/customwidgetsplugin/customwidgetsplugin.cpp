#include "customwidgetsplugin.h"
#include "colorpickerplugin.h"
#include "sliderplugin.h"
#include "sliderboxplugin.h"
#include "styledtoolbuttonplugin.h"

CustomWidgetsPlugin::CustomWidgetsPlugin(QObject *parent): QObject(parent)
{
    widgets.append(new ColorPickerPlugin(this));
    widgets.append(new SliderPlugin(this));
    widgets.append(new SliderBoxPlugin(this));
    widgets.append(new StyledToolButtonPlugin(this));
}

QList<QDesignerCustomWidgetInterface*> CustomWidgetsPlugin::customWidgets() const
{
    return widgets;
}