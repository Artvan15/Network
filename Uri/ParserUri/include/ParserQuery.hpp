#pragma once
#include "IParser.hpp"
#include <regex>

namespace ParserUri
{
	class ParserQuery : public IParser
	{
	public:
		ParserQuery(std::string& query) noexcept;

		size_t Parse(const std::string& str, size_t start) override;

	private:
		std::string& query_;
		std::regex query_regex_;
	};
}

