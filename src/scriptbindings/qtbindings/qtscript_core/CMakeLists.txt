find_package(Qt5 COMPONENTS Core Widgets Script Concurrent REQUIRED)

file(GLOB SRC_FILES *.cpp qtscriptconcurrent.h ../../generated_cpp/com_trolltech_qt_core/*.cpp)

add_library(qtscript_core SHARED ${SRC_FILES})

target_include_directories(qtscript_core PRIVATE include .)

target_link_libraries(qtscript_core PRIVATE Qt5::Core Qt5::Widgets Qt5::Script Qt5::Concurrent)

install(TARGETS qtscript_core
    RUNTIME DESTINATION ${SCRIPT_DESTINATION}
    LIBRARY DESTINATION ${SCRIPT_DESTINATION})