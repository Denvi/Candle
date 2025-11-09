find_package(Qt5 COMPONENTS Core Script PrintSupport REQUIRED)

file(GLOB SRC_FILES *.cpp ../../generated_cpp/com_trolltech_qt_printsupport/*.cpp)

add_library(qtscript_printsupport SHARED ${SRC_FILES})

target_include_directories(qtscript_printsupport PRIVATE include)

target_link_libraries(qtscript_printsupport PRIVATE Qt5::Core Qt5::Script Qt5::PrintSupport)

install(TARGETS qtscript_printsupport
    RUNTIME DESTINATION ${SCRIPT_DESTINATION}
    LIBRARY DESTINATION ${SCRIPT_DESTINATION})