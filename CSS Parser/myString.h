#pragma once
#include "list.h"

class myString : public list<char>
{
private:
public:

	myString& operator+=(const char& ch)
	{
		this->push_back(ch);
		return *this;
	}

	//base construcotor - string with no content
	myString(){}

	//constructor that creates myString from char array (string)
	myString(const char* str)
	{
		while (*str)
			this->push_back(*str++);
	}

	bool operator==(const myString& other)
	{
		ListNode* node = beg;
		ListNode* otherNode = other.beg;

		//string are not the same size, and cannot be the same
		if (this->size != other.size)
			return false;

		//check is every letter is the same
		while (node)
		{
			if (otherNode->getContent() == node->getContent())
			{
				node = node->getNext();
				otherNode = otherNode->getNext();
			}
			else
				return false;
		}

		//all test have been passed
		return true;
	}

	bool operator!=(const myString& other)
	{
		return !(*this == other);
	}

	//function that prints to the cout, stream can be change as well to file stream
	//this is due the lack of iterator implementation
	//if I had implemented iterator, i would override ostream operator<<
	void print(std::ostream& os = std::cout)
	{
		ListNode* node = beg;
		while (node)
		{
			os << node->getContent();
			node = node->getNext();
		}
	}
};