#ifndef PARSER_RELATIVE_PATH
#define PARSER_RELATIVE_PATH
#include "ParserUri.hpp"

namespace ParserUri
{
	class ParseRelativePath : public IParser
	{
	public:
		ParseRelativePath(std::vector<std::string>& path, const std::string& delimiter)
			: delimiter_(delimiter), parser_path_(path, delimiter) {}

		size_t Parse(const std::string& str, size_t start) override;

	private:
		const std::string& delimiter_;
		ParserPath parser_path_;
	};
}
#endif

