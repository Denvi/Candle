find_package(Qt5 COMPONENTS Core Widgets Script REQUIRED)

file(GLOB SRC_FILES *.cpp ../../generated_cpp/com_trolltech_qt_gui/*.cpp)

add_library(qtscript_gui SHARED ${SRC_FILES})

target_include_directories(qtscript_gui PRIVATE include)

target_link_libraries(qtscript_gui PRIVATE Qt5::Core Qt5::Widgets Qt5::Script)

install(TARGETS qtscript_gui RUNTIME DESTINATION script)