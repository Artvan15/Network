#ifndef URISTATE
#define URISTATE

#include <string>
#include <vector>
#include <iostream>

/*
 * This class saves initial params, that are set
 * and final params, that are checked by TEST
 */
class UriState
{
    class Builder;
public:
    static Builder create();

    std::string GetInitialParsingString() const { return initial_parsing_string_; }
    std::string GetFinalScheme() const { return final_scheme_; }
    std::string GetFinalHost() const { return final_host_; }
    std::vector<std::string> GetFinalPath() const { return final_path_; }
    std::string GetInitialDelimiter() const { return initial_delimiter_; }

private:
    UriState() = default;

private:
    std::string initial_parsing_string_;
    std::string final_scheme_;
    std::string final_host_;
    std::vector<std::string> final_path_;
    std::string initial_delimiter_;

    friend std::ostream& operator<<(std::ostream& os, const UriState& obj);
};

/*
 * UriState::Builder is used to incapsulate
 * the creation of object and force user to use
 * set_functions
 */
class UriState::Builder
{
public:
    Builder() = default;
    Builder(const Builder&) = delete;
    Builder(Builder&&) = delete;
    Builder& operator=(const Builder&) = delete;
    Builder& operator=(Builder&&) = delete;
    ~Builder() = default;

    Builder& SetInitialParsingString(std::string&& str);

    Builder& SetFinalScheme(std::string&& final_scheme);

    Builder& SetFinalHost(std::string&& final_host);

    Builder& SetFinalPath(std::vector<std::string>&& final_path);

    Builder& SetInitialDelimiter(std::string&& initial_delimiter);

    operator UriState();

private:
    UriState uri_state_;
};

#endif