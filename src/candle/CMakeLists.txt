set(APP_NAME ${PROJECT_NAME})
set(APP_VERSION ${PROJECT_VERSION})

execute_process(
  COMMAND git log -1 --format=%h
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  OUTPUT_VARIABLE BUILD_NUMBER
  OUTPUT_STRIP_TRAILING_WHITESPACE
)

configure_file(versionconfig.h.in versionconfig.h)
include_directories(${CMAKE_CURRENT_BINARY_DIR})

find_package(Qt5 COMPONENTS Core Widgets OpenGL SerialPort Script LinguistTools Network WebSockets REQUIRED)

if(WIN32)
    find_package(WinExtras)
endif()

file(GLOB_RECURSE SRC_FILES *.cpp)
file(GLOB TS_FILES translations/*.ts)
file(GLOB UI_FILES *.ui)

qt5_add_resources(RSC_FILES
        shaders.qrc
        images.qrc
        fonts.qrc
)

qt5_add_translation(QM_FILES ${TS_FILES})

add_executable(candle ${SRC_FILES} ${RSC_FILES} ${QM_FILES} icon.rc)

add_custom_target(
    lupdate ALL
    COMMAND $<TARGET_FILE:Qt${QT_VERSION}::lupdate>
        ${SRC_FILES} ${UI_FILES}
        -locations none
        -no-obsolete
        -ts ${TS_FILES}
    VERBATIM
)

target_include_directories(candle PRIVATE . ../customwidgets)

target_compile_definitions(candle PRIVATE
        _USE_MATH_DEFINES
        QT_NO_DEBUG
)

target_link_libraries(candle PRIVATE customwidgets customwidgetsplugin Qt5::Core Qt5::Widgets Qt5::OpenGL Qt5::SerialPort Qt5::Script Qt5::Network Qt5::WebSockets)

if(WIN32)
    target_link_libraries(candle PRIVATE Qt5::WinExtras)
    target_compile_definition(candle PRIVATE WINDOWS)
endif()

set_target_properties(candle PROPERTIES WIN32_EXECUTABLE ON)

# Main executable
install(TARGETS candle RUNTIME DESTINATION .)

# Translations
install(FILES ${QM_FILES} DESTINATION translations)

# Base translations
get_target_property(QT5_QMAKE_EXECUTABLE Qt5::qmake IMPORTED_LOCATION)
execute_process(
    COMMAND "${QT5_QMAKE_EXECUTABLE}" -query QT_INSTALL_TRANSLATIONS
    OUTPUT_VARIABLE QT_TRANSLATIONS_DIR
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

set(QT_LANGUAGES ru es fr pt)

foreach(LANG ${QT_LANGUAGES})
    set(QT_TRANSLATION_FILE "${QT_TRANSLATIONS_DIR}/qtbase_${LANG}.qm")
    if(EXISTS "${QT_TRANSLATION_FILE}")
        install(
            FILES "${QT_TRANSLATION_FILE}"
            DESTINATION "translations"
        )
    endif()
endforeach()

# Candle plugins
install(DIRECTORY ${CMAKE_SOURCE_DIR}/src/candleplugins DESTINATION . FILES_MATCHING PATTERN *.* PATTERN *.pro EXCLUDE)

# License
install(FILES ${CMAKE_SOURCE_DIR}/LICENSE DESTINATION .)

# Documentation
install(DIRECTORY ${CMAKE_SOURCE_DIR}/doc DESTINATION . FILES_MATCHING PATTERN *.png PATTERN *.html PATTERN *.ico PATTERN *.js PATTERN *.gcode)

# Shared libraries
if(WIN32)
        install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/$<CONFIG>/ DESTINATION . FILES_MATCHING PATTERN *.dll PATTERN qt.conf)
endif()