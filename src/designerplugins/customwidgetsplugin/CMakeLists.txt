find_package(Qt5 COMPONENTS Core Widgets UiPlugin REQUIRED)

file(GLOB SRC_FILES *.cpp)

add_library(customwidgetsplugin SHARED ${SRC_FILES})

target_include_directories(customwidgetsplugin PRIVATE ../../customwidgets)

target_link_libraries(customwidgetsplugin PRIVATE customwidgets Qt5::Core Qt5::Widgets Qt5::UiPlugin)

install(TARGETS customwidgetsplugin RUNTIME DESTINATION designerplugins)