#include "uiloader.h"
#include "styledtoolbutton.h"
#include "sliderbox.h"

UiLoader::UiLoader(QObject *parent): QUiLoader(parent)
{
}

QWidget *UiLoader::createWidget(const QString &className, QWidget *parent, const QString &name)
{
    // Custom widgets
    if (className == "StyledToolButton") {
        StyledToolButton *w = new StyledToolButton(parent);
        w->setObjectName(name);
        return w;
    } else if (className == "SliderBox") {
        SliderBox *w = new SliderBox(parent);
        w->setObjectName(name);
        return w;
    }

    return QUiLoader::createWidget(className, parent, name);
}