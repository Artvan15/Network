#pragma once
#include "IParser.hpp"
#include <regex>

namespace ParserUri
{
	class ParserFragment : public IParser
	{
	public:
		ParserFragment(std::string& fragment) noexcept;

		size_t Parse(const std::string& str, size_t start) override;

	private:
		std::string& fragment_;
		std::regex fragment_regex_;
	};

}

