#-------------------------------------------------
#
# Project created by QtCreator 2014-05-23T17:51:21
#
#-------------------------------------------------

QT       = core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

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
    gcodetablemodel.cpp

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
    gcodetablemodel.h

FORMS    += frmmain.ui

DEFINES += _USE_MATH_DEFINES

INCLUDEPATH += C:\\Qt\\Qt5.4.1\\Tools\\mingw491_32\\i686-w64-mingw32\\include\\GL

RESOURCES += \
    res.qrc
