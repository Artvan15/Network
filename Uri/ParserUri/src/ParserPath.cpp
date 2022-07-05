#include "ParserPath.hpp"
#include "ParserException.hpp"
#include "ReplaceHexWithChar.hpp"

namespace ParserUri
{
    ParserUri::ParserPath::ParserPath(std::vector<std::string>& path, const std::string& delimiter) noexcept
        : path_(path), delimiter_(delimiter), path_regex_(R"([a-zA-Z0-9\-\._~!$&'()*+,;=:@%/]*)")
	{}


    size_t ParserPath::Parse(const std::string& str, size_t start)
    {
        if(!std::regex_match(str, path_regex_))
        {
            throw ParserPathException("path has invalid characters");
        }

        //Corner case, when path only consists of delimiter
        if (str.substr(start).size() == delimiter_.size())
        {
            path_.emplace_back("");
            return start + delimiter_.size();
        }

        while (true)
        {
            auto end_path_part = str.find(delimiter_, start);
            std::string temp_segment = str.substr(start, end_path_part - start);
            ReplaceHexWithChar::Replace(temp_segment, ParserPathException("invalid hex code in path"));
            path_.push_back(std::move(temp_segment));
            if (end_path_part == std::string::npos)
            {
                break;
            }
            start = end_path_part + delimiter_.size();
        }
        return 1; //TODO: in future will return end of path segment
    }
}
