set(TEMPLATE app)

find_package(Qt5 COMPONENTS Core Widgets OpenGL SerialPort Script LinguistTools REQUIRED)

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
        -ts ${TS_FILES}
    VERBATIM
)

target_include_directories(candle PRIVATE . ../customwidgets)

target_compile_definitions(candle PRIVATE
        _USE_MATH_DEFINES
        QT_NO_DEBUG
)

target_link_libraries(candle PRIVATE customwidgets Qt5::Core Qt5::Widgets Qt5::OpenGL Qt5::SerialPort Qt5::Script)

set_target_properties(candle PROPERTIES WIN32_EXECUTABLE ON)

# Main executable
install(TARGETS candle RUNTIME DESTINATION .)

# Translations
install(FILES ${QM_FILES} DESTINATION translations)

# Candle plugins
install(DIRECTORY ${CMAKE_SOURCE_DIR}/src/candleplugins DESTINATION . FILES_MATCHING PATTERN *.* PATTERN *.pro EXCLUDE)

# Default settings
install(FILES ${CMAKE_SOURCE_DIR}/src/candle/settings.ini DESTINATION .)

# License
install(FILES ${CMAKE_SOURCE_DIR}/LICENSE DESTINATION .)

# Documentation
install(DIRECTORY ${CMAKE_SOURCE_DIR}/doc DESTINATION . FILES_MATCHING PATTERN *.png PATTERN *.html PATTERN *.ico)

# Shared libraries
if(WIN32)
        install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/$<CONFIG>/ DESTINATION . FILES_MATCHING PATTERN *.dll PATTERN qt.conf)
endif()