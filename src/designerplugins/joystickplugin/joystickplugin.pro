CONFIG += plugin
TEMPLATE = lib
QT += widgets uiplugin

TARGET = joystickplugin

SUBDIRS = SFML

HEADERS +=  \
            joystickwidget.h \
            joystickplugin.h

SOURCES +=  \
            joystickwidget.cpp \
            joystickplugin.cpp

INCLUDEPATH += SFML/include

LIBS += -L"$$PWD\build\SFML-2.6.1-Release\lib"
LIBS += -l"sfml-graphics" -l"sfml-system" -l"sfml-window"
