find_package(Qt5 COMPONENTS Core Widgets UiPlugin Multimedia MultimediaWidgets REQUIRED)

file(GLOB SRC_FILES *.cpp)

add_library(cameraplugin SHARED ${SRC_FILES})

target_link_libraries(cameraplugin PRIVATE Qt5::Core Qt5::Widgets Qt5::UiPlugin Qt5::Multimedia Qt5::MultimediaWidgets)

install(TARGETS cameraplugin RUNTIME DESTINATION designerplugins)

if(WIN32)
    install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/$<CONFIG>/ DESTINATION . FILES_MATCHING PATTERN *.dll)
endif()