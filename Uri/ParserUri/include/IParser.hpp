#pragma once
#include <string>
#include "ParserException.hpp"

namespace ParserUri
{
	struct IParser
	{
		virtual ~IParser() = default;
		virtual size_t Parse(const std::string& str, size_t start) = 0;
	};
}
