#pragma once
#include <stdexcept>

template<typename Derived>
struct ParserException : public std::runtime_error
{
	explicit ParserException(const std::string& str)
		: runtime_error(str) {} 

	const Derived& CastToDerived() const
	{
		return static_cast<const Derived&>(*this);
	}
};

struct ParserPortException : public ParserException<ParserPortException>
{
	using ParserException::ParserException;
};

struct ParserSchemeException : public ParserException<ParserSchemeException>
{
	using ParserException::ParserException;
};

struct ParserUserInfoException : public ParserException<ParserUserInfoException>
{
	using ParserException::ParserException;
};

struct ParserHostException : public ParserException<ParserHostException>
{
	using ParserException::ParserException;
};

struct ParserPathException : public ParserException<ParserPathException>
{
	using ParserException::ParserException;
};

struct ParserQueryException : public ParserException<ParserQueryException>
{
	using ParserException::ParserException;
};

struct ParserFragmentException : public ParserException<ParserFragmentException>
{
	using ParserException::ParserException;
};