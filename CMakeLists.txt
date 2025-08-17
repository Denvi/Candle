cmake_minimum_required(VERSION 3.10)

project(Candle)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

add_subdirectory(src/customwidgets)
add_subdirectory(src/candle)
add_subdirectory(src/designerplugins)
add_subdirectory(src/scriptbindings/qtbindings)