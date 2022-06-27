#ifndef PARSER_URL_WITHOUT_SCHEME
#define PARSER_URL_WITHOUT_SCHEME

#include "ParserUrl.hpp"

namespace ParserUri
{
	class ParserUrlWithoutScheme : public ParserUrl
	{
	public:
		ParserUrlWithoutScheme(std::string& user_info, std::string& host,
			std::optional<std::uint16_t>& port, std::vector<std::string>& path,
			std::string& query, std::string& fragment,
			const std::string& delimiter)
			: ParserUrl(user_info, host, port, path, query, fragment, delimiter)
				{}

		size_t Parse(const std::string& str, size_t start) override;
	};
}

#endif

