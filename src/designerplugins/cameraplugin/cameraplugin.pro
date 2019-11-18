CONFIG += plugin
TEMPLATE = lib
QT += widgets uiplugin multimedia multimediawidgets

TARGET = cameraplugin

HEADERS +=  camerawidget.h \
            cameraplugin.h

SOURCES +=  camerawidget.cpp \
            cameraplugin.cpp