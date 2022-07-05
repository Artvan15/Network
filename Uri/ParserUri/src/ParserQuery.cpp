#include "ParserQuery.hpp"
#include "ReplaceHexWithChar.hpp"

namespace ParserUri
{
    ParserUri::ParserQuery::ParserQuery(std::string& query) noexcept
        : query_(query), query_regex_(R"([a-zA-Z0-9\-\._~!$&'()*+,;=:@?%/]*)")
	{}

    size_t ParserQuery::Parse(const std::string& str, size_t start)
    {

        auto end_query = str.find('#', start);
        std::string temp_query = str.substr(start, end_query - start);
        if(!std::regex_match(temp_query, query_regex_))
        {
            throw ParserQueryException("query isn't valid");
        }
        ReplaceHexWithChar::Replace(temp_query, ParserQueryException("invalid hex code in query"));

        query_ = std::move(temp_query);
        return end_query;
    }
}
