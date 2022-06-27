#include "ParserUrlWithoutScheme.hpp"

namespace ParserUri
{
	size_t ParserUrlWithoutScheme::Parse(const std::string& str, size_t start)
	{
		ParserUrl::Parse(str, start + 2);
		return 1; //TODO: return enum
	}

}