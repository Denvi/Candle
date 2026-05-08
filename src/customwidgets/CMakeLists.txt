find_package(Qt5 COMPONENTS Core Widgets REQUIRED)

file(GLOB SRC_FILES *.cpp)

add_library(customwidgets SHARED ${SRC_FILES})

target_compile_definitions(customwidgets PRIVATE CUSTOMWIDGETS_EXPORT)

target_include_directories(customwidgets PRIVATE .)

target_link_libraries(customwidgets PRIVATE Qt5::Core Qt5::Widgets)

if(APPLE)
    install(TARGETS customwidgets LIBRARY DESTINATION Candle.app/Contents/Frameworks)
elseif(CANDLE_USE_STANDARD_PATHS)
    install(TARGETS customwidgets LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}/candle)
else()
    install(TARGETS customwidgets RUNTIME DESTINATION .)
endif()