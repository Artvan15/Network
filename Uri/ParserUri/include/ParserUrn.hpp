#ifndef PARSER_URN
#define PARSER_URN

#include "ParserScheme.hpp"
#include "ParserPath.hpp"
#include "ParserQuery.hpp"
#include "ParserFragment.hpp"

namespace ParserUri
{
	class ParserUrn : public IParser
	{
	public:
		ParserUrn(std::string& scheme, std::vector<std::string>& path,
			std::string& query, std::string& fragment,
			const std::string& delimiter)
			: parser_scheme_(scheme), parser_path_(path, delimiter),
				parser_query_(query), parser_fragment_(fragment){}

		size_t Parse(const std::string& str, size_t start) override;

	private:
		ParserScheme parser_scheme_;
		ParserPath parser_path_;
		ParserQuery parser_query_;
		ParserFragment parser_fragment_;
	};
}

#endif
