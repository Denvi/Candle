CONFIG += plugin
TEMPLATE = lib
QT += widgets uiplugin multimedia multimediawidgets

TARGET = cameraplugin

HEADERS +=  overlay.h \
            camerawidget.h \
            cameraplugin.h

SOURCES +=  overlay.cpp \
            camerawidget.cpp \
            cameraplugin.cpp