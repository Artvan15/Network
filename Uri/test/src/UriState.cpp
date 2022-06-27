#include "UriState.hpp"
#include <iostream>

UriState::Builder& ::UriState::Builder::SetInitialParsingString(std::string&& str)
{
    uri_state_.initial_parsing_string_ = std::move(str);
    return *this;
}

::UriState::Builder& ::UriState::Builder::SetFinalScheme(std::string&& final_scheme)
{
    uri_state_.final_scheme_ = std::move(final_scheme);
    return *this;
}

UriState::Builder& UriState::Builder::SetFinalUserInfo(std::string&& user_info)
{
    uri_state_.final_user_info_ = std::move(user_info);
    return *this;
}

::UriState::Builder& ::UriState::Builder::SetFinalHost(std::string&& final_host)
{
    uri_state_.final_host_ = std::move(final_host);
    return *this;
}

::UriState::Builder& ::UriState::Builder::SetFinalPath(std::vector<std::string>&& final_path)
{
    uri_state_.final_path_ = std::move(final_path);
    return *this;
}


UriState::Builder& UriState::Builder::SetFinalPortNumber(uint16_t final_port)
{
    uri_state_.final_port_ = final_port;
    return *this;
}


UriState::Builder& UriState::Builder::SetInitialDelimiter(std::string&& initial_delimiter)
{
    uri_state_.initial_delimiter_ = std::move(initial_delimiter);
    return *this;
}

UriState::Builder& UriState::Builder::SetIsRelativeReference(bool flag)
{
    uri_state_.is_relative_reference = flag;
    return *this;
}

UriState::Builder& UriState::Builder::SetHasRelativePath(bool flag)
{
    uri_state_.has_relative_path = flag;
    return *this;
}

UriState::Builder& UriState::Builder::SetFinalQuery(std::string&& final_query)
{
    uri_state_.final_query_ = std::move(final_query);
    return *this;
}

UriState::Builder& UriState::Builder::SetFinalFragment(std::string&& final_fragment)
{
    uri_state_.final_fragment_ = std::move(final_fragment);
    return *this;
}

::UriState::Builder::operator UriState()
{
    return std::move(uri_state_);
}




UriState::Builder UriState::create()
{
    return {};
}

std::ostream& operator<<(std::ostream& os, const UriState& obj)
{
    os <<
        "initial_parsing_string_: " << obj.initial_parsing_string_ <<
        " final_scheme_: " << obj.final_scheme_ <<
        " final_host_: " << obj.final_host_;

    os << "\nfinal_path_: ";
    for(const auto& str : obj.final_path_)
    {
        os << str << ' ';
    }
    return os;
}
