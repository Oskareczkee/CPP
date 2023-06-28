#pragma once

#include "CSSParser.h"
using Attribute = CSSBlock::CSSAttribute;
using Selector = CSSBlock::CSSSelector;

void CSSParser::Parse()
{
	//parse till endReadFlag is not set
	while (!endReadFlag)
	{
		auto selectors = parseSelectors();
		//load attributes
		auto attributes = parseAttributes();

		//this prevents pushing back empty blocks without selectors or attributes
		//changing && to || should accept blocks that may have selectors without attributes and vice versa
		if(attributes.getSize()!=0)
			blocks.push_back(CSSBlock{ selectors, attributes });
	}

	//reset flag after parsing
	endReadFlag = false;
}
//selectors.getSize()!=0
/*
* { name: value }, semicolon if value is not the last
*/
list<Attribute> CSSParser::parseAttributes()
{
	list<Attribute> attributes;
	Token t;
	t = ap.get();

	if (t.kind == (char)Tokens::INVALID || t.kind == (char)Tokens::ENDREAD)
	{
		endReadFlag = true;
		return list<Attribute>();
	}

	//check brackets
	if (t.kind != (char)AttributeTokens::BRACKETSBEGIN)
		throw exception("{ expected at the beginning of the block");

	//load values till the brackets end
	t = ap.get();
	while (t.kind != (char)AttributeTokens::BRACKETSEND)
	{
		Attribute attr;
		//load name
		if (t.kind != (char)AttributeTokens::NAMEORVALUE)
			throw exception("Expected name of the attribute");
		attr.name = t.val;
		t = ap.get();

		//check colon
		if (t.kind != (char)AttributeTokens::COLON)
			throw exception("Expected ':' after the name");
		t = ap.get();

		//load value
		if (t.kind != (char)AttributeTokens::NAMEORVALUE)
			throw exception("Expected value after name");
		attr.value = t.val;

		t = ap.get();

		//check for semicolon (if not, is there ending bracket at the end?)
		if (t.kind != (char)AttributeTokens::SEMICOLON)
		{
			t = ap.get();
			if (t.kind == (char)AttributeTokens::BRACKETSEND)
			{
				attributes.push_back(attr);
				return attributes;
			}
			else
				throw exception("Expected ';' or '}' at the end of attribute");
		}

		attributes.push_back(attr);
		t = ap.get();
	}

	return attributes;

}

//selector comma selector comma... up to the brackets
 list<Selector> CSSParser::parseSelectors()
{
	Token t;
	list<Selector> selectors;
	while (true)
	{
		//get token
		t = sp.get();

		//if it is a selector, add to the selector list
		if (t.kind == (char)SelectorTokens::SELECTOR)
			selectors.push_back(Selector{ t.val });
		//ignore commas
		else if (t.kind == (char)SelectorTokens::COMMA)
			continue;
		//if bracketsbegin, then selectors have been loaded
		else if (t.kind == (char)SelectorTokens::BRACKETSBEGIN)
			break;
		//if t is other kind than these selectors, break, we dont know what happened, maybe EOF? or some other stuff
		else
			break;
	}

	return selectors;
}

 /*
 
	FUNCTIONS FOR COMMAND HANDLER
 
 */

 int CSSParser::getSelectorCount(const myString& selector)
 {
	 int count = 0;
	 for (auto node = blocks.first(); node != blocks.last(); node = node->getNext())
	 {
		 auto& selectors = node->getContent().selectors;
		 for (auto a = selectors.first(); a != selectors.last(); a = a->getNext())
		 {
			 auto content = a->getContent();
			 if (content.name == selector)
				 count++;
		 }
	 }

	 return count;
 }

 int CSSParser::blockSelectorCount(const int& blockIndex)
 {
	 auto block = blocks.atIndex(blockIndex);
	 //if block at given index exists
	 if (block)
		 return block->getContent().selectors.getSize();
	 else
		 //otherwise return 0, block does not exist
		 return 0;
 }

 myString CSSParser::getBlockSelector(const int& blockIndex, const int& selectorIndex)
 {
	 auto block = blocks.atIndex(blockIndex);
	 
	 //if blocks exists
	 if (block)
	 {
		 //dont change these lines i had problems with them
		 auto& selectors = block->getContent().selectors;
		 auto selector = selectors.atIndex(selectorIndex);
		 //if selector exists return its name
		 if (selector)
			 return selector->getContent().name;
		 else
			 //if selector does not exist return empty string
			 return myString("");
	 }
	 //else return empty string
	 else
		 return myString("");
 }

 int CSSParser::getBlockAttributesCount(const int& blockIndex)
 {
	 auto block = blocks.atIndex(blockIndex);

	 if (block!=nullptr)
	 {
		 auto& attrs = block->getContent().attributes;
		 attrs.removeDuplicates();
		 //remove duplicates
		 return attrs.getSize();
	 }
	 else
		 return -1;
 }

 myString CSSParser::getBlockAttributeValue(const int& blockIndex, const myString& attrName)
 {
	 auto block = blocks.atIndex(blockIndex);

	 if (block)
	 {
		 auto& attributes = block->getContent().attributes;
		 myString lastOccurence = "";

		 for (auto a = attributes.first(); a != attributes.last(); a = a->getNext())
		 {
			 if (a->getContent().name == attrName)
				 lastOccurence = a->getContent().value;
		 }

		 return lastOccurence;
	 }
	 else
		 return myString("");
 }

 //duplicates has are being removed
int CSSParser::getAttributeCount(const myString& attrName)
{
	if (blocks.getSize() == 0)
		return 0;

	int count = 0;

	for (auto node = blocks.first(); node != blocks.last(); node = node->getNext())
	{
		auto& attributes = node->getContent().attributes;
		attributes.removeDuplicates();
		for (auto a = attributes.first(); a != attributes.last(); a = a->getNext())
		{
			auto content = a->getContent();
			if (content.name == attrName)
				count++;
		}
	}

	return count;
}

bool CSSParser::removeBlockAttribute(const int& blockIndex, const myString& attrName)
{
	auto blockPtr = blocks.atIndex(blockIndex);
	//if block does not exist
	if (!blockPtr)
		return false;
	auto& block = blockPtr->getContent();
	bool result = block.attributes.remove(CSSBlock::CSSAttribute{ attrName });

	if (!result)
		return result;

	if (block.attributes.getSize() == 0)
		removeBlock(blockIndex);

	return result;
}

myString CSSParser::getSelectorAttributeValue(const myString& selector, const myString& attrName)
{
	CSSBlock block;

	//helper bool, sets to true if selector was found
	bool found = false;

	//iterate loop backwards, first selector from backwards is pretty much the last we are looking for
	//we use lastTail insted of last, because last returns last element, which is always nullptr, and without proper iterator cannot be used
	//we iterate backwards, till a is not nullptr
	for (auto a = blocks.lastTail(); a !=nullptr; a = a->getPrev())
	{
		//loop through selectors of block
		auto& selectors = a->getContent().selectors;
		for (auto x = selectors.first(); x != selectors.last(); x = x->getNext())
		{
			//proper node has been found
			if (x->getContent().name == selector)
			{
				block = a->getContent();
				found = true;
				break;
			}
		}

		//leave this loop if selector has been already found
		if (found)
			break;
	}

	//if no proper block has been found, return empty string
	if (!found)
		return "";

	auto& attributes = block.attributes;

	//look for attribute in that block
	for (auto x = attributes.first(); x != attributes.last(); x = x->getNext())
	{
		if (x->getContent().name == attrName)
			return x->getContent().value;
	}

	//attribute has not been found, return empty string
	return "";
	
}