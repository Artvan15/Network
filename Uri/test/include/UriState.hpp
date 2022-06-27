#ifndef URISTATE
#define URISTATE

#include <string>
#include <vector>
#include <optional>
#include <iostream>
#include <optional>

/**
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

    std::string GetFinalUserInfo() const { return final_user_info_; }

	std::string GetFinalHost() const { return final_host_; }

	std::vector<std::string> GetFinalPath() const { return final_path_; }

	std::string GetInitialDelimiter() const { return initial_delimiter_; }

	uint16_t GetPortNumber() const { return final_port_.value(); }

    bool GetHasPort() const { return final_port_.has_value(); }

    bool IsRelativeReference() const { return is_relative_reference; }
    bool HasRelativePath() const { return has_relative_path; }

    std::string GetFinalQuery() const { return final_query_; }

	std::string GetFinalFragment() const { return final_fragment_; }

private:
    UriState() = default;

private:
    std::string initial_parsing_string_;

    std::string initial_delimiter_;
    std::string final_scheme_;
    std::string final_user_info_;
    std::string final_host_;
    std::optional<uint16_t> final_port_;
    std::vector<std::string> final_path_;
    std::string final_query_;
    std::string final_fragment_;

    bool is_relative_reference = false;
    bool has_relative_path = false;

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

    Builder& SetFinalUserInfo(std::string&& user_info);

    Builder& SetFinalHost(std::string&& final_host);

    Builder& SetFinalPortNumber(uint16_t final_port);

    Builder& SetFinalPath(std::vector<std::string>&& final_path);

    Builder& SetInitialDelimiter(std::string&& initial_delimiter);

    Builder& SetIsRelativeReference(bool flag);

    Builder& SetHasRelativePath(bool flag);

    Builder& SetFinalQuery(std::string&& final_query);

    Builder& SetFinalFragment(std::string&& final_fragment);

    operator UriState();

private:
    UriState uri_state_;
};

#endif
