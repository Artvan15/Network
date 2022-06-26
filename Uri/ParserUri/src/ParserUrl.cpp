#include "ParserUrl.hpp"

namespace ParserUri
{
	size_t ParserUrl::Parse(const std::string& str, size_t start)
	{
		auto scheme_end = parser_scheme_.Parse(str, start);
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
		//cut path part up to "?#" (start of query or fragment)
		if(auto query_fragment_start = str.find_first_of("?#", end_authority);
			query_fragment_start != std::string::npos)
		{
			end_path = parser_path_.Parse(str.substr(end_authority, query_fragment_start - end_authority),
				0);
		}
		else if (end_path != std::string::npos)
		{
			end_path = parser_path_.Parse(str, end_authority);
		}
		return end_path;
	}

	//TODO: think about return value 
}
