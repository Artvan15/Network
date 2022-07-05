#ifndef PARSER_RELATIVE_PATH
#define PARSER_RELATIVE_PATH

#include "ParserPath.hpp"
#include "ParserQuery.hpp"
#include "ParserFragment.hpp"

namespace ParserUri
{
	class ParseRelativeReference : public IParser
	{
	public:
		ParseRelativeReference(std::vector<std::string>& path, std::string& query, std::string& fragment,
			const std::string& delimiter)
			: delimiter_(delimiter), parser_path_(path, delimiter),
				parser_query_(query), parser_fragment_(fragment) {}

		size_t Parse(const std::string& str, size_t start) override;

	private:
		const std::string& delimiter_;
		ParserPath parser_path_;
		ParserQuery parser_query_;
		ParserFragment parser_fragment_;
	};
}
#endif

