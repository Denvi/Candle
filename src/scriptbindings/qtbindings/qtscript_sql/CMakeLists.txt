find_package(Qt5 COMPONENTS Core Script Sql REQUIRED)

file(GLOB SRC_FILES *.cpp ../../generated_cpp/com_trolltech_qt_sql/*.cpp)

add_library(qtscript_sql SHARED ${SRC_FILES})

target_include_directories(qtscript_sql PRIVATE include)

target_link_libraries(qtscript_sql PRIVATE Qt5::Core Qt5::Script Qt5::Sql)

install(TARGETS qtscript_sql RUNTIME DESTINATION script)