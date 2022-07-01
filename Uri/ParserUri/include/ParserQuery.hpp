#pragma once
#include "IParser.hpp"

namespace ParserUri
{
	class ParserQuery : public IParser
	{
	public:
		ParserQuery(std::string& query) noexcept
			: query_(query) {}
		size_t Parse(const std::string& str, size_t start) override;

	private:
		std::string& query_;
	};
}

