#pragma once

/// <summary>
/// Minimum implementation of matrix used for graphs algorithms
/// Includes multiplication and calculation of trace
/// </summary>
/// <typeparam name="T"></typeparam>
template<class T = int>
class Matrix {
private:
	T** _matrix = nullptr;
	int _width=0, _height = 0;

	void create_matrix();
	void delete_matrix();
	void copy(const Matrix& other);

public:
	Matrix():_width(0), _height(0), _matrix(nullptr){}
	Matrix(const int& width, const int& height) : _width(width), _height(height) { create_matrix();}
	Matrix(const Matrix& other);
	~Matrix() { delete_matrix(); }

	/*multiplication  of matrix*/
	Matrix<T> operator*(const Matrix& other) const;
	T* operator[](const int& index);
	Matrix<T>& operator=(const Matrix& other);
	/*calculates trace of matrix (sum of products on main diagonal). Trace can be calculated only for square matrices*/
	T trace() const;/*calculates trace of matrix (sum of products on main diagonal). Trace can be calculated only for square matrices*/
	void fill(const T& val);	/*fills matrix with given value*/
};

template<class T>
inline Matrix<T>::Matrix(const Matrix& other)
{
	_width = other._width;
	_height = other._height;

	create_matrix();
	copy(other);
}

template<class T>
Matrix<T> Matrix<T>::operator*(const Matrix& other) const
{
	//multiplication is only allowed for matrices with the same row count
	if (_width != other._height)
		return Matrix<T>();

	Matrix<T> output(_width, other._height);


	int row = 0, col = 0;

	for (int x = 0; x < other._height; x++)
	{
		for (int y = 0; y < _width; y++)
		{
			int add = 0;
			for (int z = 0; z < other._height; z++)
				add += _matrix[x][z] * other._matrix[y][z];
			output[x][y] = add;
		}

	}

	return output;
}

template<class T>
T* Matrix<T>::operator[](const int& index)
{
	return _matrix[index];
}

template<class T>
inline T Matrix<T>::trace() const
{
	if (_width != _height)
		return T();
	
	T out = T();
	for (int x = 0; x < _height; x++)
		out += _matrix[x][x];
	return out;
}

template<class T>
Matrix<T>& Matrix<T>::operator=(const Matrix& other)
{
	//self assignemnt guard
	if (this == &other)
		return *this;

	delete_matrix();

	_width = other._width;
	_height = other._height;

	create_matrix();
	copy(other);
}

template<class T>
inline void Matrix<T>::fill(const T& val)
{
	if (_matrix == nullptr)
		return;

	for (int x = 0; x < _height; x++) {
		for (int y = 0; y < _width; y++)
			_matrix[x][y] = val;
	}
}

template<class T>
inline void Matrix<T>::create_matrix()
{
	if (_matrix != nullptr)
		delete_matrix();

	_matrix = new T * [_height];
	for (int x = 0; x < _height; x++)
		_matrix[x] = new T[_width];
}

template<class T>
inline void Matrix<T>::delete_matrix()
{
	if (_matrix == nullptr)
		return;

	for (int x = 0; x < _height; x++)
		delete[] _matrix[x];

	delete[] _matrix;
}

template<class T>
inline void Matrix<T>::copy(const Matrix& other)
{
	for (int x = 0; x < _height; x++)
		for (int y = 0; y < _width; y++)
			_matrix[x][y] = other._matrix[x][y];
}
