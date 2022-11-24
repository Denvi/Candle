cmake_minimum_required(VERSION 3.20)

set(NAME custom)

project(qtscript_${NAME} LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Script REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Gui widgets REQUIRED)

include(../qtbindingsbase.cmake)

#include_directories(
#    ../../../designerplugins/customwidgetsplugin
#)

add_library(${PROJECT_NAME} SHARED
    ${HEADERS}
    ${SOURCES}
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    customwidgets
    Qt${QT_VERSION_MAJOR}::Script
    Qt${QT_VERSION_MAJOR}::Gui
    Qt${QT_VERSION_MAJOR}::Widgets
)

target_compile_definitions(${PROJECT_NAME} PRIVATE ${NAME}_LIBRARY)
