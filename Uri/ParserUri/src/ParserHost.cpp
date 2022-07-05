#include "ParserHost.hpp"
#include "ParserException.hpp"
#include "ReplaceHexWithChar.hpp"
#include <regex>

namespace ParserUri
{
    size_t ParserHost::Parse(const std::string& str, size_t start)
    {
        size_t end_host{ 0 };
        std::string temp_host;


        //IPv6 or IPvFuture
    	if(str[start] == '[')
        {
            end_host = str.find(']', start);
            if(end_host == std::string::npos)
            {
                throw ParserHostException("IPv6/Future is invalid");
            }
            temp_host = str.substr(start, end_host + 1 - start);
            CheckIPLiteral(temp_host);
        }

        else
        {
            //find on what host ends (port, path(delimiter), query, fragment 
            end_host = std::min(str.find_first_of(":#?", start),
                str.find(delimiter_, start));
            temp_host = str.substr(start, end_host - start);

            if (std::regex IPv4_regex(R"(\d{1,3}\.\d{1,3}\.\d{1,3}\.\d{1,3})"); std::regex_match(temp_host, IPv4_regex))
            {
                CheckIPv4(temp_host);
            }
            else
            {
                CheckRegName(temp_host);
                ReplaceHexWithChar::Replace(temp_host, ParserHostException("invalid hex code in host"));
            }
        }

        host_ = std::move(temp_host);
        return end_host;
    }

    void ParserHost::CheckIPLiteral(std::string& temp_host)
    {       
        //IPvFuture
    	if(temp_host[1] == 'v')
        {
            if (std::regex IPvFuture_regex(R"([0-9A-F]+\.[\w:\-\.~!$&'()*+,;=]+)");
                !std::regex_match(temp_host.begin() + 2, temp_host.end() - 1, IPvFuture_regex))
                {
					throw ParserHostException("IPvFuture is not valid");
                }
            
        }
        //TODO: IPv6 check
        else
        {
	        
        }

    }

    //TODO: IPv4 check
    void ParserHost::CheckIPv4(const std::string& temp_host)
    {
	    
    }

    void ParserHost::CheckRegName(const std::string& temp_host)
    {
        std::regex reg_name_regex(R"([\w%\-\.~!$&'()*+,;=]*)");
        if(!std::regex_match(temp_host, reg_name_regex))
        {
            throw ParserHostException("reg_name host has invalid characters");
        }
    }
    
}
