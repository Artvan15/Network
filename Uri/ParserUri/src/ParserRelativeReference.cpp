#include "ParserRelativeReference.hpp"

namespace ParserUri
{
	size_t ParseRelativeReference::Parse(const std::string& str, size_t start)
	{
		//TODO: duplicate code from ParserUrl, need refactoring
		auto query_fragment_start = str.find_first_of("?#", start);
		parser_path_.Parse(str.substr(start, query_fragment_start - start), 0);

		if(query_fragment_start == std::string::npos)
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
}
