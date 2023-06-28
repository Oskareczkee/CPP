#pragma once
#include <iostream>
#include <vector>
#include <list>
#include <iterator>
#include <algorithm>
#include "Templates.h"
#include <random>
#include "CrackTimer.h"

using namespace std;


//task 5 done in Templates.h
//functions below do not provide range control
template <class T, class VAL = double>
	requires forward_iterator<T>
void increase(T begin, T end, VAL val)
{
	while (begin != end)
	{
		*begin += val;
		++begin;
	}
}

template<class Iter1, class Iter2>
	requires input_iterator<Iter1>&& input_or_output_iterator<Iter2>
Iter2 copy(Iter1 f1, Iter1 e1, Iter2 f2)
{
	if (f1 == e1)
		return f2;

	while (f1 != e1)
	{
		*f2 = *f1;
		++f2;
		++f1;
	}

	return f2;
}

template<class T>
	requires input_iterator<T>&& Excercise::Printable<T*>
void printContent(T begin, T end, ostream& os = cout)
{
	os << "{";
	while (begin != end)
	{
		os << *begin << " ";
		++begin;
	}
	os << "}";
}


void Test()
{
	const int arraylen = 9;

	int nums[] = { 1,2,3,4,5,6,7,8,9 };
	vector<int> vectornums{ 1,2,3,4,5,6,7,8,9};
	list<int>listnums{ 1,2,3,4,5,6,7,8,9 };

	int* numscpy = nums;
	vector<int>numsveccpy(vectornums);
	list<int>numslistcpy(listnums);

	increase(&nums[0], &nums[0] + arraylen, 2);
	cout << "\n";
	increase(vectornums.begin(), vectornums.end(), 3);
	cout << "\n";
	increase(listnums.begin(), listnums.end(), 5);
	cout << "\n";

	copy(&nums[0], &nums[0] + arraylen, vectornums.begin());;
	cout << "\n";
	copy(listnums.begin(), listnums.end(), &nums[0]);
	cout << "\n";

	cout << *find(vectornums.begin(), vectornums.end(), 3);
	cout << "\n";

	printContent(vectornums.begin(), vectornums.end());
	cout << "\n";
	printContent(listnums.begin(), listnums.end());
	cout << "\n";
	printContent(&nums[0], &nums[0] + arraylen);
}

//7
string findLast(vector<string>& vec)
{
	sort(vec.begin(), vec.end());
	return *(vec.end() - 1);
}

//11
vector<double> ListToVector(const list<int>& lst)
{
	vector<double> output;
	for (const int& i : lst)
	{
		output.push_back(static_cast<double>(i));
	}
	return output;
}


template<class Iter>
	requires input_iterator<Iter>
Iter High(Iter first, Iter second)
{
	Iter high = first;

	for (Iter p = first; p != second; ++p)
	{
		if (*high < *p)high = p;
	}
	return high;
}

//14
//only definition, with simple operations for test, and working iterator
template<class T>
class slist
{
public:
	class iterator;

	iterator begin() {return first;};
	iterator end() { return last; };

	iterator insert(iterator p, const T& v)
	{
		Node* temp = p->next;
		p->next = new Node{ temp, v };
	};

	//high cost of this operation for bigger lists
	//iterator erase(iterator p);

	void push_back(const T& elem)
	{
		if (!last && !first)
		{
			last = new Node{ nullptr, elem };
			first = last;
			return;
		}
			last->next = new Node{ nullptr, elem }; 
			last = last->next;
	};
	void push_front(const T& elem)
	{
		if (!last && !first)
		{
			last = new Node{ nullptr, elem };
			first = last;
			return;
		}
			Node* temp = first;
			first = new Node{ temp, elem };

	};
	void pop_front()
	{
		Node* next = first->next;
		delete first;
		first = next;
	};

	//high cost of this operation for bigger lists
	//not implemented due cost
	//void pop_back();

	T& front() { return first->val; };
	T& back() { return last->val; };

private:
	struct Node;

	Node* first=nullptr;
	Node* last=nullptr;

};

template<class T>
class slist<T>::iterator
{
	public:
		friend class slist;
		iterator(Node* n): current(n){}
		iterator& operator++() { current = current->next; return *this; }
		T& operator*() { return current->val; }
		bool operator==(const iterator& other) { return current == other.current; }
		bool operator!=(const iterator & other) { return current != other.current; }
	private:
		Node* current;
};

template<class T>
struct slist<T>::Node
{
	Node* next;
	T val;
};

//15
//simple vector, without iterators
template<class T>
class pvector
{
public:
	using size_type = vector<T*>::size_type;

	pvector(): elems(){}

	~pvector()
	{
		for (int x = 0; x < elems.size(); x++)
			delete elems[x];
	}

	void push_back(T* elem) { elems.push_back(elem); }
	T* operator[] (size_type i) { return elems[i]; }
	const T* operator[] (size_type i) const { return elems[i]; }

	size_type size() { return elems.size(); }
	size_type capacity() { return elems.capacity(); }

private:
	vector<T*> elems;
};

//16
//simple vector, without iterators
template<class T>
class ovector: public pvector<T>
{
public:
	using size_type = vector<T*>::size_type;
	T& operator[] (size_type i) { return *pvector::operator[](i); }
	const T& operator[] (size_type i) const { return *pvector::operator[](i); }
};


//17
//simple vector, without iterators
template<class T>
class ownership_vector
{
public:

	using size_type = long int;

	ownership_vector(): elems(), owned(){}

	void push_back(T* elem) { elems.push_back(elem); owned.push_back(elem); }
	void push_back(T& elem) { elems.push_back(&elem); }

	size_type number_of_owned() { return owned.size(); }
	size_type number_of_elems() { return elems.size(); }

	~ownership_vector()
	{
		for (int x = 0; x < owned.size(); x++)
			delete owned[x];
	}

private:
	vector<T*> elems;
	vector<T*> owned;
};

//18
//simple vector with random-access iterator
//this vector type just derives from original vector but has its own iterator
//i had no time to write whole new vector just for iterator
template<class T>
class Vector : public std::vector<T>
{
public:
	class Iterator;
	using size_type = vector<T>::size_type;
	using value_type = vector<T>::value_type;
	using pointer_type = vector<T>::pointer;
	using reference_type = vector<T>::reference;
	using const_reference_type = vector<T>::const_reference;


	Iterator begin() { return Iterator(&(*vector<T>::begin()), &(*vector<T>::begin()), &(*(vector<T>::end() - 1))); };
	Iterator end(){ return Iterator(&(*(vector<T>::end()-1)), &(*vector<T>::begin()), &(*(vector<T>::end() - 1))); }
};


//random-access iterator with range control
template<class T>
class Vector<T>::Iterator
{
public:
	Iterator(const Iterator& n) : current(n.current), begin(n.begin), end(n.end) {}
	Iterator() :current(nullptr), begin(nullptr), end(nullptr) {}
	Iterator(pointer_type curr, pointer_type beg, pointer_type e): current(curr), begin(beg), end(e){}


	bool operator <(const Iterator& other) { return current < other.current; }
	bool operator >=(const Iterator& other) { return !(*this < other); }
	bool operator >(const Iterator& other) { return current>other.current; }
	bool operator <=(const Iterator& other) { return !(*this > other); }

	Iterator& operator++()
	{
		if (current+1 == end)
			throw out_of_range("iterator::operator++: out of range");
		++current;
		return *this; 
	}
	Iterator& operator--()
	{
		if (current-1 < begin)
			throw out_of_range("iterator::operator--: out of range");
		--current;
		return *this; 
	}
	Iterator& operator+(int i)
	{
		if(current+i>end || current +i<begin)
			throw out_of_range("iterator::operator+: out of range");
		current += i;
		return *this;
	}

	Iterator& operator-(int i)
	{
		if (current - i >end || current - i < begin)
			throw out_of_range("iterator::operator-: out of range");
		current -= i;
		return *this;
	}

	int operator-(const Iterator& i)
	{
		return distance(i.current, this->current);
	}

	bool operator==(const Iterator& other) { return other.current == current; }
	bool operator!=(const Iterator& other) { return !(*this == other); }
	


	reference_type operator*()
	{
		if(current>end || current<begin)
			throw out_of_range("iterator::operator*: out of range");
		return *current; 
	}
	reference_type operator[](int i)
	{
		if(current+i>end || current+i<begin)
			throw out_of_range("iterator::operator[]: out of range");
		return *(current + i);
	}

	pointer_type operator->() const
	{
		return current;
	}
private:
	pointer_type current;
	pointer_type begin;
	pointer_type end;
};

int GenerateRandomInt(int left, int right)
{
	static random_device rd;
	static mt19937 mt(rd());
	uniform_real_distribution<double> dist(left, right);

	//generates double, casts to int
	return { static_cast<int>((dist(mt))) };
}

void BentleysExperiment(int n, int capacity)
{
	vector<int> vec;
	list<int> lst;

	CrackTimer timer1;

	timer1.StartTimer();

	for (int x = 0; x<capacity; x++)
	{
		vec.push_back(GenerateRandomInt(0, n));
		std::sort(vec.begin(), vec.end());
	}
	timer1.EndTimer();
	cout << "Vector:\n";

	for (int& x : vec)
		cout << x << " ";

	cout << "\n\nList:\n";
	CrackTimer timer2;

	timer2.StartTimer();
	for (int x = 0; x<capacity; x++)
	{
		lst.push_back(GenerateRandomInt(0, n));
		lst.sort();
	}

	timer2.EndTimer();
	for (int& x : lst)
		cout << x << " ";

	cout << "\n\n\n";
	cout << "Vector time: " << timer1.ShowTime(CrackTimer::TimeUnit::MILISECONDS)<<" ms\n";
	cout<< "List time: " << timer2.ShowTime(CrackTimer::TimeUnit::MILISECONDS)<<" ms";
}
