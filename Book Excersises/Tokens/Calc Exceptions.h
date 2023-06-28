#pragma once
#include <iostream>

struct DivideByZeroError
{
	DivideByZeroError() { throw std::exception("Cannot divide by zero !"); };
};

struct NotDefinedVariableError
{
	NotDefinedVariableError(string var_name) { string message = var_name + " has not been defined !"; throw std::exception(message.c_str()); };
};

struct DoubleDefinedVariableError
{
	DoubleDefinedVariableError(string var_name) { string message = var_name + " has been already defined !"; throw std::exception(message.c_str()); };
};

struct ConstantVariableValueChangeError
{
	ConstantVariableValueChangeError(string var_name) { string message = var_name + " is constant"; throw std::exception(message.c_str()); };
};