#pragma once
#include <iostream>

//the implementation is pretty much the same as normal list
//optimized operations for double links

template <class Type>
class dlink_list
{
protected:
	//list node does not have destructor, list is responsible for destruction
	//that's why node is private, so no one can create its instance
	class ListNode
	{
		friend class dlink_list;
	protected:
		Type content;
		ListNode* next;
		ListNode* prev;
		ListNode(const Type& _content) : content(_content), next(nullptr) {}
		ListNode(const Type& _content, ListNode* _prev) : content(_content), prev(_prev) {}
		ListNode(const Type& _content, ListNode* _prev, ListNode* _next) : content(_content), prev(_prev), next(_next) {}
	public:
		ListNode* getNext() { return next; }
		ListNode* getPrev() { return prev; }
		Type& getContent() { return content; }
		void setContent(const Type& _content) { content = _content; }
	};

	ListNode* beg = nullptr;
	ListNode* tail = nullptr;
	int size = 0;
public:
	dlink_list() {}


	//copy constructor
	dlink_list(const dlink_list& other)
	{
		ListNode* node = other.beg;
		while (node)
		{
			push_back(node->content);
			node = node->getNext();
		}
	}

	//asign operator
	dlink_list& operator=(const dlink_list& other)
	{
		//self assignment guard
		if (this == &other)
			return *this;


		//clear and copy
		this->erase();

		ListNode* node = other.beg;

		while (node)
		{
			this->push_back(node->getContent());
			node = node->getNext();
		}

		return *this;
	}

	ListNode* push_back(const Type& t)
	{
		if (beg == nullptr)
		{
			beg = new ListNode(t, nullptr, nullptr);
			tail = beg;
			size++;
			return beg;
		}

		ListNode* newNode = new ListNode(t, tail, nullptr);
		tail->next = newNode;
		tail = newNode;

		size++;
		return newNode;
	}

	void pop_back()
	{
		ListNode* back = tail;
		ListNode* prev = tail->prev;
		delete back;
		tail = prev;
		tail->next = nullptr;
		size--;
		return;
	}

	//this function will accept only comparable types
	//returns true if could find object and remove it, false if not
	bool remove(const Type& type)
	{
		ListNode* actual = beg;
		ListNode* next = beg->getNext();
		ListNode* prev = nullptr;

		while (actual)
		{
			//we found what we were looking for
			if (actual->getContent() == type)
			{
				//the node we want to remove is beginning node
				if (prev == nullptr)
				{
					delete actual;
					beg = next;
					beg->prev = nullptr;
					size--;
					return true;
				}
				//the end node
				else if (actual == tail)
				{
					delete actual;
					tail = prev;
					prev->next = nullptr;
					size--;
					return true;
				}

				//somewhere in the middle
				else
				{
					delete actual;
					prev->next = next;
					next->prev = prev;
					size--;
					return true;
				}
			}

			prev = actual;
			actual = actual->getNext();
			next = actual->getNext();
		}
	}

	//optimized for double link list
	//will search for index from the end if index is higher than size/2
	//returns true if element was removed, false if not
	bool removeIndex(const unsigned int& index)
	{
		if (index >= size || beg==nullptr)
			return false;

		//end node
		if (index == size)
		{
			ListNode* ln = tail;
			ListNode* prev = tail->prev;
			tail = prev;
			prev->next = nullptr;
			delete ln;
			size--;
			return true;
		}

		//beg node
		else if (index == 0)
		{
			ListNode* ln = beg;
			ListNode* next = beg->next;
			delete ln;
			if (!next)
			{
				beg = nullptr;
				tail = nullptr;
				size--;
				return true;
			}

			beg = next;
			next->prev = nullptr;

			size--;
			return true;
		}

		//from the end
		/*
		if (index > size / 2)
		{
			ListNode* node = tail;
			
			for (int x = size; x > index; x--)
				node = node->prev;

			ListNode* next = node->next;
			ListNode* prev = node->prev;
			delete node;
			if (prev != nullptr)
				prev->next = next;
			if (next != nullptr)
				next->prev = prev;
			size--;
			return true;
		}
		*/
			ListNode* node = beg;
			for (int x = 0; node!=nullptr && x < index; x++)
				node = node->next;

			if (node == nullptr)
				return false;

			ListNode* next = node->next;
			ListNode* prev = node->prev;
			delete node;
			if(prev!=nullptr)
				prev->next = next;
			if(next!=nullptr)
				next->prev = prev;
			size--;
			return true;

		return false;
	}

	int getSize() { return size; }

	//usefull for iteration without proper iterators implemented
	ListNode* first() { return beg; }
	ListNode* last() { return nullptr; }
	//returns tail of the list, usefull for iterating backwards
	ListNode* lastTail() { return tail; }
	//this function has been optimized, when index in closer to the end we iterate from the back
	ListNode* atIndex(const int& index)
	{

		//out of range element
		if (index >= size || beg==nullptr || index<0)
			return nullptr;

		/*
		//iterate from end
		if (index > size / 2)
		{
			ListNode* elem = tail;
			for (int x = size; x >= index; x++)
				elem = elem->prev;
			return elem;
		}
		*/
		//iterate from beggining
			ListNode* elem = beg;
			for (int x = 0; elem!=nullptr && x < index; x++)
				elem = elem->next;

			return elem;
	}


	//erases all the content from the list, works like destructror, but does not delete object itself
	void erase()
	{
		ListNode* currentNode = beg;
		while (currentNode)
		{
			ListNode* next = currentNode->getNext();
			delete currentNode;
			currentNode = next;
		}

		beg = nullptr;
		tail = nullptr;
	}

	//destructor destroys list until it has no nodes left
	~dlink_list()
	{
		if (beg == nullptr)
			return;

		ListNode* currentNode = beg;


		while (currentNode)
		{
			ListNode* next = currentNode->getNext();

			if (next != nullptr)
				delete currentNode;
			currentNode = next;
		}
	}
};