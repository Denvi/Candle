find_package(Qt5 COMPONENTS Core Script Network REQUIRED)

file(GLOB SRC_FILES *.cpp ../../generated_cpp/com_trolltech_qt_network/*.cpp)

add_library(qtscript_network SHARED ${SRC_FILES})

target_include_directories(qtscript_network PRIVATE include)

target_link_libraries(qtscript_network PRIVATE Qt5::Core Qt5::Script Qt5::Network)

install(TARGETS qtscript_network RUNTIME DESTINATION script)