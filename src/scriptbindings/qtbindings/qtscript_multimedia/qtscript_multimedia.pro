TARGET = qtscript_multimedia
include(../qtbindingsbase.pri)
SOURCES += plugin.cpp
HEADERS += plugin.h
QT += core gui widgets multimedia
INCLUDEPATH += ./include/
include($$GENERATEDCPP/com_trolltech_qt_multimedia/com_trolltech_qt_multimedia.pri)
