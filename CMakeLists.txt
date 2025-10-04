cmake_minimum_required(VERSION 3.10)

project(Candle VERSION 10.10)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

if(MSVC)
    add_compile_options(/MP)
endif()

add_subdirectory(src/customwidgets)
add_subdirectory(src/candle)
add_subdirectory(src/designerplugins)
add_subdirectory(src/scriptbindings/qtbindings)