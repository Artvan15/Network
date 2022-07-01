#include "ParserQuery.hpp"

namespace ParserUri
{
    size_t ParserQuery::Parse(const std::string& str, size_t start)
    {
        auto end_query = str.find('#', start);
        query_ = str.substr(start, end_query - start);
        return end_query;
    }
}
