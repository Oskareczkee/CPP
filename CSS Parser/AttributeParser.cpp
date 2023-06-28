#pragma once
#include "AttributeParser.h"

Token AttributeParser::get()
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

	//token was found
	switch (ch)
	{
	case (char)AttributeTokens::BRACKETSBEGIN:
	case (char)AttributeTokens::BRACKETSEND:
	case (char)AttributeTokens::COLON:
	case (char)AttributeTokens::SEMICOLON:
		return Token(ch);

	//endread token is "????", when we find any '?' when loading css return endread token
	case (char)Tokens::ENDREAD:
	{
		while (ch == (char)Tokens::ENDREAD)
			stream.get(ch);
		return Token((char)Tokens::ENDREAD);
	}
	//name or value
	//when declaring variable in switch case remember about brackets, othwerwise some unexpected error may occur
	default:
	{
		myString val;
		//store first letter
		val += ch;
		stream.get(ch);
		while (ch != (char)AttributeTokens::BRACKETSBEGIN
			&& ch != (char)AttributeTokens::BRACKETSEND
			&& ch != (char)AttributeTokens::COLON
			&& ch != (char)AttributeTokens::SEMICOLON
			&& stream)
		{
			val += ch;
			stream.get(ch);
		}

		//value has been loaded and token is propably one of the tokens in loop
		//remember to put it back, otherwise it will disappear, and may be useful for semantics
		stream.putback(ch);
		
		return Token((char)AttributeTokens::NAMEORVALUE, val);
	}
	}

	//if somehow code will get here, return invalid token (it should not get here by any means)
	return Token((char)Tokens::INVALID);
}