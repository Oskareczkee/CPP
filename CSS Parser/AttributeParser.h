#pragma once
#include "TokenStream.h"

enum class AttributeTokens
{
	BRACKETSBEGIN ='{',
	BRACKETSEND='}',
	COLON =':',
	SEMICOLON=';',
	ENDREAD='?',
	//token for name or value, they are pretty much treated the same
	NAMEORVALUE='N'
};

class AttributeParser : public TokenStream
{
	//inherit constructors
	using TokenStream::TokenStream;

	public:
		virtual Token get();
};
