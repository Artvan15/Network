cmake_minimum_required(VERSION 3.15)

set(This Network)

#selects for all following targets a multi-threaded statically-linked runtime 
#library with or without debug information depending on the configuration.
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
project(${This} C CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

enable_testing()

#path to cmake project
add_subdirectory(googletest)

#set the folder name for targets
set_target_properties(gtest gtest_main PROPERTIES
    FOLDER Libreries)

#path to the cmake project
add_subdirectory(Uri)

#test commit2
