#include "ParserUrlWithScheme.hpp"

namespace ParserUri
{
	size_t ParserUrlWithScheme::Parse(const std::string& str, size_t start)
	{
		auto scheme_end = parser_scheme_.Parse(str, start);
		ParserUrl::Parse(str, scheme_end + 3);
		return 1; //TODO: return enum
	}

}