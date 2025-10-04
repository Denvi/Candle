find_package(Qt5 COMPONENTS Core Widgets Script OpenGL REQUIRED)

file(GLOB SRC_FILES *.cpp ../../generated_cpp/com_trolltech_qt_opengl/*.cpp)

add_library(qtscript_opengl SHARED ${SRC_FILES})

target_include_directories(qtscript_opengl PRIVATE include)

target_link_libraries(qtscript_opengl PRIVATE Qt5::Core Qt5::Widgets Qt5::Script Qt5::OpenGL)

install(TARGETS qtscript_opengl
    RUNTIME DESTINATION script
    LIBRARY DESTINATION script)