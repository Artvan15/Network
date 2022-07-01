#pragma once
#include "IParser.hpp"


namespace ParserUri
{
	class ParserHost : public IParser
	{
	public:
		ParserHost(std::string& host, const std::string& delimiter) noexcept
			: host_(host), delimiter_(delimiter) {}
		size_t Parse(const std::string& str, size_t start) override;

	private:
		void CheckIPLiteral(std::string& temp_host);
		void CheckIPv4(const std::string& temp_host);
		void CheckRegName(const std::string& temp_host);

	private:
		std::string& host_;
		const std::string& delimiter_;
	};
}

