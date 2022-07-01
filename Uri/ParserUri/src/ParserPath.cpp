#include "ParserPath.hpp"

namespace ParserUri
{
    size_t ParserPath::Parse(const std::string& str, size_t start)
    {
        //Corner case, when path only consists of delimiter
        if (str.substr(start).size() == delimiter_.size())
        {
            path_.emplace_back("");
            return start + delimiter_.size();
        }

        while (true)
        {
            auto end_path_part = str.find(delimiter_, start);
            path_.emplace_back(str, start, end_path_part - start);
            if (end_path_part == std::string::npos)
            {
                break;
            }
            start = end_path_part + delimiter_.size();
        }
        return 1; //TODO: in future will return end of path segment
    }
}
