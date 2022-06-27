#ifndef PARSER_URI
#define PARSER_URI

#include "ParserUri.hpp"

namespace ParserUri
{
	class ParserUrl : public IParser
	{
	protected:
		ParserUrl(std::string& user_info, std::string& host,
			std::optional<std::uint16_t>& port, std::vector<std::string>& path,
			std::string& query, std::string& fragment,
			const std::string& delimiter)
			: parser_user_info_(user_info), parser_host_(host, delimiter),
			parser_port_(port, delimiter), parser_path_(path, delimiter),
				parser_query_(query), parser_fragment_(fragment),
				delimiter_(delimiter) {}

		size_t Parse(const std::string& str, size_t start) override;

	protected:
		ParserUserInfo parser_user_info_;
		ParserHost parser_host_;
		ParserPort parser_port_;
		ParserPath parser_path_;
		ParserQuery parser_query_;
		ParserFragment parser_fragment_;
		
		const std::string& delimiter_;
	};
}
#endif


