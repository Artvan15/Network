#pragma once
#include <string>
#include <vector>
#include <optional>

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
		ParserScheme(std::string& scheme)
			: scheme_(scheme) {}
		size_t Parse(const std::string& str, size_t start) override;

	protected:
		std::string& scheme_;
	};

	class ParserHost : public IParser
	{
	public:
		ParserHost(std::string& host, const std::string& delimiter)
			: host_(host), delimiter_(delimiter) {}
		size_t Parse(const std::string& str, size_t start) override;

	protected:
		std::string& host_;
		const std::string& delimiter_;
	};

	class ParserPort : public IParser
	{
	public:
		ParserPort(std::optional<std::uint16_t>& port, const std::string& delimiter)
			: port_(port), delimiter_(delimiter) {}
		size_t Parse(const std::string& str, size_t start) override;

	protected:
		std::optional<std::uint16_t>& port_;
		const std::string& delimiter_;
	};

	class ParserPath : public IParser
	{
	public:
		ParserPath(std::vector<std::string>& path, const std::string& delimiter)
			: path_(path), delimiter_(delimiter) {}
		size_t Parse(const std::string& str, size_t start) override;

	protected:
		std::vector<std::string>& path_;
		const std::string& delimiter_;
	};

}