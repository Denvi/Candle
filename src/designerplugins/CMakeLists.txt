if(APPLE)
    set(DESIGNER_DESTINATION "candle.app/Contents/MacOS/designerplugins")
else()
    set(DESIGNER_DESTINATION "designerplugins")
endif()

add_subdirectory(cameraplugin)
add_subdirectory(customwidgetsplugin)