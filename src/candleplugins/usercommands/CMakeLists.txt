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

project(usercommands LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY}/plugins/${PROJECT_NAME})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY})

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core REQUIRED)

file(GLOB_RECURSE HEADERS *.h)
file(GLOB_RECURSE QRC_FILES *.qrc)
file(GLOB_RECURSE SOURCES *.cpp)
file(GLOB_RECURSE TS_FILES *.ts)
file(GLOB_RECURSE UIS *.ui)

add_library(${PROJECT_NAME} SHARED
    ${APP_ICON_RESOURCE_WINDOWS}
    ${HEADERS}
    ${QRC_FILES}
    ${RESOURCES}
    ${SOURCES}
    ${TS_FILES}
    ${UIS}
)

COPY(${CMAKE_CURRENT_SOURCE_DIR} ${OUTPUT_DIRECTORY})

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
)

target_compile_definitions(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}_LIBRARY)
