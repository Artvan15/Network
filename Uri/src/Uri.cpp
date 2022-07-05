#include "Uri/Uri.hpp"
#include <charconv>
#include <optional>

#include "ParserUrlWithScheme.hpp"
#include "ParserUrlWithoutScheme.hpp"
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
            user_info_.clear();
            query.clear();
            fragment.clear();
        }
                
        /**
         * "scheme" of the URI
         */
        std::string scheme;

        /**
         * "user info" of the URI
         *
         * @note
         *      goes after possible scheme and ends with a '@' char
         */
        std::string user_info_;

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
         
        if(str.size() > 1 && str.substr(0, 2) == "//")
        {
            pImpl_->parser = std::make_unique<ParserUri::ParserUrlWithoutScheme>(
                pImpl_->user_info_,
                pImpl_->host,
                pImpl_->port,
                pImpl_->path,
                pImpl_->query,
                pImpl_->fragment,
                pImpl_->delimiter
                );
        }
        else if (const auto colon = str.find(':', 0); 
            colon != std::string::npos && str.substr(colon + 1, 2) == "//")
        {
            pImpl_->parser = std::make_unique<ParserUri::ParserUrlWithScheme>(
                pImpl_->scheme,
                pImpl_->user_info_,
                pImpl_->host,
                pImpl_->port,
                pImpl_->path,
                pImpl_->query,
                pImpl_->fragment,
                pImpl_->delimiter
                );
        }
        //RelativeReference has path, first segment of which can't hold ':'
        else if(const auto first_segment_start = str.find(pImpl_->delimiter); 
            first_segment_start < colon || (first_segment_start == std::string::npos && colon == std::string::npos))
        {
            pImpl_->parser = std::make_unique<ParserUri::ParseRelativeReference>(
                pImpl_->path,
                pImpl_->query,
                pImpl_->fragment,
                pImpl_->delimiter);
        }
        
        else
        {
            pImpl_->parser = std::make_unique<ParserUri::ParserUrn>(
                pImpl_->scheme,
                pImpl_->path,
                pImpl_->query,
                pImpl_->fragment,
                pImpl_->delimiter);
        }
        //TODO: Factory for creating Parser???

        pImpl_->parser->Parse(str, 0);


        return true;
    }
    
    bool Uri::IsRelativeReference() const
    {
        return pImpl_->scheme.empty() && pImpl_->host.empty();
    }

    bool Uri::HasRelativePath() const
    {
        return (pImpl_->path.empty() ||
            !pImpl_->path.front().empty()) ? true : false;
    }

    std::string Uri::GetQuery() const
    {
        return pImpl_->query;
    }


	std::string Uri::GetScheme() const
    {
        return pImpl_->scheme;
    }

    std::string Uri::GetUserInfo() const
    {
        return pImpl_->user_info_;
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

    std::string Uri::GetFragment() const
    {
        return pImpl_->fragment;
    }

    void Uri::SetDelimiter(const std::string& str)
    {
        pImpl_->delimiter = str;
    }

}
