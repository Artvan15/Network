#include "ParserFragment.hpp"

namespace ParserUri
{
    size_t ParserFragment::Parse(const std::string& str, size_t start)
    {
        fragment_ = str.substr(start);
        return 1;
        //TODO: should mark the end of the fragment
    }
}
