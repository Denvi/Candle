find_package(Qt5 COMPONENTS Core Widgets Script REQUIRED)

file(GLOB SRC_FILES *.cpp ../../generated_cpp/com_trolltech_qt_custom/*.cpp)

add_library(qtscript_custom SHARED ${SRC_FILES})

target_include_directories(qtscript_custom PRIVATE include ../../../customwidgets)

target_link_libraries(qtscript_custom PRIVATE customwidgets Qt5::Core Qt5::Widgets Qt5::Script)

install(TARGETS qtscript_custom
    RUNTIME DESTINATION ${SCRIPT_DESTINATION}
    LIBRARY DESTINATION ${SCRIPT_DESTINATION})