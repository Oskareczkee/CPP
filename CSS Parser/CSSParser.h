#pragma once
#include "AttributeParser.h"
#include "SelectorParser.h"
#include "list.h"
#include "dLinkList.h"
//#include <vector>

class CSSBlock
{
public:
	struct CSSAttribute
	{
		myString name;
		myString value;

		//for remove attribute from block command, remove must have comparable type
		//that is why we write this operator, so css attribute becomes comparable by name
		bool operator==(const CSSAttribute& other)
		{
			return name == other.name;
		}
	};
	struct CSSSelector
	{
		myString name;
	};

	list<CSSSelector> selectors;
	list<CSSAttribute> attributes;
};

class CSSParser
{
	private:
		istream& stream;
		AttributeParser ap;
		SelectorParser sp;

		//endReadFlaf will be used in parser, to indicate whether it should end its work (end of stream or ???? token)
		bool endReadFlag = false;
		dlink_list<CSSBlock> blocks;

		//parsing utilities
		list<CSSBlock::CSSAttribute> parseAttributes();
		list<CSSBlock::CSSSelector> parseSelectors();
	public:
		CSSParser(istream& is): stream(is), ap(is), sp(is){}

		int blocksNumber(){	return blocks.getSize(); }
		int blockSelectorCount(const int& block);
		int getSelectorCount(const myString& selector);
		myString getBlockSelector(const int& blockIndex, const int& selectorIndex);
		int getBlockAttributesCount(const int& blockIndex);
		myString getBlockAttributeValue(const int& blockIndex, const myString& attrName);
		int getAttributeCount(const myString& attrName);
		bool removeBlock(const int& blockIndex){ return blocks.removeIndex(blockIndex); }
		bool removeBlockAttribute(const int& blockIndex, const myString& attrName);
		myString getSelectorAttributeValue(const myString& selector, const myString& attrName);

		void PrintContent()
		{
			for (auto node = blocks.first(); node != blocks.last(); node = node->getNext())
			{
				auto& selectors = node->getContent().selectors;
				auto& attributes = node->getContent().attributes;

				for (auto a = selectors.first(); a != selectors.last(); a = a->getNext())
				{
					auto content = a->getContent();
					content.name.print();
					cout << " ";
				}
				
				cout << "\n";

				for (auto a = attributes.first(); a != attributes.last(); a = a->getNext())
				{
					auto content = a->getContent();
					content.name.print();
					cout << ": ";
					content.value.print();
					cout << "\n";
				}
			}
		}
		void Parse();
};
