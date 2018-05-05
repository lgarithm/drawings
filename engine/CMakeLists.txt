cmake_minimum_required(VERSION 3.9)
project(rey)

set(CMAKE_CXX_STANDARD 17)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

include_directories(${CMAKE_SOURCE_DIR}/src)

file(GLOB test_srcs src/rey/**/*_test.cpp)
file(GLOB all_srcs src/rey/**/*.cpp)
list(REMOVE_ITEM all_srcs ${test_srcs}) 

add_library(rey ${all_srcs})
# target_link_libraries(rey stdc++fs)
target_link_libraries(rey pthread)

foreach(src ${test_srcs})
    get_filename_component(base_name ${src} NAME)
    string(REPLACE "." "_" bin_name ${base_name})
    add_executable(${bin_name} ${src})
    target_link_libraries(${bin_name} rey)
endforeach()


file(GLOB apps src/apps/*)
foreach(app_dir ${apps})
    get_filename_component(app ${app_dir} NAME)
    file(GLOB srcs ${app_dir}/*.cpp)
    set(bin_name ${app}_main)
    add_executable(${bin_name} ${srcs})
    target_link_libraries(${bin_name} rey)
endforeach()
