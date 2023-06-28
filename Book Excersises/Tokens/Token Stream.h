#pragma once
#include <iostream>
#include <vector>
using namespace std;

enum Tokens {
	print = ';',
	newline = '\n',
	number = '8',
	result = '=',
	assign ='=',
	modulo = '%',
	prompt = '>',
	name='N',
	let='L',
	constant='C',
	help='H',
	quit = 'Q',
};

const string declkey = "var";
const string constkey = "const";
const string helpkey = "help";
const string quitkey = "quit";

class Variable
{
public:
	string name;
	double value;
	bool isConstant;
	Variable(string var_name, double Value, bool isConst = false) :name(var_name), value(Value), isConstant(isConst) {};
};


//mayble i will implement functions in future
class Function
{
	public:
		string name;
		vector<Variable> args;
		bool isConstant;
		Function(string func_name, vector<Variable>arguments, bool isConst = false) : name(func_name), args(arguments), isConstant(isConst) {};
};

class FunctionTable
{
public:
	void defineName(string func_name, Variable* args, bool isConstant);
	bool isDeclared(string func_name, vector<Variable> args);
private:
	vector<Function>func_table;
};

class SymbolTable
{
public:
	double getValue(string var_name);
	void set_value(string var_name, double value);
	double defineName(string var_name, double value, bool isConstant);
	bool isDeclared(string var_name);
private:
	vector<Variable> var_table;
};

class Token
{
public:
	char kind;
	double value;
	string name;
	Token(char ch) : kind(ch), value(0) {};
	Token(char ch, double val) : kind(ch), value(val) {};
	Token(char ch, string Name) : kind(ch), name(Name), value(0) {};
};

class Token_Stream
{
public:
	Token_Stream() : full(false), buffer(0)/*stream(0)*/ {};
	//Token_Stream(istream& inputStream) : full(false), buffer(0)stream(inputStream){};
	Token get();
	void putback(Token t);
	void ignore(char c);

private:
	//istream stream;
	bool full;
	Token buffer;
};
