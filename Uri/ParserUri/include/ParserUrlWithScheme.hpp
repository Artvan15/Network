#ifndef PARSER_URL_WITH_SCHEME
#define PARSER_URL_WITH_SCHEME

#include "ParserUrl.hpp"

namespace ParserUri
{
	class ParserUrlWithScheme : public ParserUrl
	{
	public:
		ParserUrlWithScheme(std::string& scheme, std::string& user_info, std::string& host,
			std::optional<std::uint16_t>& port, std::vector<std::string>& path,
			std::string& query, std::string& fragment,
			const std::string& delimiter)
				: ParserUrl(user_info, host, port, path, query, fragment, delimiter),
					parser_scheme_(scheme) {}

		size_t Parse(const std::string& str, size_t start) override;

	private:
		ParserScheme parser_scheme_;
	};
}
#endif

