#pragma once
#include <iostream>
#include "Token Stream.h"
#include "Calc Exceptions.h"
using namespace std;

void Token_Stream::putback(Token t)
{
	if (full) throw exception("Calling putback function, while buffer is full");
	buffer = t;
	full = true;
}

Token Token_Stream::get()
{
	if (full)
	{
		full = false;
		return buffer;
	}

	//cannot use cin, cin ignores whitespaces and newline characters
	char ch;
	cin.get(ch);
	while (isspace(ch) && ch != newline)cin.get(ch);

	switch (ch)
	{
		// each character represents itself
	case '(':
	case ')':
	case '+':
	case '-':
	case '*':
	case '/':
	case 'q':
	case result:
	case modulo:
	case print:
		return Token(ch);
	case newline:
		return Token(print);


	case '.':
	case'1': case'2':case'3':case'4':case'5':
	case'6':case'7':case'8':case'9':case'0': //loading numbers
	{
		cin.putback(ch);
		double val;
		cin >> val;
		return Token(number, val);
	}
	default:
		if (isalpha(ch) || ch=='_')
		{
			string s;
			s += ch;

			while (cin.get(ch) && (isalpha(ch) || isdigit(ch) || ch=='_'))s += ch;

			cin.putback(ch);
			if (s == declkey)return Token(let);
			else if (s == constkey)return Token(constant);
			else if (s == helpkey)return Token(help);
			else if (s == quitkey)return Token(quit);

			return Token(name, s);
		}

		throw exception("Undefined token");
	}

}

void Token_Stream::ignore(char c)
{
	if (full && c == buffer.kind)
	{
		full = false;
		return;
	}

	full = false;
	char ch = 0;

	while (cin >> ch)
		if (ch == c)return;
}




double SymbolTable::getValue(string var_name)
{
	for (Variable var : var_table)
		if (var.name == var_name)return var.value;
	//if not found, throw error
	throw NotDefinedVariableError(var_name);
}

void SymbolTable::set_value(string var_name, double value)
{
	for (Variable var : var_table)
		if (var.name == var_name)
		{
			if (var.isConstant)
				throw ConstantVariableValueChangeError(var.name);
			var.value = value;
			return;
		}
	//if not found, throw error
	throw NotDefinedVariableError(var_name);
}

bool SymbolTable::isDeclared(string var_name)
{
	for (Variable var : var_table)
		if (var.name == var_name)return true;
	return false;
}

double SymbolTable::defineName(string var_name, double value, bool isConstant)
{
	if (isDeclared(var_name)) throw DoubleDefinedVariableError(var_name);

	var_table.push_back(Variable(var_name, value, isConstant));

	return value;
}