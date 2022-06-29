#pragma once
#include <string>
#include <vector>
#include <optional>
#include <regex>

namespace ParserUri
{
	struct IParser
	{
		virtual ~IParser() = default;
		virtual size_t Parse(const std::string& str, size_t start) = 0;
	};


	class ParserScheme : public IParser
	{
	public:
		ParserScheme(std::string& scheme) noexcept;
		size_t Parse(const std::string& str, size_t start) override;

	protected:
		std::string& scheme_;
		std::regex scheme_regex_;
	};

	class ParserUserInfo : public IParser
	{
	public:
		ParserUserInfo(std::string& user_info) noexcept;

		size_t Parse(const std::string& str, size_t start) override;

	protected:
		std::string& user_info_;
		std::regex user_info_regex_;
	};

	class ParserHost : public IParser
	{
	public:
		ParserHost(std::string& host, const std::string& delimiter) noexcept
			: host_(host), delimiter_(delimiter) {}
		size_t Parse(const std::string& str, size_t start) override;

	protected:
		std::string& host_;
		const std::string& delimiter_;
	};

	class ParserPort : public IParser
	{
	public:
		ParserPort(std::optional<std::uint16_t>& port, const std::string& delimiter) noexcept
			: port_(port), delimiter_(delimiter) {}
		size_t Parse(const std::string& str, size_t start) override;

	protected:
		std::optional<std::uint16_t>& port_;
		const std::string& delimiter_;
	};

	class ParserPath : public IParser
	{
	public:
		ParserPath(std::vector<std::string>& path, const std::string& delimiter) noexcept
			: path_(path), delimiter_(delimiter) {}

		size_t Parse(const std::string& str, size_t start) override;

	protected:
		std::vector<std::string>& path_;
		const std::string& delimiter_;
	};

	class ParserQuery : public IParser
	{
	public:
		ParserQuery(std::string& query) noexcept
			: query_(query) {}
		size_t Parse(const std::string& str, size_t start) override;

	protected:
		std::string& query_;
	};

	class ParserFragment : public IParser
	{
	public:
		ParserFragment(std::string& fragment) noexcept
			: fragment_(fragment) {}
		size_t Parse(const std::string& str, size_t start) override;

	private:
		std::string& fragment_;
	};

}