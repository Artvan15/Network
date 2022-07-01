#include "ParserScheme.hpp"

namespace ParserUri
{
    ParserScheme::ParserScheme(std::string& scheme) noexcept
        : scheme_(scheme), scheme_regex_("[a-zA-Z]([a-zA-Z0-9+\\-\\.])*")
    {}

    size_t ParserScheme::Parse(const std::string& str, size_t start)
    {
        auto scheme_end = str.find(':', start);
        std::string temp_scheme = str.substr(start, scheme_end);
        if (!std::regex_match(temp_scheme, scheme_regex_))
        {
            throw ParserSchemeException("scheme isn't valid");
        }
        scheme_ = std::move(temp_scheme);
        return scheme_end;
    }
}