#pragma once
#include <stdexcept>

struct ParserException : public std::runtime_error
{
	explicit ParserException(const std::string& str)
		: runtime_error(str) {}
};

struct ParserPortException : public ParserException
{
	using ParserException::ParserException;
};
