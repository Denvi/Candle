find_package(Qt5 COMPONENTS Core Widgets Script UiTools REQUIRED)

file(GLOB SRC_FILES *.cpp ../../generated_cpp/com_trolltech_qt_uitools/*.cpp)

add_library(qtscript_uitools SHARED ${SRC_FILES})

target_include_directories(qtscript_uitools PRIVATE include)

target_link_libraries(qtscript_uitools PRIVATE Qt5::Core Qt5::Widgets Qt5::Script Qt::UiTools)

install(TARGETS qtscript_uitools
    RUNTIME DESTINATION script
    LIBRARY DESTINATION script)