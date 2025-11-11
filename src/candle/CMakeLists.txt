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

find_package(Qt5 COMPONENTS Core Widgets OpenGL SerialPort Script ScriptTools LinguistTools Network WebSockets Help REQUIRED)

if(WIN32)
    find_package(Qt5 COMPONENTS WinExtras)
endif()

file(GLOB_RECURSE SRC_FILES *.cpp)
file(GLOB TS_FILES translations/*.ts)
file(GLOB UI_FILES *.ui)

qt5_add_resources(RSC_FILES
        shaders.qrc
        images.qrc
        fonts.qrc
        styles.qrc
)

qt5_add_translation(QM_FILES ${TS_FILES})

if(WIN32)
    add_executable(candle ${SRC_FILES} ${RSC_FILES} ${QM_FILES} icon.rc)
    target_link_libraries(candle PRIVATE Qt5::WinExtras)
    set_target_properties(candle PROPERTIES WIN32_EXECUTABLE ON)
elseif(APPLE)
    set(APP_ICON_MACOS "${CMAKE_SOURCE_DIR}/src/candle/images/candle.icns")
    set_source_files_properties(${APP_ICON_MACOS} PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")
    add_executable(candle ${SRC_FILES} ${RSC_FILES} ${QM_FILES} ${APP_ICON_MACOS} icon.rc)
    set_target_properties(candle PROPERTIES
        INSTALL_RPATH "@executable_path/../Frameworks"
        MACOSX_BUNDLE TRUE
        MACOSX_BUNDLE_BUNDLE_NAME "Candle"
        MACOSX_BUNDLE_INFO_PLIST "${CMAKE_SOURCE_DIR}/deploy/mac/Info.plist.in"
    )
elseif(UNIX)
    add_executable(candle ${SRC_FILES} ${RSC_FILES} ${QM_FILES} icon.rc)
    set_target_properties(candle PROPERTIES INSTALL_RPATH "$ORIGIN/lib")
endif()

target_include_directories(candle PRIVATE . ../customwidgets)

target_compile_definitions(candle PRIVATE
        _USE_MATH_DEFINES
        QT_NO_DEBUG
)

target_link_libraries(candle PRIVATE customwidgets Qt5::Core Qt5::Widgets Qt5::OpenGL Qt5::SerialPort Qt5::Script Qt5::ScriptTools Qt5::Network Qt5::WebSockets Qt5::Help)

# Main executable
if(APPLE)
    install(TARGETS candle BUNDLE DESTINATION .)
else()
    install(TARGETS candle RUNTIME DESTINATION .)
endif()

# Translations
if(APPLE)
    set(TRANSLATIONS_DESTINATION "Candle.app/Contents/MacOS/translations")
else()
    set(TRANSLATIONS_DESTINATION "translations")
endif()

install(FILES ${QM_FILES} DESTINATION ${TRANSLATIONS_DESTINATION})

# Base translations
get_target_property(QT5_QMAKE_EXECUTABLE Qt5::qmake IMPORTED_LOCATION)
execute_process(
    COMMAND "${QT5_QMAKE_EXECUTABLE}" -query QT_INSTALL_TRANSLATIONS
    OUTPUT_VARIABLE QT_TRANSLATIONS_DIR
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

set(QT_LANGUAGES ru es fr pt)

foreach(LANG ${QT_LANGUAGES})
    set(QT_TRANSLATION_FILE_BASE "${QT_TRANSLATIONS_DIR}/qtbase_${LANG}.qm")
    if(EXISTS "${QT_TRANSLATION_FILE_BASE}")
        install(
            FILES "${QT_TRANSLATION_FILE_BASE}"
            DESTINATION ${TRANSLATIONS_DESTINATION}
        )
    endif()
    set(QT_TRANSLATION_FILE_SCRIPT "${QT_TRANSLATIONS_DIR}/qtscript_${LANG}.qm")
    if(EXISTS "${QT_TRANSLATION_FILE_SCRIPT}")
        install(
            FILES "${QT_TRANSLATION_FILE_SCRIPT}"
            DESTINATION ${TRANSLATIONS_DESTINATION}
        )
    endif()    
    set(QT_TRANSLATION_FILE_HELP "${QT_TRANSLATIONS_DIR}/qt_help_${LANG}.qm")
    if(EXISTS "${QT_TRANSLATION_FILE_HELP}")
        install(
            FILES "${QT_TRANSLATION_FILE_HELP}"
            DESTINATION ${TRANSLATIONS_DESTINATION}
        )
    endif()    
endforeach()

if(APPLE)
    set(GENERAL_DESTINATION "Candle.app/Contents/MacOS")
else()
    set(GENERAL_DESTINATION ".")
endif()

# Manual targets
# Translations
add_custom_target(
    lupdate
    COMMAND $<TARGET_FILE:Qt${QT_VERSION}::lupdate>
        ${SRC_FILES} ${UI_FILES}
        -locations none
        -no-obsolete
        -ts ${TS_FILES}
    VERBATIM
)

# Docs
add_custom_target(
    docs
    COMMAND $<TARGET_FILE:Qt${QT_VERSION}::qhelpgenerator>
        ${CMAKE_SOURCE_DIR}/help/candle.qhcp
        -o ${CMAKE_SOURCE_DIR}/help/candle.qhc
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    VERBATIM
)

# Install
# Candle plugins
install(DIRECTORY ${CMAKE_SOURCE_DIR}/src/candleplugins
    DESTINATION ${GENERAL_DESTINATION}
    FILES_MATCHING
    PATTERN *.*
    PATTERN *.pro EXCLUDE
)

# License
install(FILES ${CMAKE_SOURCE_DIR}/LICENSE DESTINATION ${GENERAL_DESTINATION})

# Documentation
install(DIRECTORY ${CMAKE_SOURCE_DIR}/help DESTINATION ${GENERAL_DESTINATION} FILES_MATCHING PATTERN *.qch PATTERN *.qhc)
 
# Shared libraries
if(WIN32)
    install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/$<CONFIG>/ DESTINATION . FILES_MATCHING PATTERN *.dll PATTERN qt.conf)
endif()

# Plugins
if(APPLE)
    get_target_property(QT_QMAKE_EXECUTABLE Qt5::qmake IMPORTED_LOCATION)
    execute_process(
        COMMAND ${QT_QMAKE_EXECUTABLE} -query QT_INSTALL_PLUGINS
        OUTPUT_VARIABLE QT_PLUGINS_DIR
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )

    install(DIRECTORY ${QT_PLUGINS_DIR}/sqldrivers
        DESTINATION Candle.app/Contents/PlugIns
        FILES_MATCHING PATTERN "*.dylib"
    )

    install(DIRECTORY "${QT_PLUGINS_DIR}/mediaservice/"
        DESTINATION Candle.app/Contents/PlugIns/mediaservice
        FILES_MATCHING PATTERN "*.dylib"
    )

    find_library(SQLITE3_LIB sqlite3)
    if(SQLITE3_LIB)
        install(FILES ${SQLITE3_LIB} DESTINATION Candle.app/Contents/Frameworks)
    endif()
endif()