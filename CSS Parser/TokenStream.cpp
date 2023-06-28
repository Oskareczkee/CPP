#pragma once

#include "TokenStream.h"

void TokenStream::putback(Token t)
{
	if (full) throw exception("Token Stream: calling putback while buffer is full");

	buffer = t;
	full = true;
}

void TokenStream::ignore(char c)
{
	if (full && c == buffer.kind)
	{
		full = false;
		return;
	}

	full = false;
	char ch = 0;

	while (stream >> ch)
		if (ch == c)return;
}