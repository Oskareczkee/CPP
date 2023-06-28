#pragma once

#include "SelectorParser.h"

Token SelectorParser::get()
{
	if (full)
	{
		full = false;
		return buffer;
	}

	char ch;
	stream.get(ch);

	if (!stream)
		return Token((char)Tokens::INVALID);

	//ingore all spaces
	while (isspace(ch))
		stream.get(ch);

	//if ch is one of these tokens, return them
	if (ch == (char)SelectorTokens::COMMA)
		return Token(ch);

	//endread token is "????", when we find any '?' when loading css return endread token
	if(ch==(char)Tokens::ENDREAD)
		return Token((char)Tokens::ENDREAD);

	//if brackets, putback it cause it is usefull for attribute parser, and return token
	else if (ch == (char)SelectorTokens::BRACKETSBEGIN)
	{
		stream.putback(ch);
		return Token(ch);
	}
	
	myString val;
	//remember that char has been loaded and need to be stored, otherwise we will always miss 1st letter of attribute
	val += ch;
	stream.get(ch);
	//load everything till comma or brackets, we dont care what it is
	while (ch != (char)SelectorTokens::COMMA && ch != (char)SelectorTokens::BRACKETSBEGIN && stream)
	{
		//ignore spaces, load next char instead
		if (isspace(ch))
		{
			stream.get(ch);
			continue;
		}

		val += ch;
		stream.get(ch);
	}

	//putback whatever was not text, maybe its comma or bracketsbegin and may be usefull
	stream.putback(ch);

	//return token with selector
	return Token{(char)SelectorTokens::SELECTOR, val };
}