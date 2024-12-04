#pragma once

/// <summary>
/// Simple implementation of list-based queue used in vertex_eccentrity algorithm
/// </summary>
template<class T>
class Queue {
private:
	struct list_node {
		T val;
		list_node* next, * prev;
		list_node(list_node* n, list_node* p, const T& v) : next(n), prev(p), val(v){}
	};

	list_node* head, * tail;
	int _size = 0;

	void add_first(const T& val);
	void delete_first();

public:
	Queue():_size(0), head(nullptr), tail(nullptr){}
	~Queue();

	bool empty() { return _size == 0; }


	void push(const T& val);
	void pop();
	T& front();
	T& back();
};

template<class T>
inline void Queue<T>::add_first(const T& val)
{
	head = new list_node(nullptr, nullptr, val);
	tail = head;
}

template<class T>
inline void Queue<T>::delete_first()
{
	delete head;
	head = tail = nullptr;
}

template<class T>
inline Queue<T>::~Queue()
{
	while (_size > 0)
		pop();
}

template<class T>
inline void Queue<T>::push(const T& val)
{
	if (_size == 0) {
		add_first(val);
		_size++;
		return;
	}

	tail->next = new list_node(nullptr, tail, val);
	tail = tail->next;
	_size++;
}

template<class T>
inline void Queue<T>::pop()
{
	if (_size == 0) return;
	else if (_size == 1) {
		delete_first();
		_size--;
		return;
	}

	list_node* new_head = head->next;
	delete head;
	head = new_head;
	head->prev = nullptr;
	_size--;
}

template<class T>
inline T& Queue<T>::front()
{
	return head->val;
}

template<class T>
inline T& Queue<T>::back()
{
	return tail->val;
}
