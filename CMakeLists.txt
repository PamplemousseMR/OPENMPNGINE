#=======================================
#                PROJECT
#=======================================

cmake_minimum_required(VERSION 3.0)
project("OPENMPNGINE")

#=======================================
#               LIBRARIES
#=======================================

FIND_PACKAGE("OpenMP" REQUIRED)

#=======================================
#                SAMPLES
#=======================================

function(add_sample)
    set(options "")
    set(singleValues "")
    set(multipleValues SOURCES)

    cmake_parse_arguments(SAMPLE "${options}" "${singleValues}" "${multipleValues}" ${ARGN})

    get_filename_component(openmpngine_current_name ${CMAKE_CURRENT_SOURCE_DIR} NAME)

    add_executable(${openmpngine_current_name} ${SAMPLE_SOURCES})
    set_target_properties(${openmpngine_current_name} PROPERTIES CXX_STANDARD 14)

    if(UNIX)
        target_link_libraries(${openmpngine_current_name} PRIVATE ${OpenMP_CXX_FLAGS})
    endif(UNIX)
    target_compile_options(${openmpngine_current_name} PRIVATE ${OpenMP_CXX_FLAGS})
endfunction()

add_subdirectory("For")
add_subdirectory("Parallel")
add_subdirectory("Section")
add_subdirectory("Single")
