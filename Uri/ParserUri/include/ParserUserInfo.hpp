#pragma once
#include "IParser.hpp"
#include <regex>

namespace ParserUri
{
	class ParserUserInfo : public IParser
	{
	public:
		ParserUserInfo(std::string& user_info) noexcept;

		size_t Parse(const std::string& str, size_t start) override;

	private:
		std::string& user_info_;
		std::regex user_info_regex_;
	};
}

