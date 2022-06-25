#include "ParserUri.hpp"
#include "ParserException.hpp"
#include <charconv>

namespace ParserUri
{
    size_t ParserScheme::Parse(const std::string& str, size_t start)
    {
        auto scheme_end = str.find(':', start);
        if (scheme_end != std::string::npos)
        {
            scheme_ = str.substr(0, scheme_end);
        }
        return scheme_end;
    }

    size_t ParserHost::Parse(const std::string& str, size_t start)
    {
        auto end_authority = str.find(':', start);
        if (end_authority == std::string::npos)
        {
            end_authority = str.find(delimiter_, start);
        }
        host_ = str.substr(start, end_authority - start);
        return end_authority;
    }

    size_t ParserPort::Parse(const std::string& str, size_t start)
    {
        auto end_port = str.find(delimiter_, start);
        std::string str_port = str.substr(start, end_port - start);
        uint16_t port{ 0 };
        auto result = std::from_chars(str_port.c_str(), str_port.c_str() + str_port.size(), port);

        //check error_code and if all string was parsed
        if (static_cast<bool>(result.ec) || result.ptr != str_port.c_str() + str_port.size())
        {
            throw ParserPortException("port is not valid");
        }
        port_ = port;
        return end_port;
    }

    size_t ParserPath::Parse(const std::string& str, size_t start)
    {
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
        return 0; //TODO: in future will return end of path segment
    }

}