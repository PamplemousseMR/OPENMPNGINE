CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

#------------ project ------------
PROJECT("OPENMPNGINE")

#------------ variables ------------
SET(openmpngine_src_dir "src")
SET(openmpngine_header_dir "include")

FUNCTION(openmpngineTest)
    SET(openmpngine_oneValueArgs NAME)
    CMAKE_PARSE_ARGUMENTS(VAR "" ${openmpngine_oneValueArgs} "" ${ARGN})

    #------ find files ------
    FILE(GLOB_RECURSE openmpngine_src_files ${openmpngine_src_dir}/*)
    FILE(GLOB_RECURSE openmpngine_header_files ${openmpngine_header_dir}/*)

    #------ create project ------
    GET_FILENAME_COMPONENT(openmpngine_current_name ${CMAKE_CURRENT_SOURCE_DIR} NAME)
    SET(openmpngine_current_name ${openmpngine_current_name} PARENT_SCOPE)
    SET(${VAR_NAME} ${openmpngine_current_name} PARENT_SCOPE)

    ADD_EXECUTABLE(${openmpngine_current_name} ${openmpngine_src_files} ${openmpngine_header_files})
    TARGET_INCLUDE_DIRECTORIES(${openmpngine_current_name} PRIVATE ${openmpngine_header_dir})

    #------ find OpenMP ------
    FIND_PACKAGE("OpenMP")

    IF(NOT ${OPENMP_FOUND})
        MESSAGE(FATAL_ERROR "Can't find OpenMP")
    ENDIF()

    TARGET_COMPILE_OPTIONS(${openmpngine_current_name} PRIVATE ${OpenMP_CXX_FLAGS})
ENDFUNCTION()

#------------ cmake variables ------------
SET(CMAKE_CXX_STANDARD 14)

#------------ create project ------------

#------ find sub directories ------
SET(openmpngine_project_dir "")

FILE(GLOB openmpngine_glob_dir ./*)
FOREACH(openmpngine_dir ${openmpngine_glob_dir})
    IF((IS_DIRECTORY ${openmpngine_dir}) AND (NOT ${openmpngine_dir} MATCHES ".*git"))
        LIST(APPEND openmpngine_project_dir ${openmpngine_dir})
    ENDIF()
ENDFOREACH()

#------ generate project for each sub directories ------
FOREACH(openmpngine_dir ${openmpngine_project_dir})
    MESSAGE(INFO " generate project : " ${openmpngine_dir})
    ADD_SUBDIRECTORY(${openmpngine_dir})
ENDFOREACH()
