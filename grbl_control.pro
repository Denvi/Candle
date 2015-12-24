#-------------------------------------------------
#
# Project created by QtCreator 2014-05-23T17:51:21
#
#-------------------------------------------------

QT       = core gui opengl serialport

win32: {
    QT += winextras
    DEFINES += WINDOWS
    LIBS += -L"C:\\WinDDK\\7600.16385.1\\lib\\win7\\i386" -L"C:\\Program Files (x86)\\Microsoft SDKs\\Windows\\v7.1A\\Lib" -lopengl32
    LIBS += -L"C:\\Program Files\\Microsoft SDKs\\Windows\\v7.1\\Lib" -lopengl32
}

unix: {
    DEFINES += UNIX #GL_GLEXT_PROTOTYPES
    QMAKE_LFLAGS += "-Wl,-rpath,\'\$$ORIGIN/libs\'"
}

contains(QT_CONFIG, opengles.) {
    warning("GL ES detected. VAO will be disabled.")
    DEFINES += GLES
    INSTALLS += target
    target.path = /home/pi
#    QMAKE_CXXFLAGS += -mno-unaligned-access
#    QMAKE_LFLAGS += -mno-unaligned-access
}

#DEFINES += sNan=\"NAN\"
DEFINES += sNan=\"65536\"

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

VERSION = 0.8.1

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
    tooldrawer.cpp \
    tablewidget.cpp \
    gcodetablemodel.cpp \
    frmsettings.cpp \
    styledtoolbutton.cpp \
    frmabout.cpp \
    combobox.cpp \
    heightmapborderdrawer.cpp \
    heightmapgriddrawer.cpp \
    heightmaptablemodel.cpp \
    heightmapinterpolationdrawer.cpp \
    scrollarea.cpp \
    widget.cpp \
    groupbox.cpp \
    shaderdrawable.cpp \
    origindrawer.cpp \
    colorpicker.cpp

HEADERS  += frmmain.h \
    glwidget.h \
    pointsegment.h \
    gcodepreprocessorutils.h \
    gcodeparser.h \
    arcproperties.h \
    linesegment.h \
    gcodeviewparse.h \
    gcodedrawer.h \
    tooldrawer.h \
    tablewidget.h \
    gcodetablemodel.h \
    frmsettings.h \
    styledtoolbutton.h \
    frmabout.h \
    combobox.h \
    heightmapborderdrawer.h \
    heightmapgriddrawer.h \
    heightmaptablemodel.h \
    heightmapinterpolationdrawer.h \
    util.h \
    interpolation.h \
    scrollarea.h \
    widget.h \
    groupbox.h \
    shaderdrawable.h \
    origindrawer.h \
    colorpicker.h

FORMS    += frmmain.ui \
    frmsettings.ui \
    frmabout.ui

DEFINES += _USE_MATH_DEFINES

RESOURCES += \
    shaders.qrc \
    images.qrc

CONFIG += c++11

RC_ICONS += images/grblControl2.ico

TRANSLATIONS += translations/grblControl_ru.ts translations/grblControl_es.ts translations/grblControl_fr.ts

win32: {
    QMAKE_CXXFLAGS_DEBUG += -g3 -pg
    QMAKE_LFLAGS_DEBUG += -pg -lgmon
}
