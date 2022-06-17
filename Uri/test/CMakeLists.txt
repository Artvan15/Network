cmake_minimum_required(VERSION 3.15)
set(This UriTests)

set(Sources
    src/UriTests.cpp
	src/UriState.cpp)
	
set(Headers
	include/UriState.hpp)

#Enabling this option will make gtest link the runtimes dynamically too,
#and match the project in which it is included.
#set(gtest_force_shared_crt on)

#build as exe and locate project into folder "Tests"
add_executable(${This} ${Sources} ${Headers})
set_target_properties(${This} PROPERTIES
    FOLDER Tests)

#add library through the project name (add_library())
#path will be added to solution
#path to includes that lib needs will be added too
target_link_libraries(${This} PUBLIC
    gtest_main
    Uri)
	
target_include_directories(${This} PUBLIC include)

#Adds a test to the project to be run by ctest(1)
#Adds a test called <name>. The test name can contain arbitrary
#charecters
#if <command> specifies an executable target (created by
#add executable()) it will automatically be replaced by
#the location of the executable created at build time
add_test(
    NAME ${This}
    COMMAND ${This}
)

