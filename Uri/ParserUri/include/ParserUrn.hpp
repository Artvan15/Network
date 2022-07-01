#ifndef PARSER_URN
#define PARSER_URN

#include "ParserScheme.hpp"
#include "ParserPath.hpp"

namespace ParserUri
{
	class ParserUrn : public IParser
	{
	public:
		ParserUrn(std::string& scheme, std::vector<std::string>& path,
			const std::string& delimiter)
			: parser_scheme_(scheme), parser_path_(path, delimiter) {}

		size_t Parse(const std::string& str, size_t start) override;

	private:
		ParserScheme parser_scheme_;
		ParserPath parser_path_;
	};
}

#endif
