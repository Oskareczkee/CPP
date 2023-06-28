//does not work yet

#pragma once
#include <iostream>
#include <vector>
#include "Token Stream.h"
#include "Calc Exceptions.h"

using namespace std;

//defines
Token_Stream token_stream;
double primary(Token_Stream& ts);
double term(Token_Stream& ts);
double expression(Token_Stream& ts);
SymbolTable st;

void keep_window_open()
{
	char c;
	cout << "Type anything to close a program\n";
	cin.ignore();
	cin >> c;
}

void clean_mess(Token_Stream& ts)
{
	ts.ignore(print);
}

void ShowHelp()
{
	cout << "Welcome to the Token Calculator Help\n"
		<< "+,-,/,* performs standard mathematical operation\n"
		<< "use () to type in expressions inside it\n"
		<< "var \"var_name\" and const \"var_name\" to declare variables and constant variables (constant variables cannot be changed)\n"
		<< "quit to quit the program\n";
}
/*
* 
Grammar:
	Calculation:
		Statement
		Print
		Quit
		Calculation Statement

	Statement:
		Declaration
		Expression

	Declaration:
		"let" var_name "=" Expression
		"const" var_name "=" Expression
		"func" func_name "(func_var "," func_var ","...) "=" Expression
		var_name "=" Expression

Expression:
	Term
	Expression "+" Term
	Expression "-" Term
Term:
	Primary
	Term "*" Primary
	Term "\" Primary
	Term "%" Primary
Primary:
	Number
	"("Expression")"
	"-"Primary
	"+"Primary
	Variable
Number:
	Floating-point-literal
*/


double declaration(Token k, Token_Stream& ts)
{
	Token t = ts.get();

	if (t.kind != name)throw exception("Expected name in declaration");
	
	string var_name = t.name;

	Token t2 = ts.get();
	if (t2.kind != '=')
	{
		string excepction = "Expected '=' in variable declaration in: " + var_name;
		throw exception(excepction.c_str());
	}
	double d = expression(ts);
	st.defineName(var_name, d, k.kind==constant);
	return d;
}

double statement(Token_Stream& ts)
{
	Token t = ts.get();
	switch (t.kind)
	{
	case let:
	case constant:
		return declaration(t, ts);
	default:
		ts.putback(t);
		return expression(ts);
	}
}

double term(Token_Stream& ts)
{
	double left = primary(ts);
	Token t = ts.get();

	while (true)
	{
		switch (t.kind)
		{
		case '*':
			left *= primary(ts);
			t = ts.get();
			break;
		case '/':
		{
			double d = primary(ts);
			if (d == 0)
				throw DivideByZeroError();
			left /=d;
			t = ts.get();
			break;
		}

		case modulo:
		{
			double d = primary(ts);
			if (d == 0) throw DivideByZeroError();
			left = fmod(left, d);
			t = ts.get();
			break;
		}

		default:
			ts.putback(t);
			return left;
		}
	}
}

double primary(Token_Stream& ts)
{
	Token t = ts.get();
	switch (t.kind)
	{
		case '(':
		{
			double d = expression(ts);
			t = ts.get();
			if (t.kind != ')') throw exception("Expected ')' operator after expression");
			return d;
		}
		case number:
			return t.value;
		case '-':
			return -primary(ts);
		case '+':
			return primary(ts);
		case name:
		{
			Token next = ts.get();
			if (next.kind == assign)
			{
				double d = expression(ts);
				st.set_value(t.name, d);
				return d;
			}
			ts.putback(next);
			return st.getValue(t.name);
		}
		default:
			throw exception("Expected expression");
	}
}


double expression(Token_Stream& ts)
{
	double left = term(ts);
	Token t = ts.get();

	while (true)
	{
		switch (t.kind)
		{
		case '+':
			left += term(ts);
			t = ts.get();
			break;
		case '-':
			left -= term(ts);
			t = ts.get();
			break;
		default:
			ts.putback(t);
			return left;
		}
	}

}

void Run(Token_Stream& ts)
{
	st.defineName("pi", 3.14, true);
	while (cin)
	{

		try
		{
			cout << (char)prompt;
			Token t = ts.get();
			while (t.kind == print)
			{
				t=ts.get();
			}
			if (t.kind == quit)break;
			if (t.kind == help)ShowHelp();

				ts.putback(t);
				cout << (char)result << statement(ts) << "\n";
		}
		catch (exception& e)
		{
			cerr << e.what() << "\n";
			clean_mess(ts);
		}
		catch (...)
		{
			cerr << "Undefined Exception\n";
			clean_mess(ts);
		}
	}
		keep_window_open();

}


