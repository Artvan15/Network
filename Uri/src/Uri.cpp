#include "Uri/Uri.hpp"
#include <charconv>
#include <optional>
#include "ParserUrl.hpp"
#include "ParserUrn.hpp"
#include "ParserRelativeReference.hpp"

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
         * Query of the uri
         *
         * @note
         *      Comes after '?'
         */
        std::string query;

        /**
         * Fragment of the uri
         *
         * @note
         *      Comes after '#'
         */
        std::string fragment;

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
            pImpl_->parser = std::make_unique<ParserUri::ParseRelativeReference>(
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
        //TODO: Factory for creating Parser???

        pImpl_->parser->Parse(str, 0);


        return true;
    }
    
    bool Uri::IsRelativeReference() const
    {
        return pImpl_->scheme.empty();
    }

    bool Uri::HasRelativePath() const
    {
        return (pImpl_->path.empty() ||
            !pImpl_->path.front().empty()) ? true : false;
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
