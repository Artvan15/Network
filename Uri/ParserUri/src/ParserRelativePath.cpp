#include "ParserRelativePath.hpp"

namespace ParserUri
{
	size_t ParseRelativePath::Parse(const std::string& str, size_t start)
	{
		auto possible_front_delimiter = str.substr(0, delimiter_.size());
		auto end_path = parser_path_.Parse(str, (possible_front_delimiter == delimiter_) ? delimiter_.size() : 0);
		return end_path;
	}
}
