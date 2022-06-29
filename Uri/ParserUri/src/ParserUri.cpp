#include "ParserUri.hpp"
#include "ParserException.hpp"
#include <charconv>

namespace ParserUri
{
    ParserScheme::ParserScheme(std::string& scheme) noexcept
        : scheme_(scheme), scheme_regex_("[a-zA-Z]([a-zA-Z0-9+-\\.])*")
    {}

    size_t ParserScheme::Parse(const std::string& str, size_t start)
    {
        auto scheme_end = str.find(':', start);
        std::string temp_scheme = str.substr(start, scheme_end);
        if(!std::regex_match(temp_scheme, scheme_regex_))
        {
            throw ParserSchemeException("scheme isn't valid");
        }
        scheme_ = std::move(temp_scheme);
        return scheme_end;
    }

    size_t ParserHost::Parse(const std::string& str, size_t start)
    {
        //find on what host ends (port, path(delimiter), query, fragment 
        auto end_authority = std::min(str.find_first_of(":#?", start),
            str.find(delimiter_, start));
        host_ = str.substr(start, end_authority - start);
        return end_authority;
    }

    size_t ParserPort::Parse(const std::string& str, size_t start)
    {
        auto end_port = str.find(delimiter_, start);
        if(end_port == std::string::npos)
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

    size_t ParserPath::Parse(const std::string& str, size_t start)
    {
        //Corner case, when path only consists of delimiter
        if(str.substr(start).size() == delimiter_.size())
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

    size_t ParserQuery::Parse(const std::string& str, size_t start)
    {
        auto end_query = str.find('#', start);
        query_ = str.substr(start, end_query - start);
        return end_query;
    }

    size_t ParserFragment::Parse(const std::string& str, size_t start)
    {
        fragment_ = str.substr(start);
        return 1;
        //TODO: should mark the end of the fragment
    }

    ParserUserInfo::ParserUserInfo(std::string& user_info) noexcept
        : user_info_(user_info), user_info_regex_("([\\w%-.~!$&'()*+,;=:])*")
    {}

    size_t ParserUserInfo::Parse(const std::string& str, size_t start)
    {
        auto end_user_info = str.find('@', start);
        if (end_user_info != std::string::npos)
        {
            std::string temp_user_info = str.substr(start, end_user_info - start);
            if(!std::regex_match(temp_user_info, user_info_regex_))
            {
                throw ParserUserInfoException("inaccessible character(s) in user_info");
            }

            for(size_t hex_delimiter = temp_user_info.find('%', 0); hex_delimiter != std::string::npos;
                hex_delimiter = temp_user_info.find('%', hex_delimiter + 1))
            {
                std::string hex_string = temp_user_info.substr(hex_delimiter + 1, 2);
                unsigned char char_from_hex = '\0';
            	try
                {
                    char_from_hex = std::stoul(hex_string, nullptr, 16);
                }
                catch(const std::exception& ex)
                {
                    throw ParserUserInfoException("hex in user_info is ill-formed");
                }
                temp_user_info.replace(hex_delimiter, 3, 1, char_from_hex);
            }

            user_info_ = std::move(temp_user_info);
            return end_user_info + 1;
        }
        return start;
    }

}