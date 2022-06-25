#ifndef PARSER_URI
#define PARSER_URI

#include "ParserUri.hpp"

namespace ParserUri
{
	class ParserUrl : public IParser
	{
	public:
		ParserUrl(std::string& scheme, std::string& host,
			std::optional<std::uint16_t>& port, std::vector<std::string>& path,
			const std::string& delimiter)
			: parser_scheme_(scheme), parser_host_(host, delimiter),
			parser_port_(port, delimiter), parser_path_(path, delimiter) {}

		size_t Parse(const std::string& str, size_t start) override;

	private:
		ParserScheme parser_scheme_;
		ParserHost parser_host_;
		ParserPort parser_port_;
		ParserPath parser_path_;
	};
}
#endif


