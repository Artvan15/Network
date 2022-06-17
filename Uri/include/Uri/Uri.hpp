#ifndef URI
#define URI

#include <memory>
#include <string>
#include <vector>

namespace Uri
{
    class Uri
    {
    public:
        Uri();
        ~Uri();
        Uri(const Uri&) = delete;
        Uri& operator=(const Uri&) = delete;
        Uri(Uri&&) = delete;
        Uri& operator=(Uri&&) = delete;

        /**
         * Builds the URI from the parsed elements from
         * the given string
         *
         * @param[in] str
         *      This the string to parse
         *
         *  @return
         *      An indication the given URI was parsed
         *      successfully
         */
        bool ParseFromString(const std::string& str);

        /**
         * This method returns the "scheme" element of the URI
         *
         * @return
         *      The "scheme" element of the URI is returned
         *
         * @retval ""
         *      This returned if there's no "scheme" element
         *      in the URI
         */
        std::string GetScheme() const;

        /**
         * This method returns the "host" element of the URI
         *
         * @return
         *      The "host" element of the URI is returned
         *
         * @retval ""
         *      This returned if there's no "host" element
         *      in the URI
         */
        std::string GetHost() const;

        /**
         * This method returns the "path" of the URI
         * as a sequence of steps
         *
         * @note
         *      If the first step of the path is an empty
         *      string, then the URI has an absolute path
         *
         * @return
         *      The "path" element of the URI is returned
         *      as a sequence of steps
         */
        std::vector<std::string> GetPath() const;
             
    private:
        struct Impl;
        //unique pointer is fine for using an opaque type
        //as long as constructors and destructor are
        //external objects, not inline
        std::unique_ptr<Impl> pImpl_;
    };
}
#endif