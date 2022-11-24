cmake_minimum_required(VERSION 3.20)

set(NAME sql)

project(qtscript_${NAME} LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Script REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Sql REQUIRED)

include(../qtbindingsbase.cmake)

add_library(${PROJECT_NAME} SHARED
    ${HEADERS}
    ${SOURCES}
)

target_link_libraries(${PROJECT_NAME} PRIVATE 
    Qt${QT_VERSION_MAJOR}::Script
    Qt${QT_VERSION_MAJOR}::Sql
)

target_compile_definitions(${PROJECT_NAME} PRIVATE ${NAME}_LIBRARY)
