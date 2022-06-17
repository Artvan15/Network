#include "UriState.hpp"

UriState::Builder& ::UriState::Builder::set_initial_parsing_string(std::string&& str)
{
    uri_state_.initial_parsing_string_ = std::move(str);
    return *this;
}

::UriState::Builder& ::UriState::Builder::set_final_scheme(std::string&& final_scheme)
{
    uri_state_.final_scheme_ = std::move(final_scheme);
    return *this;
}

::UriState::Builder& ::UriState::Builder::set_final_host(std::string&& final_host)
{
    uri_state_.final_host_ = std::move(final_host);
    return *this;
}

::UriState::Builder& ::UriState::Builder::set_final_path(std::vector<std::string>&& final_path)
{
    uri_state_.final_path_ = std::move(final_path);
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
