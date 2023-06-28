#pragma once
#define TEMPLATES
#include <vector>
#include <algorithm>

using namespace std;

template<typename T>
T Sum_Vector(vector<T> Vector)
{
   T Sum=NULL;

   for (typename vector<T>::iterator itr = Vector.begin(); itr != Vector.end(); ++itr)
      Sum+= *itr;

   return Sum;
}

template<class VectorT, class VarT>
bool FindInVector(const vector<VectorT> &Vector, const VarT &value)
{
   //compilator returns error when both types are incomparable with each other
	for (typename vector<VectorT>::const_iterator itr = Vector.begin(); itr != Vector.end(); ++itr)
	{
		if (*itr == value)
			return true;
	}
	return false;
}

template<class T>
void SortVector(vector<T>& Vector)
{
	sort(Vector.begin(), Vector.end(), [](const T& a, const T& b){return a > b; });
}



template<typename T> class Vector
{
public:
	Vector();
	Vector(unsigned int length);
	~Vector();
	Vector(const Vector& other);
	T getValue(unsigned int index);
	bool setValue(unsigned int index, T value);//returns true if everything went ok
	bool push_back(T value);
	Vector* get_new_node_ptr(T value);
	int length() { return elementCount; };

	Vector& operator= (const Vector& other);

private:
	T value;
	static unsigned int elementCount;
	//I forgot to add head, so its implementation was a bit trickier, but it works like normal vector
	Vector* next;
	Vector(T value, bool create_node = false);//i had to added this bool, otherwise this constructor could be received as constructor with lenght
};

template<typename T> unsigned int Vector<T>::elementCount = 0;

template<typename T> Vector<T>::Vector()
{

}
template<typename T> Vector<T>::Vector(unsigned int length)
{
	while (elementCount <= length)
	{
		value = NULL;
		elementCount++;
		next = new Vector();
	}
}
template<typename T> Vector<T>::Vector(T value, bool create_node)
{
	if (!create_node)
	{
		delete this;
		return;
	}
	this->value = value;
	this->next = NULL;
}

template<typename T> Vector<T>::~Vector()
{
	delete next;
}

template<typename T> Vector<T>::Vector(const Vector<T>& other)
{
	Vector* temp = other.next;

	value = other.value;
	elementCount = 0;

	while (temp != NULL)
	{
		push_back(temp->value);
		temp = temp->next;
	}
}

template<typename T> Vector<T>& Vector<T>::operator=(const Vector& other)
{
	if (this == &other)
		return *this;
	delete next;
	next = NULL;

	Vector* temp = other.next;

	this->value = other.value;
	this->elementCount = 0;

	while (temp != NULL)
	{
		push_back(temp->value);
		temp = temp->next;
	}
	return *this;
}

template<typename T> Vector<T>* Vector<T>::get_new_node_ptr(T value)
{
	Vector* temp = new Vector(value, true);
	return temp;
}


template<typename T> T Vector<T>::getValue(unsigned int index)
{
	int actualIndex = 0;
	Vector* temp = this;

	while (actualIndex != index)
	{
		temp = temp->next;
		actualIndex++;
		if (actualIndex > elementCount)
			return NULL;
	}
	return temp->value;
}

template<typename T> bool Vector<T>::setValue(unsigned int index, T value)
{
	if (index > elementCount)
		return false;

	int actualIndex = 0;

	Vector* temp = this;

	while (actualIndex != index)
	{
		actualIndex++;
		temp = temp->next;
	}
	temp->value = value;
	return true;
}

template<typename T> bool Vector<T>::push_back(T value)
{
	Vector* temp = this;

	while (temp->next != NULL)
	{
		temp = temp->next;
	}
	temp->next = get_new_node_ptr(value);
	this->elementCount++;
	return true;
}