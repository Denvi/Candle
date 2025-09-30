find_package(Qt5 COMPONENTS Core Widgets REQUIRED)

file(GLOB SRC_FILES *.cpp)
include_directories(. )

add_library(customwidgets SHARED ${SRC_FILES})

target_compile_definitions(customwidgets PRIVATE CUSTOMWIDGETS_EXPORT)

target_link_libraries(customwidgets PRIVATE Qt5::Core Qt5::Widgets)

install(TARGETS customwidgets RUNTIME DESTINATION .)
