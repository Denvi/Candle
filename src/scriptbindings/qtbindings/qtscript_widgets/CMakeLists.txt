find_package(Qt5 COMPONENTS Core Widgets Script REQUIRED)

file(GLOB SRC_FILES *.cpp ../../generated_cpp/com_trolltech_qt_widgets/*.cpp)

add_library(qtscript_widgets SHARED ${SRC_FILES})

target_include_directories(qtscript_widgets PRIVATE include)

target_link_libraries(qtscript_widgets PRIVATE Qt5::Core Qt5::Widgets Qt5::Script)

install(TARGETS qtscript_widgets
    RUNTIME DESTINATION script
    LIBRARY DESTINATION script)