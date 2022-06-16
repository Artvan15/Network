cmake_minimum_required(VERSION 3.15)

set(This Uri)

set(Headers
    include/Uri/Uri.hpp)

set(Sources
    src/Uri.cpp)

#Adds a library target called <name> to the build from the
#source files listed. <name> must be globally unique.
#<name>.lib
add_library(${This} STATIC ${Sources} ${Headers})

#add project to the folder "Libraries"
set_target_properties(${This} PROPERTIES
    FOLDER Libraries)

#set include path
target_include_directories(${This} PUBLIC include)

add_subdirectory(test)