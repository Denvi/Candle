find_package(Qt5 COMPONENTS Core Widgets REQUIRED)

file(GLOB SRC_FILES *.cpp)

add_library(customwidgets SHARED ${SRC_FILES})

target_compile_definitions(customwidgets PRIVATE CUSTOMWIDGETS_EXPORT)

target_include_directories(customwidgets PRIVATE .)

target_link_libraries(customwidgets PRIVATE Qt5::Core Qt5::Widgets)

install(TARGETS customwidgets RUNTIME DESTINATION .)