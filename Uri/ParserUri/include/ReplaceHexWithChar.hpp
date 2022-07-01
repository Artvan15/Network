#pragma once
#include <string>
#include "ParserException.hpp"

struct ReplaceHexWithChar
{
	template<typename DerivedParser>
	static void Replace(std::string& string, const ParserException<DerivedParser>& exception);
};

template<typename DerivedParser>
void ReplaceHexWithChar::Replace(std::string& string, const ParserException<DerivedParser>& exception)
{
    for (size_t hex_delimiter = string.find('%', 0); hex_delimiter != std::string::npos;
        hex_delimiter = string.find('%', hex_delimiter + 1))
    {
        std::string hex_string = string.substr(hex_delimiter + 1, 2);
        unsigned char char_from_hex = '\0';
        try
        {
            char_from_hex = std::stoul(hex_string, nullptr, 16);
        }
        catch (const std::exception& ex)
        {
            throw exception.CastToDerived();
        }
        string.replace(hex_delimiter, 3, 1, char_from_hex);
    }
}