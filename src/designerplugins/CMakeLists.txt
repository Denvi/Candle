if(APPLE)
    set(DESIGNER_DESTINATION "Candle.app/Contents/MacOS/designerplugins")
else()
    set(DESIGNER_DESTINATION "designerplugins")
endif()

add_subdirectory(cameraplugin)
add_subdirectory(customwidgetsplugin)