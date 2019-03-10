cmake_minimum_required(VERSION 3.13)
project(Candle)

# set(CMAKE_VERBOSE_MAKEFILE ON)

# instruct CMake to run moc automatically when needed
set(CMAKE_AUTOMOC ON)

# create code from a list of Qt designer ui files
set(CMAKE_AUTOUIC ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -W -msse3")

if(APPLE)
    add_compile_definitions(Q_OS_MAC)
endif()
add_compile_definitions(APP_VERSION="1.1.9")
add_compile_definitions(QT_NO_DEBUG)

find_package(Qt5 COMPONENTS Core Widgets OpenGL SerialPort REQUIRED)

include_directories(${PROJECT_SOURCE_DIR})

file(GLOB SRC_FILES ${PROJECT_SOURCE_DIR}/*.cpp
                    ${PROJECT_SOURCE_DIR}/drawers/*.cpp
                    ${PROJECT_SOURCE_DIR}/parser/*.cpp
                    ${PROJECT_SOURCE_DIR}/widgets/*.cpp
                    ${PROJECT_SOURCE_DIR}/tables/*.cpp
                    )

qt5_add_resources(SHADER_RSC 
    ${PROJECT_SOURCE_DIR}/shaders.qrc
    ${PROJECT_SOURCE_DIR}/images.qrc
    ${PROJECT_SOURCE_DIR}/fonts.qrc
    )

if(APPLE)
    add_executable(Candle MACOSX_BUNDLE ${SRC_FILES} ${SHADER_RSC})
    set_target_properties(Candle PROPERTIES MACOSX_BUNDLE_INFO_PLIST ${PROJECT_SOURCE_DIR}/Info.plist)
else()
    add_executable(Candle ${SRC_FILES} ${SHADER_RSC})
endif()

target_link_libraries(Candle
    Qt5::Core
    Qt5::Widgets
    Qt5::OpenGL
    Qt5::Gui
    Qt5::SerialPort
    )
