#pragma once
#include <stdexcept>

template <class T>
class vector {
private:
	const static int INITIAL_SIZE = 100000;
	T* _arr = nullptr;

	int _capacity = 0; //capacity of the whole vector
	int _size = 0;     //number of elements stored

	void resize();
public:
	vector(): _arr(new T[INITIAL_SIZE]), _capacity(INITIAL_SIZE){}
	vector(const int& capacity): _arr(new T[capacity]), _capacity(capacity){}
	~vector();

	void push_back(T val);
	void pop_back(); //delete last element
	void pop_back(const T& val); //find and delete element, does nothing if element does not exist
	void clear(); //clears all values, sets size to 0

	int get_size() { return _size; }
	int get_capacity() { return _capacity; }

	T& operator[](const int& idx);
};

template<class T>
inline void vector<T>::resize()
{
	T* copy = new T[_size];
	for (int x = 0; x < _size; x++)
		copy[x] = _arr[x];

	delete[] _arr;
	_capacity *= 2; //double the capacity

	_arr = new T[_capacity];
	for (int x = 0; x < _size; x++)
		_arr[x] = copy[x];

	delete[] copy;
}

template<class T>
inline vector<T>::~vector()
{
	delete[] _arr;
}

template<class T>
inline void vector<T>::push_back(T val)
{
	if (_size + 1  >= _capacity)
		resize();

	_arr[_size++] = val;
}

template<class T>
inline void vector<T>::pop_back()
{
	_size--;
}

template<class T>
inline void vector<T>::pop_back(const T& val)
{
	//find the value
	for (int x = 0; x < _size; x++)
	{
		if (_arr[x] == val) {

			//shift array by -1 index
			for (int y = x; y < _size - 1; y++)
				_arr[y] = _arr[y + 1];
			_size--;

			return;
		}
	}
}

template<class T>
inline void vector<T>::clear()
{
	_size = 0;
}

template<class T>
inline T& vector<T>::operator[](const int& idx)
{
	if (idx > _size)
		throw std::out_of_range("vector index is out of range");

	return _arr[idx];
}
