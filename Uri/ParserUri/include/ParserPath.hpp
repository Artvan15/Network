#pragma once
#include "IParser.hpp"
#include <vector>
#include <regex>

namespace ParserUri
{
	class ParserPath : public IParser
	{
	public:
		ParserPath(std::vector<std::string>& path, const std::string& delimiter) noexcept;

		size_t Parse(const std::string& str, size_t start) override;

	private:
		std::vector<std::string>& path_;
		const std::string& delimiter_;
		std::regex path_regex_;
	};
}

