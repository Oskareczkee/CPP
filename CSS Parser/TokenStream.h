#pragma once
#include<iostream>
#include "myString.h"

using namespace std;

struct Token
{
	char kind;
	myString val;

	Token(char ch) :kind(ch) {}
	Token(char ch, myString value) :kind(ch), val(value) {}
	Token():kind(0){}
};

//here you can add general use tokens, like invalid
enum class Tokens
{
	INVALID = 0,
	ENDREAD='?'
};

class TokenStream
{
	protected:
		istream& stream;
		Token buffer;
		bool full;
	public:
		TokenStream(istream& s) : stream(s), buffer(0), full(false) {}

		//virtual get with 0 makes class interface, which will be used by parsers to parse
		//each parser will override get and have its own implementation - having own get function for its functionalities
		virtual Token get()=0;
		void putback(Token t);
		void ignore(char c);
};
