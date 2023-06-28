#pragma once
#include <iostream>

using namespace std;


void to_lower(char* s)
{
	if (!s)
		throw exception("pointer to s has not been inicialized or is nullptr");

	int x = 0;
	do
	{
		if (isupper(s[x]))
			s[x] = tolower(s[x]);
		x++;
	} while (s[x] != 0);
}

void stack_check()
{
	int* x1 = new int(2);
	int* x2 = new int(3);
	int* x3 = new int(3);
	int* x4 = new int(4);

	cout << x1 << "  " << x2<<"\n";
	cout << x3 << "  " << x4 << "\n";

	delete x4;
	delete x3;

	int* x5 = new int(3);
	int* x6 = nullptr;

	//x3 and x4 gives in this case warning, cause they are deleted and uninitalized
	cout <<"\n\n"<< x5<<"   "<<x3<<"   "<<x4<<"   "<<x6;
}




//simple list, just to test pointers, it has no practical functionalities, just a test
template <class T>
class List
{
public:
	class Node
	{
	public:
		T content;
		Node(Node* left, Node* right, T Content) : Left(left), Right(right), content(Content) {};
		Node() : Left(nullptr), Right(nullptr), content(0) {};
	private:
		friend class List;
		Node* Left;
		Node* Right;
	};

	//adds at the end
	void add(T content)
	{
		if (!Root)
		{
			Root= new Node(nullptr, nullptr, content);
			size++;
			return;
		}

		Node* temp = Root;
		while (temp->Right)
		{
			temp = temp->Right;
		}

		temp->Right = new Node(temp, nullptr, content);
		size++;
	}

	Node* GetContent(int place)
	{
		if (place >= size)
			throw exception("Place is out of index !");

		Node* temp = Root;
		for (int x = 0; x <= place; x++)
		{
			temp = temp->Right;
		}

		return temp;
	}

	int get_size()const { return size; }

private:
	Node* Root;
	int size = 0;
};