find_package(Qt5 COMPONENTS Core Script Xml REQUIRED)

file(GLOB SRC_FILES *.cpp ../../generated_cpp/com_trolltech_qt_xml/*.cpp)

add_library(qtscript_xml SHARED ${SRC_FILES})

target_include_directories(qtscript_xml PRIVATE include)

target_link_libraries(qtscript_xml PRIVATE Qt5::Core Qt5::Script Qt5::Xml)

install(TARGETS qtscript_xml
    RUNTIME DESTINATION script
    LIBRARY DESTINATION script)