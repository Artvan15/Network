#include "ParserPort.hpp"

#include <charconv>

namespace ParserUri
{
    size_t ParserPort::Parse(const std::string& str, size_t start)
    {
        auto end_port = str.find(delimiter_, start);
        if (end_port == std::string::npos)
        {
            end_port = str.find_first_of("#?", start);
        }
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
}
