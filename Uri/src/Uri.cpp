#include "Uri/Uri.hpp"
#include <charconv>
#include <optional>

namespace Uri
{
    struct Uri::Impl
    {
        //Method section
        void clear()
        {
            scheme.clear();
            host.clear();
            path.clear();
        }
        

        /**
         * "scheme" of the URI
         */
        std::string scheme;

        /**
         * "host" of the URI
         */
        std::string host;

        /**
         * "port" of the URI
         *
         * @note
         *     set to std::nullopt if port isn't valid
         */
        std::optional<uint16_t> port;

        /**
         * "path" of the URI, as a sequence of steps
         */
        std::vector<std::string> path;

        /**
        * Delimiter for path
        */
        std::string delimiter = "/";
    };
    

    Uri::Uri()
        : pImpl_(std::make_unique<Impl>()) {}
    
    Uri::~Uri() = default;

    bool Uri::ParseFromString(const std::string& str)
    {
        pImpl_->clear();

        //Parse path
        auto parse_path = [this](const std::string& str, size_t start_path_part, const std::string& delimiter)
        {
            while (true)
            {
                auto end_path_part = str.find(delimiter, start_path_part);
                pImpl_->path.emplace_back(str, start_path_part, end_path_part - start_path_part);
                if(end_path_part == std::string::npos)
                {
                    break;
                }
                start_path_part = end_path_part + pImpl_->delimiter.size();
            }
        };


        //Parse scheme
        auto scheme_end = str.find(':');
        pImpl_->scheme = str.substr(0, scheme_end);

        //for URI with authority
        if(str.substr(scheme_end + 1, 2) == "//")
        {
            //save authority
            auto end_authority = str.find(pImpl_->delimiter, scheme_end + 3);
        	pImpl_->host = str.substr(scheme_end + 3, end_authority - scheme_end - 3);

            //if authority has port
        	if(auto port_delimiter = pImpl_->host.find(':'); port_delimiter != std::string::npos)
            {
                std::string str_port = pImpl_->host.substr(port_delimiter + 1);
                uint16_t port{ 0 };
                auto result = std::from_chars(str_port.c_str(), str_port.c_str() + str_port.size(), port);

                //check error_code and if all string was parsed
                if(static_cast<bool>(result.ec) || result.ptr != str_port.c_str() + str_port.size())
                {
                    return false;
                }
                pImpl_->port = port;
                pImpl_->host = pImpl_->host.substr(0, port_delimiter);
            }
            

            if(end_authority != std::string::npos)
            {
                parse_path(str, end_authority + pImpl_->delimiter.size(), pImpl_->delimiter);
            }
        }
        //for URI without authority 
        else
        {
            parse_path(str, scheme_end + 1, pImpl_->delimiter);
        }

        return true;
    }
    //TODO: separate into smaller functions: ParseScheme(), ParseAuthority(), ParsePath()
    
    std::string Uri::GetScheme() const
    {
        return pImpl_->scheme;
    }

    std::string Uri::GetHost() const
    {
        return pImpl_->host;
    }

    bool Uri::HasPort() const
    {
        return pImpl_->port.has_value();
    }


    uint16_t Uri::GetPortNumber() const
    {
        return pImpl_->port.value();
    }


    std::vector<std::string> Uri::GetPath() const
    {
        return pImpl_->path;
    }

    void Uri::SetDelimiter(const std::string& str)
    {
        pImpl_->delimiter = str;
    }

}

//TODO: c++17 parameter in cmake