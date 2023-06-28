#pragma once
#include "CSSParser.h"
/*
* basic command handler designed to handle commands for css parser
* basically it uses parser commands to get data we're looking for
*/

class CommandHandler
{
	private:
		CSSParser parser;
	public:
		//parses command to usefull format
		CommandHandler(CSSParser& _parser): parser(_parser){}

		void GetCommand();
		
		//COMMAND HANDLERS
		//depricated due to strict output requirements
		/*
		void printBlocksNum();
		void printSelectorCount(const myString& selector);
		void printSelectorCountForBlock(const int& blockIndex);
		void printSelectorForBlock(const int& blockIndex, const int& selectorIndex);
		void printBlockAttributes(const int& blockIndex);
		void printBlockAttributeValue(const int& blockIndex, const myString& attrName);
		void printAttributeOccurrenceCount(const myString& attrName);
		void removeBlock(const int& blockIndex);
		void removeAttributeFromBlock(const int& blockIndex, const myString& attrName);
		void printAttributeFromSelector(const myString& selector, const myString& attrName);
		*/
};
