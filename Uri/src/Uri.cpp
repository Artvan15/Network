#include "Uri/Uri.hpp"
#include <charconv>
#include <optional>
#include "ParserUrl.hpp"
#include "ParserUrn.hpp"
#include "ParserRelativePath.hpp"

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

        /**
         * 
         */
        std::unique_ptr<ParserUri::IParser> parser;
    };
    
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

        auto scheme_end = str.find(':', 0);
        if(scheme_end == std::string::npos)
        {
            pImpl_->parser = std::make_unique<ParserUri::ParseRelativePath>(
                pImpl_->path,
                pImpl_->delimiter);
        }
        else if(str.substr(scheme_end + 1, 2) == "//")
        {
            pImpl_->parser = std::make_unique<ParserUri::ParserUrl>(
                pImpl_->scheme,
                pImpl_->host,
                pImpl_->port,
                pImpl_->path,
                pImpl_->delimiter);
        }
        else
        {
            pImpl_->parser = std::make_unique<ParserUri::ParserUrn>(
                pImpl_->scheme,
                pImpl_->path,
                pImpl_->delimiter);
        }

        pImpl_->parser->Parse(str, 0);


        return true;
    }
    
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
