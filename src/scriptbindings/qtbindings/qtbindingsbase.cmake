if(CMAKE_BUILD_TYPE MATCHES Debug)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY}/script_debug)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY}/script_debug)
else()
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY}/script)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY}/script)
endif()

if(WIN32)
    add_compile_options(/MP /GS /Zi)
    add_link_options(/DEBUG /OPT:REF /OPT:ICF)
endif()

find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Script REQUIRED)

include_directories(
    ../../generated_cpp/com_trolltech_qt_${NAME}
    include
)

file(GLOB_RECURSE HEADERS *.h ../../generated_cpp/com_trolltech_qt_${NAME}/*.h)
file(GLOB_RECURSE SOURCES *.cpp ../../generated_cpp/com_trolltech_qt_${NAME}/*.cpp)
