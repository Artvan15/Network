#include "ParserUserInfo.hpp"
#include <ReplaceHexWithChar.hpp>

namespace ParserUri
{
    ParserUserInfo::ParserUserInfo(std::string& user_info) noexcept
        : user_info_(user_info), user_info_regex_("([\\w%-.~!$&'()*+,;=:])*")
    {}

    size_t ParserUserInfo::Parse(const std::string& str, size_t start)
    {
        auto end_user_info = str.find('@', start);
        if (end_user_info != std::string::npos)
        {
            std::string temp_user_info = str.substr(start, end_user_info - start);
            if (!std::regex_match(temp_user_info, user_info_regex_))
            {
                throw ParserUserInfoException("inaccessible character(s) in user_info");
            }
            ReplaceHexWithChar::Replace(temp_user_info, ParserUserInfoException("invalid hex code in user_info"));
            user_info_ = std::move(temp_user_info);
            return end_user_info + 1;
        }
        return start;
    }
}