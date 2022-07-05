#include "ParserUrn.hpp"

namespace ParserUri
{
	size_t ParserUrn::Parse(const std::string& str, size_t start)
	{
		auto scheme_end = parser_scheme_.Parse(str, start);

		auto query_fragment_start = str.find_first_of("?#", scheme_end + 1);
		parser_path_.Parse(str.substr(scheme_end + 1, query_fragment_start - scheme_end - 1), 0);

		if (query_fragment_start == std::string::npos)
		{
			return 1;
		}

		//parse possible query
		if (str[query_fragment_start] == '?')
		{
			auto end_query = parser_query_.Parse(str, query_fragment_start + 1);
			if (end_query == std::string::npos)
			{
				return 1;
			}
			//in this case 'end_path' is end of query
			query_fragment_start = end_query;
		}
		parser_fragment_.Parse(str, query_fragment_start + 1);
		return query_fragment_start;
	}

	//TODO: return value 
}
