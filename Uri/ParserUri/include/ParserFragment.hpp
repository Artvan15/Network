#pragma once
#include "IParser.hpp"

namespace ParserUri
{
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

