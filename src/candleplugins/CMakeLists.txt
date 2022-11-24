cmake_minimum_required(VERSION 3.20)

function(COPY_PLUGIN SOURCE_DIR OUTPUT_DIR)
    file(GLOB_RECURSE PLUGIN_FILES *.ui *.qm *.ts *js *png)
    foreach(FILE  ${PLUGIN_FILES})
        string(REPLACE ${SOURCE_DIR} "" OUTPUT_FILE ${FILE})
        set(OUTPUT_FILE ${OUTPUT_DIR}${OUTPUT_FILE})
        get_filename_component(OUTPUT_DIRECTORY2 ${OUTPUT_FILE} DIRECTORY)
        file(MAKE_DIRECTORY ${OUTPUT_DIRECTORY2})
        file(COPY_FILE ${FILE} ${OUTPUT_FILE} RESULT COPY_RESULT ONLY_IF_DIFFERENT)
    endforeach()
endfunction()

add_subdirectory(camera)
add_subdirectory(coordinatesystem)
add_subdirectory(emergencybutton)
add_subdirectory(usercommands)



