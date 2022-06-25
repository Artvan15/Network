#include "ParserUrl.hpp"

namespace ParserUri
{
	size_t ParserUrl::Parse(const std::string& str, size_t start)
	{
		auto scheme_end = parser_scheme_.Parse(str, 0);
		auto end_authority = parser_host_.Parse(str, scheme_end + 3);
		if (end_authority == std::string::npos)
		{
			return end_authority;
		}
		if (str[end_authority] == ':')
		{
			end_authority = parser_port_.Parse(str, end_authority + 1);
		}
		size_t end_path = end_authority;
		if (end_path != std::string::npos)
		{
			end_path = parser_path_.Parse(str, end_authority + 1);
		}
		return end_path;
	}

	//TODO: think about return value 
}
