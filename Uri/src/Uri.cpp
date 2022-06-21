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

        void set_delimiter(const std::string& str)
        {
            delimiter = str;
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
            //Parse host
            auto end_authority = str.find(pImpl_->delimiter, scheme_end + 3);
            pImpl_->host = str.substr(scheme_end + 3, end_authority - scheme_end - 3);

            if(end_authority != std::string::npos)
            {
                parse_path(str, end_authority + pImpl_->delimiter.size(), pImpl_->delimiter);
            }
        }
        else
        {
            parse_path(str, scheme_end + 1, pImpl_->delimiter);
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

    void Uri::SetDelimiter(const std::string& str)
    {
        pImpl_->delimiter = str;
    }

}
