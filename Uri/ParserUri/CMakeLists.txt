cmake_minimum_required(VERSION 3.15)
set(This ParserUri)

set(Sources
	src/ParserUri.cpp
	src/ParserUrl.cpp
	src/ParserUrn.cpp
	src/ParserRelativeReference.cpp
	src/ParserUrlWithScheme.cpp
	src/ParserUrlWithoutScheme.cpp)

set(Headers
	include/ParserUri.hpp
	include/ParserUrl.hpp
	include/ParserUrn.hpp
	include/ParserRelativeReference.hpp
	include/ParserException.hpp
	include/ParserUrlWithoutScheme.hpp
	include/ParserUrlWithScheme.hpp)

add_library(${This} STATIC ${Sources} ${Headers})
target_compile_features(${This} PRIVATE cxx_std_17)

set_target_properties(${This} PROPERTIES
	FOLDER ParserUri)

target_include_directories(${This} PUBLIC include)
