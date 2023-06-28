#pragma once

//since we use old C functions, many of them are considered unsafe
//and compiler does not allow us this program, cause warning 4996
//we disable it, cause "we know what we do"
//if we had used string, there would be no such problems, string functions are pretty safe
#pragma warning(disable : 4996)
#include "CommandHandler.h"

void CommandHandler::GetCommand()
{
	//max command size - 100
	char command[100];
	//cout << "command: ";
	cin.getline(command, sizeof(command), '\n');

	//tokenize string, ',' is delimeter
	//we use null at 2 last ones, this is proper according to the documentation
	//we would use better tools if we would have been working with string, but we can't
	const char* token1 = strtok(command, ",");
	const char* token2 = strtok(NULL, ",");
	const char* token3 = strtok(NULL, ",");

	//if token 1 is empty, end input
	//this is for stos i hope this will work
	if (token1 == NULL)
		return;

	//carry null tokens
	if (!token1)
		token1 = "";
	if (!token2)
		token2 = "";
	if (!token3)
		token3 = "";
	//comamnd handling


	//**** command - continue reading CSS
	//i use strcmp, when i have to compare 2 strings, if i need to compare only 1st character i use standard comparsion
	//strcmp - compares 2 char strings, returns 0 if they are equal
	if (strcmp(token1, "****") == 0)
	{
		//parser will parse till next ???? or file/stream end
		parser.Parse();
		return;
	}



	/*
	if (token1[0] == 'p')
	{
		parser.PrintContent();
		cout << "\n";
		return;
	}
	*/

	//?
	if (token1[0]=='?')
	{
		cout << token1<< " == ";
		cout << parser.blocksNumber() << "\n";
		return;
	}
	
	//SELECTOR COMMANDS
	if (token2[0] == 'S' || token2[0] == 's')
	{
		//token 1 is not a numer, then it is selector
		int num = atoi(token1);
		//z,S,?
		if (num == 0)
		{
			if (token3[0] != '?')
			{
				//cout << "Command does not exist\n";
				return;
			}
			
			cout << token1 << "," << token2 << "," << token3 << " == ";
			cout << parser.getSelectorCount(token1) << "\n";
			return;
		}
		//i,S,?
		else if (token3[0] == '?')
		{
			int count = parser.blockSelectorCount(num - 1);
			if (count != 0)
			{
				cout << token1 << "," << token2 << "," << token3 << " == ";
				cout << count << "\n";
			}
			return;
		}
		//i,S,j
		else if (atoi(token3) != 0)
		{
			int num2 = atoi(token3);
			myString str = parser.getBlockSelector(num - 1, num2 - 1);
			if (str != "")
			{
				cout << token1 << "," << token2 << "," << token3 << " == ";
				str.print();
				cout << "\n";
				return;
			}
			return;
		}
		else
		{
			//cout << "Command does not exist\n";
			return;
		}
	}

	//ATTRIBUTES COMMANDS

	else if (token2[0] == 'A' || token2[0] == 'a')
	{
		//check whether token 1 is a number
		int num = atoi(token1);
		if (num == 0)
		{
			if (token3[0] == '?')
			{
				cout << token1 << "," << token2 << "," << token3 << " == ";
				cout << parser.getAttributeCount(token1) << "\n";
				//printAttributeOccurrenceCount(token1);
				return;
			}
			else
			{
				//cout << "Command does not exist\n";
				return;
			}
		}
		//i,A,?
		else if (token3[0]=='?')
		{
			int output = parser.getBlockAttributesCount(num-1);

			if (output == -1)
				return;
			else
			{
				cout << token1 << "," << token2 << "," << token3<<" == ";
				cout << output << "\n";
			}
			return;
		}
		//i,A,n
		else
		{
			myString output = parser.getBlockAttributeValue(num - 1, token3);
			if (output != "")
			{
				cout << token1 << "," << token2 << "," << token3 << " == ";
				output.print();
				cout << "\n";
				return;
			}
			//printBlockAttributeValue(num - 1, token3);
			return;
		}
	}

	//DELETE COMMANDS

	else if (token2[0] == 'D' || token2[0] == 'd')
	{
		//all delete commands have a number as the first token, so if it is not a number, command does not exist
		int num = atoi(token1);
		if (num == 0)
		{
			//cout << "Command does not exist\n";
			return;
		}
		//i,D,*
		else if (token3[0] == '*')
		{
			if (parser.removeBlock(num - 1))
				cout << token1 << "," << token2 << "," << token3 << " ==  deleted\n";
				//removeBlock(num - 1);
			return;
		}
		//i,D,n
		else
		{
			if(parser.removeBlockAttribute(num-1, token3))
				cout << token1 << "," << token2 << "," << token3 << " ==  deleted\n";
			//removeAttributeFromBlock(num-1, token3);
			return;
		}
	}

	//THE MIGHTY E COMMAND

	//z,E,n
	else if (token2[0] == 'E' || token2[0] == 'e')
	{
		myString output = parser.getSelectorAttributeValue(token1, token3);
		if (output != "")
		{
			cout << token1 << "," << token2 << "," << token3 << " == ";
			output.print();
			cout << "\n";
		}

		//printAttributeFromSelector(token1, token3);
		return;
	}

	else
	{
		//cout << "Command does not exist\n";
		return;
	}
}

/*
void CommandHandler::printBlocksNum()
{
	cout << parser.blocksNumber() << "\n";
}

void CommandHandler::printSelectorCount(const myString& selector)
{
	cout << parser.getSelectorCount(selector) << "\n";
}

void CommandHandler::printSelectorCountForBlock(const int& blockIndex)
{
	cout << parser.blockSelectorCount(blockIndex) << "\n";
}

void CommandHandler::printSelectorForBlock(const int& blockIndex, const int& selectorIndex)
{
	parser.getBlockSelector(blockIndex, selectorIndex).print();
	cout << "\n";
}

void CommandHandler::printBlockAttributes(const int& blockIndex)
{
	int num = parser.getBlockAttributesCount(blockIndex);

	if (num == -1)
		return;
	else
		cout << num << "\n";
}

void CommandHandler::printBlockAttributeValue(const int& blockIndex, const myString& attrName)
{
	parser.getBlockAttributeValue(blockIndex, attrName).print();
	cout << "\n";
}

void CommandHandler::printAttributeOccurrenceCount(const myString& attrName)
{
	cout << parser.getAttributeCount(attrName) << "\n";
}

void CommandHandler::removeBlock(const int& blockIndex)
{
	parser.removeBlock(blockIndex);
	cout << "deleted\n";
}

void CommandHandler::removeAttributeFromBlock(const int& blockIndex, const myString& attrName)
{
	parser.removeBlockAttribute(blockIndex, attrName);
	cout << "deleted\n";
}

void CommandHandler::printAttributeFromSelector(const myString& selector, const myString& attrName)
{
	parser.getSelectorAttributeValue(selector, attrName).print();
	cout << "\n";
}
*/