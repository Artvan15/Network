#pragma once
#include "IParser.hpp"
#include <vector>

namespace ParserUri
{
	class ParserPath : public IParser
	{
	public:
		ParserPath(std::vector<std::string>& path, const std::string& delimiter) noexcept
			: path_(path), delimiter_(delimiter) {}

		size_t Parse(const std::string& str, size_t start) override;

	private:
		std::vector<std::string>& path_;
		const std::string& delimiter_;
	};
}

