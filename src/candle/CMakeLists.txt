set(TEMPLATE app)

find_package(Qt5 COMPONENTS Core Widgets OpenGL SerialPort Script LinguistTools REQUIRED)

file(GLOB_RECURSE SRC_FILES *.cpp)
file(GLOB TS_FILES translations/*.ts)

qt5_add_resources(RSC_FILES
        shaders.qrc
        images.qrc
        fonts.qrc
)

qt5_add_translation(QM_FILES ${TS_FILES})

add_executable(candle ${SRC_FILES} ${RSC_FILES} ${QM_FILES} icon.rc)

target_include_directories(candle PRIVATE . ../customwidgets)

target_compile_definitions(candle PRIVATE
        _USE_MATH_DEFINES
        QT_NO_DEBUG
        sNan=65536
)

target_link_libraries(candle PRIVATE customwidgets Qt5::Core Qt5::Widgets Qt5::OpenGL Qt5::SerialPort Qt5::Script)

set_target_properties(candle PROPERTIES WIN32_EXECUTABLE ON)

install(TARGETS candle RUNTIME DESTINATION .)
install(FILES ${QM_FILES} DESTINATION translations)
install(DIRECTORY ${CMAKE_SOURCE_DIR}/src/candleplugins DESTINATION . FILES_MATCHING PATTERN *.* PATTERN *.pro EXCLUDE)
install(FILES ${CMAKE_SOURCE_DIR}/src/candle/settings.ini DESTINATION .)
install(FILES ${CMAKE_SOURCE_DIR}/LICENSE DESTINATION .)

if(WIN32)
        install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/$<CONFIG>/ DESTINATION . FILES_MATCHING PATTERN *.dll PATTERN qt.conf)
endif()