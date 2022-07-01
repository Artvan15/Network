#pragma once
#include "IParser.hpp"
#include <regex>

namespace ParserUri
{
	class ParserScheme : public IParser
	{
	public:
		ParserScheme(std::string& scheme) noexcept;
		size_t Parse(const std::string& str, size_t start) override;

	private:
		std::string& scheme_;
		std::regex scheme_regex_;
	};
}

