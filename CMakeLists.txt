cmake_minimum_required(VERSION 3.10)

project(Candle VERSION 11.2)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

# Include GNUInstallDirs for standard path variables
include(GNUInstallDirs)

# Determine if we should use standard Linux paths (for distro packaging)
# Default is false (portable installation)
if(CMAKE_INSTALL_PREFIX MATCHES "^/usr")
    set(CANDLE_USE_STANDARD_PATHS TRUE)
else()
    set(CANDLE_USE_STANDARD_PATHS FALSE)
endif()

if(MSVC)
    add_compile_options(/MP)
endif()

add_subdirectory(src/customwidgets)
add_subdirectory(src/candle)
add_subdirectory(src/designerplugins)
add_subdirectory(src/scriptbindings/qtbindings)
