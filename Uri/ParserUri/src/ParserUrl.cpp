#include "ParserUrl.hpp"

#include <iostream>
#include <chrono>

namespace ParserUri
{
	//TODO: return enum instead of size_t
	size_t ParserUrl::Parse(const std::string& str, size_t start)
	{
		start = parser_user_info_.Parse(str, start);

		auto end_authority = parser_host_.Parse(str, start);

		//No port, path, query, fragment after host
		if (end_authority == std::string::npos)
		{
			return 1;
		}

		//parse possible port
		if (str[end_authority] == ':')
		{
			end_authority = parser_port_.Parse(str, end_authority + 1);
			if(end_authority == std::string::npos)
			{
				return 1;
			}
		}

		
		//parse possible path
		size_t end_path = end_authority;
		if(str.substr(end_authority, delimiter_.size()) == delimiter_)
		{
			auto query_fragment_start = str.find_first_of("?#", end_authority);
			parser_path_.Parse(str.substr(end_authority, query_fragment_start - end_authority), 0);
			if(query_fragment_start == std::string::npos)
			{
				return 1;
			}
			end_path = query_fragment_start;
		}

		//parse possible query
		if(str[end_path] == '?')
		{
			auto end_query = parser_query_.Parse(str, end_path + 1);
			if(end_query == std::string::npos)
			{
				return 1;
			}
			//in this case 'end_path' is end of query
			end_path = end_query;
		}
		parser_fragment_.Parse(str, end_path + 1);;
		return 1;

	}

	//TODO: think about return value 
}
