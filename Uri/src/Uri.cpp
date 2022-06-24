#include "Uri/Uri.hpp"
#include <charconv>
#include <optional>

namespace Uri
{
    struct Uri::Impl
    {
        //Method section
        /**
         * Clears all members of URI
         */
        void Clear()
        {
            scheme.clear();
            host.clear();
            if(port)
            {
                port = std::nullopt;
            }
            path.clear();
        }

        size_t ParseScheme(const std::string& str);

        size_t ParsePath(const std::string& str, size_t start_path_part);

        size_t ParseHost(const std::string& str, size_t start_host);

        bool ParsePortIfAny();
        
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

    size_t Uri::Impl::ParseScheme(const std::string& str)
    {
        auto scheme_end = str.find(':');
        if (scheme_end != std::string::npos)
        {
            scheme = str.substr(0, scheme_end);
        }
        return scheme_end;
    }

    size_t Uri::Impl::ParsePath(const std::string& str, size_t start_path_part)
    {
        while (true)
        {
            auto end_path_part = str.find(delimiter, start_path_part);
            path.emplace_back(str, start_path_part, end_path_part - start_path_part);
            if (end_path_part == std::string::npos)
            {
                break;
            }
            start_path_part = end_path_part + delimiter.size();
        }
        return 0; //TODO: in future will return end of path segment
    }

    size_t Uri::Impl::ParseHost(const std::string& str, size_t start_host)
    {
        auto end_authority = str.find(delimiter, start_host);
        host = str.substr(start_host, end_authority - start_host);
        return end_authority;
    }

    bool Uri::Impl::ParsePortIfAny()
    {
        //if authority has port
        if (auto port_delimiter = host.find(':'); port_delimiter != std::string::npos)
	    {
		    std::string str_port = host.substr(port_delimiter + 1);
	    	uint16_t port{ 0 };
	    	auto result = std::from_chars(str_port.c_str(), str_port.c_str() + str_port.size(), port);

	    	//check error_code and if all string was parsed
	    	if (static_cast<bool>(result.ec) || result.ptr != str_port.c_str() + str_port.size())
	    	{
	    		return false;
	    	}
	    	this->port = port;
	    	host = host.substr(0, port_delimiter);
	    }
        return true;
    }


    Uri::Uri()
        : pImpl_(std::make_unique<Impl>()) {}
    
    Uri::~Uri() = default;

    bool Uri::ParseFromString(const std::string& str)
    {
        pImpl_->Clear();
        if(str.empty())
        {
            return true;
        }        


        //Parse scheme
        auto scheme_end = pImpl_->ParseScheme(str);

        //if path is relative reference - parse path and exit
        if(IsRelativeReference())
        {
            pImpl_->ParsePath(str, (str.front() == '/') ? pImpl_->delimiter.size() : 0);
            return true;
        }

        //for URI with authority
        if(str.substr(scheme_end + 1, 2) == "//")
        {
            auto end_authority = pImpl_->ParseHost(str, scheme_end + 3);

            //parse port
        	if(!pImpl_->ParsePortIfAny())
            {
                return false;
            }
                        
            //parse path
            if(end_authority != std::string::npos)
            {
                pImpl_->ParsePath(str, end_authority + pImpl_->delimiter.size());
            }
        }
        //for URI without authority 
        else
        {
             pImpl_->ParsePath(str, scheme_end + 1);
        }

        return true;
    }
    //TODO: separate into smaller functions: ParseScheme(), ParseAuthority(), ParsePath()
    
    bool Uri::IsRelativeReference() const
    {
        return pImpl_->scheme.empty();

    }


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