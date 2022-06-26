#include "ParserRelativeReference.hpp"

namespace ParserUri
{
	size_t ParseRelativeReference::Parse(const std::string& str, size_t start)
	{
		auto end_path = parser_path_.Parse(str, start);
		return end_path;
	}
}
