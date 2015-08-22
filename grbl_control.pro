#-------------------------------------------------
#
# Project created by QtCreator 2014-05-23T17:51:21
#
#-------------------------------------------------

QT       = core gui opengl serialport winextras

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

VERSION = 0.3

DEFINES += APP_VERSION=\\\"$$VERSION\\\"

TARGET = grbl_control
TEMPLATE = app

SOURCES += main.cpp\
        frmmain.cpp \
    glwidget.cpp \
    pointsegment.cpp \
    gcodepreprocessorutils.cpp \
    gcodeparser.cpp \
    arcproperties.cpp \
    linesegment.cpp \
    gcodeviewparse.cpp \
    gcodedrawer.cpp \
    gldrawable.cpp \
    tooldrawer.cpp \
    tablewidget.cpp \
    gcodetablemodel.cpp \
    frmsettings.cpp \
    styledtoolbutton.cpp \
    frmabout.cpp \
    combobox.cpp

HEADERS  += frmmain.h \
    glwidget.h \
    pointsegment.h \
    gcodepreprocessorutils.h \
    gcodeparser.h \
    arcproperties.h \
    linesegment.h \
    gcodeviewparse.h \
    gcodedrawer.h \
    gldrawable.h \
    tooldrawer.h \
    tablewidget.h \
    gcodetablemodel.h \
    frmsettings.h \
    styledtoolbutton.h \
    frmabout.h \
    combobox.h

FORMS    += frmmain.ui \
    frmsettings.ui \
    frmabout.ui

DEFINES += _USE_MATH_DEFINES

INCLUDEPATH += "C:\\WinDDK\\7600.16385.1\\inc\\crt\\gl" "C:\\Program Files (x86)\\Microsoft SDKs\\Windows\\v7.1A\\Include\\gl"
LIBS += -L"C:\\WinDDK\\7600.16385.1\\lib\\win7\\i386" -L"C:\\Program Files (x86)\\Microsoft SDKs\\Windows\\v7.1A\\Lib" -lopengl32 -lglu32

RESOURCES += \
    res.qrc

CONFIG += c++11

RC_ICONS += images/grblControl2.ico

TRANSLATIONS = translations/grblControl_ru.ts

QMAKE_CXXFLAGS_DEBUG += -g3 -pg
QMAKE_LFLAGS_DEBUG += -pg -lgmon
