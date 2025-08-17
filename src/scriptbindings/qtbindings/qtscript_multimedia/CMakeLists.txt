find_package(Qt5 COMPONENTS Core Widgets Script Multimedia REQUIRED)

file(GLOB SRC_FILES *.cpp ../../generated_cpp/com_trolltech_qt_multimedia/*.cpp)

add_library(qtscript_multimedia SHARED ${SRC_FILES})

target_include_directories(qtscript_multimedia PRIVATE include)

target_link_libraries(qtscript_multimedia PRIVATE Qt5::Core Qt5::Widgets Qt5::Script Qt5::Multimedia)

install(TARGETS qtscript_multimedia RUNTIME DESTINATION script)