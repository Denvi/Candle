#/*******************************************************************************
#* Author    :  Damir Bakiev                                                    *
#* Version   :  na                                                              *
#* Date      :  11 November 2021                                                *
#* Website   :  na                                                              *
#* Copyright :  Damir Bakiev 2016-2022                                          *
#* License:                                                                     *
#* Use, modification & distribution is subject to Boost Software License Ver 1. *
#* http://www.boost.org/LICENSE_1_0.txt                                         *
#*******************************************************************************/
cmake_minimum_required(VERSION 3.20)

project(customwidgets LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core REQUIRED)


find_package(Qt${QT_VERSION_MAJOR} COMPONENTS
    Core
    Gui
    Widgets
    UiPlugin
    Multimedia
    MultimediaWidgets
    REQUIRED
)

add_library(${PROJECT_NAME} SHARED
    colorpicker.cpp
    colorpicker.h
    colorpickerplugin.cpp
    colorpickerplugin.h
    customwidgetsplugin.cpp
    customwidgetsplugin.h
    slider.cpp
    slider.h
    sliderbox.cpp
    sliderbox.h
    sliderbox.ui
    sliderboxplugin.cpp
    sliderboxplugin.h
    sliderplugin.cpp
    sliderplugin.h
    styledtoolbutton.cpp
    styledtoolbutton.h
    styledtoolbuttonplugin.cpp
    styledtoolbuttonplugin.h
)


target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Gui
    Qt${QT_VERSION_MAJOR}::Multimedia
    Qt${QT_VERSION_MAJOR}::MultimediaWidgets
    Qt${QT_VERSION_MAJOR}::UiPlugin
    Qt${QT_VERSION_MAJOR}::Widgets
)

target_compile_definitions(${PROJECT_NAME} PRIVATE CUSTOMWIDGETS_EXPORT)

