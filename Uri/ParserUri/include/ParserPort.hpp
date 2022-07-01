#pragma once
#include "IParser.hpp"
#include <optional>

namespace ParserUri
{
	class ParserPort : public IParser
	{
	public:
		ParserPort(std::optional<std::uint16_t>& port, const std::string& delimiter) noexcept
			: port_(port), delimiter_(delimiter) {}
		size_t Parse(const std::string& str, size_t start) override;

	private:
		std::optional<std::uint16_t>& port_;
		const std::string& delimiter_;
	};
}

