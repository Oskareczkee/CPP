#pragma once
#include "TokenStream.h"

enum class SelectorTokens
{
	COMMA = ',',
	BRACKETSBEGIN='{',
	SELECTOR = 'S'
};

class SelectorParser : public TokenStream
{
//inherit constructors
using TokenStream::TokenStream;

public:
	virtual Token get() override;
};
