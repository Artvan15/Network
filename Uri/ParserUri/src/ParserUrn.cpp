#include "ParserUrn.hpp"

namespace ParserUri
{
	size_t ParserUrn::Parse(const std::string& str, size_t start)
	{
		auto scheme_end = parser_scheme_.Parse(str, start);
		auto path_end = parser_path_.Parse(str, scheme_end + 1);
		return path_end;
	}

	//TODO: return value 
}
