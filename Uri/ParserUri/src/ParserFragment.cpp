#include "ParserFragment.hpp"
#include "ReplaceHexWithChar.hpp"

namespace ParserUri
{
    ParserUri::ParserFragment::ParserFragment(std::string& fragment) noexcept
        : fragment_(fragment), fragment_regex_(R"([a-zA-Z0-9\-\._~!$&'()*+,;=:@?%/]*)")
    {}

    size_t ParserFragment::Parse(const std::string& str, size_t start)
    {
        std::string temp_fragment = str.substr(start);
        if(!std::regex_match(temp_fragment, fragment_regex_))
        {
            throw ParserFragmentException("fragment isn't valid");
        }
        ReplaceHexWithChar::Replace(temp_fragment, ParserFragmentException("invalid hex code in fragment"));
        fragment_ = std::move(temp_fragment);

        return 1;
        //TODO: should mark the end of the fragment
    }
}
