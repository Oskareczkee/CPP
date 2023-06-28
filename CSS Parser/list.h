#pragma once

template <class Type>
class list
{
protected:
	//list node does not have destructor, list is responsible for destruction
	//that's why node is private, so no one can create its instance
	class ListNode
	{
		friend class list;
		protected:
			Type content;
			ListNode* next;
			ListNode(const Type& _content): content(_content), next(nullptr){}
			ListNode(const Type& _content, ListNode* _next): content(_content), next(_next){}
		public:
			ListNode* getNext(){ return next; }
			Type getContent() { return content; }
			void setContent(const Type& _content) { content = _content; }
	};

	ListNode* beg=nullptr;
	ListNode* tail=nullptr;
	int size = 0;
public:
	list(){}

	//copy constructor
	list(const list& other)
	{
		ListNode* node = other.beg;
		while (node)
		{
			push_back(node->content);
			node = node->getNext();
		}
	}

	//assign operator
	list& operator=(const list& other)
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
			beg = new ListNode(t);
			tail = beg;
			size++;
			return beg;
		}

		ListNode* newNode = new ListNode(t);
		tail->next = newNode;
		tail = newNode;

		size++;
		return newNode;
	}

	//this function will accept only comparable types
	//returns true if could  find and remove object, false if not
	bool remove(const Type& type)
	{
		if (beg==nullptr)
			return false;

		ListNode* actual = beg;
		ListNode* next = beg->getNext();
		ListNode* prev = nullptr;

		while (actual)
		{
			//we found what we were looking for
			if (actual->getContent() == type)
			{
				//the node we want to remove is beginning node
				if (actual==beg)
				{
					delete actual;
					beg = next;
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
					size--;
					return true;
				}
			}

			prev = actual;
			actual = actual->getNext();
			//if actual will be nullptr, exception will be thrown, this prevents this
			if (actual)
				next = actual->getNext();
		}

		//object has not been found
		return false;
	}

	int getSize() { return size; }

	//usefull for iteration without proper iterators implemented
	ListNode* first() { return beg; }
	ListNode* last() { return nullptr; }
	//returns tail of list, usefull for iterating backwards
	ListNode* lastTail() { return tail; }
	//gets element at index, indexing starts from 0
	ListNode* atIndex(const int& index)
	{
		ListNode* elem = beg;

		//out of range element
		if (index >= size)
			return nullptr;

		for (int x = 0; x < index; x++)
			elem = elem->next;

		return elem;
	}

	void removeDuplicates()
	{
		list<ListNode*> toRemove;
		for (ListNode* elem = first(); elem != last(); elem = elem->getNext())
		{
			auto content = elem->getContent();
			for (ListNode* x = elem->getNext(); x != last(); x=x->getNext())
			{
				if (content == x->getContent())
					toRemove.push_back(x);
			}
		}

		//no elements to remove
		if (toRemove.getSize() == 0)
			return;

		for (ListNode* elem = toRemove.first()->getContent(); elem != last(); elem = elem->getNext())
			remove(elem->getContent());
	}


	//erases all the content from the list, works like destructror, but does not delete object itself
	void erase()
	{
		ListNode* currentNode = beg;

		//list is already empty
		if (currentNode == nullptr)
			return;

		while (currentNode)
		{
			ListNode* next = currentNode->getNext();
			delete currentNode;
			currentNode = next;
		}

		beg = nullptr;
		tail = nullptr;
		size = 0;
	}

	//destructor destroys list until it has no nodes left
	~list()
	{
		if (beg == nullptr)
			return;

		ListNode* currentNode = beg;

		while (currentNode!=nullptr)
		{
			ListNode* next = currentNode->getNext();

			if(next!=nullptr)
				delete currentNode;
			currentNode = next;
		}
	}
};