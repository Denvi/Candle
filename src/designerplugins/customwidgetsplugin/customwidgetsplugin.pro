CONFIG += plugin
TEMPLATE = lib
QT += widgets uiplugin multimedia multimediawidgets

TARGET = customwidgets

DEFINES += CUSTOMWIDGETS_EXPORT

HEADERS +=  colorpicker.h \
            slider.h \
            colorpickerplugin.h \
            sliderplugin.h \
            sliderbox.h \
            sliderboxplugin.h \
            styledtoolbutton.h \
            styledtoolbuttonplugin.h \
            customwidgetsplugin.h

SOURCES +=  colorpicker.cpp \
            slider.cpp \
            colorpickerplugin.cpp \
            sliderplugin.cpp \
            sliderbox.cpp \
            sliderboxplugin.cpp \
            styledtoolbutton.cpp \
            styledtoolbuttonplugin.cpp \
            customwidgetsplugin.cpp

FORMS +=    sliderbox.ui