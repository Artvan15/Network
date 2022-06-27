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
         * Returns "user info" parsed from string
         *
         * @return
         *      The "user info" of the URI is returned
         *
         * @note
         *      user_info goes after possible scheme and
         *      ends with a '@' char
         */
        std::string GetUserInfo() const;

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


        /**
         * Returns port number parsed from a string
         *
         * @return
         *      The port number
         *
         * @note
         *      The return port number is only valid
         *      if HasPort() method returns true
         */
        uint16_t GetPortNumber() const;

        /**
         * Indicates whether port exist
         *
         * @return
         *      Flag that port is set
         */
        bool HasPort() const;

        /**
         * Indicates whether URI is a
         * relative reference
         * 
         * @return
         *      Indication whether URI is
         *      a relative reference
         *
         * @note
         *      URI is relative if Uri has no
         *      scheme, host, port. Only path
         */
        bool IsRelativeReference() const;

        /**
         * Indicates whether Uri has relative
         * path
         *
         * @return
         *      Indication whether Uri has
         *      a relative path
         *
         * @note
         *      Path is relative when it
         *      doesn't start with a delimiter
         */
        bool HasRelativePath() const;

        /**
         * Returns query of parsed from string
         *
         *  @return
         *      Query of the Uri
         *
         *  @note
         *      Query is part after '?' mark
         */
        std::string GetQuery() const;

        /**
         * Returns fragment parsed from string
         *
         * @return
         *      Fragment of the Uri
         *
         * @note
         *      Fragment is part after '#' mark
         */
        std::string GetFragment() const;
             
        /**
         * Set delimiter for parsing path
         *
         * @param [in] str
         *      Delimiter to set
         */
        void SetDelimiter(const std::string& str);

             
    private:
        struct Impl;
        //unique pointer is fine for using an opaque type
        //as long as constructors and destructor are
        //external objects, not inline
        std::unique_ptr<Impl> pImpl_;
    };
}
#endif