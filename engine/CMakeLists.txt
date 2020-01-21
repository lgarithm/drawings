CMAKE_MINIMUM_REQUIRED(VERSION 3.9)
PROJECT(rey)

SET(CMAKE_CXX_STANDARD 17)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

IF(OPTIMIZE)
    ADD_DEFINITIONS(-ffast-math)
    ADD_DEFINITIONS(-ftree-vectorize)
    ADD_DEFINITIONS(-ftree-vectorizer-verbose=2)
ENDIF()

INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/include)
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/src)
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/3rdparty/include)

FILE(GLOB test_srcs src/rey/**/*_test.cpp)
FILE(GLOB all_srcs src/rey/**/*.cpp)
LIST(REMOVE_ITEM all_srcs ${test_srcs})

ADD_LIBRARY(rey ${all_srcs})
TARGET_LINK_LIBRARIES(rey pthread)
IF(APPLE)
    # noop
ELSE()
    TARGET_LINK_LIBRARIES(rey stdc++fs)
ENDIF()

FOREACH(src ${test_srcs})
    GET_FILENAME_COMPONENT(base_name ${src} NAME)
    STRING(REPLACE "." "_" bin_name ${base_name})
    ADD_EXECUTABLE(${bin_name} ${src})
    TARGET_LINK_LIBRARIES(${bin_name} rey)
ENDFOREACH()

FILE(GLOB apps src/apps/*)
FOREACH(app_dir ${apps})
    GET_FILENAME_COMPONENT(app ${app_dir} NAME)
    FILE(GLOB srcs ${app_dir}/*.cpp)
    SET(bin_name ${app}_main)
    ADD_EXECUTABLE(${bin_name} ${srcs})
    TARGET_LINK_LIBRARIES(${bin_name} rey)
ENDFOREACH()
