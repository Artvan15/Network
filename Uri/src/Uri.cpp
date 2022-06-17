#include "Uri/Uri.hpp"


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
         * "path" of the URI, as a sequence of steps
         */
        std::vector<std::string> path;
    };

    Uri::Uri()
        : pImpl_(std::make_unique<Impl>()) {}
    
    Uri::~Uri() = default;

    bool Uri::ParseFromString(const std::string& str)
    {
        pImpl_->clear();

        auto scheme_end = str.find(':');
        pImpl_->scheme = str.substr(0, scheme_end);

        //for URI with authority
        if(str.substr(scheme_end + 1, 2) == "//")
        {
            auto end_authority = str.find('/', scheme_end + 3);
            pImpl_->host = str.substr(scheme_end + 3, end_authority - scheme_end - 3);

            while(end_authority != std::string::npos)
            {
                auto end_path_part = str.find('/', end_authority + 1);
                pImpl_->path.emplace_back(str, end_authority + 1, end_path_part - end_authority - 1);
                end_authority = end_path_part;
            }

        }
        //for URI without authority
        else
        {
            auto start_path_part = scheme_end;

            while(start_path_part != std::string::npos)
            {
                auto end_path_part = str.find(':', start_path_part + 1);
                pImpl_->path.emplace_back(str, start_path_part + 1, end_path_part - start_path_part - 1);
                start_path_part = end_path_part;
            }
        }

        return true;
    }

    std::string Uri::GetScheme() const
    {
        return pImpl_->scheme;
    }

    std::string Uri::GetHost() const
    {
        return pImpl_->host;
    }

    std::vector<std::string> Uri::GetPath() const
    {
        return pImpl_->path;
    }


}
