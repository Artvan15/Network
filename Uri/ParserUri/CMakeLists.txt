cmake_minimum_required(VERSION 3.15)
set(This ParserUri)

set(Sources
	src/IParser.cpp
	src/ParserUrl.cpp
	src/ParserUrn.cpp
	src/ParserRelativeReference.cpp
	src/ParserUrlWithScheme.cpp
	src/ParserUrlWithoutScheme.cpp
	src/ParserFragment.cpp
	src/ParserHost.cpp
	src/ParserPath.cpp
	src/ParserPort.cpp
	src/ParserQuery.cpp
	src/ParserScheme.cpp
	src/ParserUserInfo.cpp
	src/ReplaceHexWithChar.cpp)

set(Headers
	include/IParser.hpp
	include/ParserUrl.hpp
	include/ParserUrn.hpp
	include/ParserRelativeReference.hpp
	include/ParserException.hpp
	include/ParserUrlWithoutScheme.hpp
	include/ParserUrlWithScheme.hpp
	include/ParserFragment.hpp
	include/ParserHost.hpp
	include/ParserPath.hpp
	include/ParserPort.hpp
	include/ParserQuery.hpp
	include/ParserScheme.hpp
	include/ParserUserInfo.hpp
	include/ReplaceHexWithChar.hpp)

add_library(${This} STATIC ${Sources} ${Headers})
target_compile_features(${This} PRIVATE cxx_std_17)

set_target_properties(${This} PROPERTIES
	FOLDER ParserUri)

target_include_directories(${This} PUBLIC include)
