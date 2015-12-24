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
    frmsettings.cpp \
    frmabout.cpp \
    drawers/gcodedrawer.cpp \
    drawers/heightmapborderdrawer.cpp \
    drawers/heightmapgriddrawer.cpp \
    drawers/heightmapinterpolationdrawer.cpp \
    drawers/origindrawer.cpp \
    drawers/shaderdrawable.cpp \
    drawers/tooldrawer.cpp \
    parser/arcproperties.cpp \
    parser/gcodeparser.cpp \
    parser/gcodepreprocessorutils.cpp \
    parser/gcodeviewparse.cpp \
    parser/linesegment.cpp \
    parser/pointsegment.cpp \
    tables/gcodetablemodel.cpp \
    tables/heightmaptablemodel.cpp \
    widgets/colorpicker.cpp \
    widgets/combobox.cpp \
    widgets/groupbox.cpp \
    widgets/scrollarea.cpp \
    widgets/styledtoolbutton.cpp \
    widgets/widget.cpp \
    widgets/glwidget.cpp

HEADERS  += frmmain.h \
    frmsettings.h \
    frmabout.h \
    drawers/gcodedrawer.h \
    drawers/heightmapborderdrawer.h \
    drawers/heightmapgriddrawer.h \
    drawers/heightmapinterpolationdrawer.h \
    drawers/origindrawer.h \
    drawers/shaderdrawable.h \
    drawers/tooldrawer.h \
    parser/arcproperties.h \
    parser/gcodeparser.h \
    parser/gcodepreprocessorutils.h \
    parser/gcodeviewparse.h \
    parser/linesegment.h \
    parser/pointsegment.h \
    tables/gcodetablemodel.h \
    tables/heightmaptablemodel.h \
    utils/interpolation.h \
    utils/util.h \
    widgets/colorpicker.h \
    widgets/combobox.h \
    widgets/groupbox.h \
    widgets/scrollarea.h \
    widgets/styledtoolbutton.h \
    widgets/widget.h \
    widgets/glwidget.h

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
