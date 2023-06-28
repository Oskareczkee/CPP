#pragma once
#include <iostream>
#include <functional>
#include <random>
#include <chrono>
#include "Matrix.h"

using namespace Numeric_lib;

//12


//4,5
//this code has been copied, this is original code from book, nothing has been changed in it
namespace GaussElimination
{
	class Elim_failure : public std::runtime_error
	{
	public:
		Elim_failure(std::string msg): std::runtime_error(msg), what_msg(msg){}

		virtual const char* what() const throw() override
		{
			return what_msg.c_str();
		}
	private:
		string what_msg;
	};

	//-----------------------------------------------------------------------------

	class Back_subst_failure : public std::runtime_error
	{
	public:
		Back_subst_failure(std::string msg): std::runtime_error(msg), what_msg(msg){}

		virtual const char* what() const throw() override
		{
			return what_msg.c_str();
		}

	private:
		std::string what_msg;
	};

	//-----------------------------------------------------------------------------

	typedef Numeric_lib::Matrix<double, 2> Matrix;
	typedef Numeric_lib::Matrix<double, 1> Vector;

	//-----------------------------------------------------------------------------

	/*
		Converts A to upper triangular matrix,
		modifying b as necessary.
		Otherwise throws exception reflecting inability
		to convert A to upper triangular.
	*/
	void classical_elimination(Matrix& A, Vector& b)
	{
		const Numeric_lib::Index n = A.dim1();

		for (Numeric_lib::Index j = 0; j < n - 1; ++j)
		{
			// scale every element of the current row by the main-diagonal-element
			const double pivot = A(j, j);

			if (pivot == 0)	// zero element on the main diagonal
			{
				std::stringstream ss;
				ss <<"Exception::Classical elimination at: "<< j;
				throw Elim_failure(ss.str());
			}

			for (Numeric_lib::Index i = j + 1; i < n; ++i)
			{
				const double multiplier = A(i, j) / pivot;

				A[i].slice(j) = scale_and_add(A[j].slice(j), -multiplier, A[i].slice(j));

				b[i] = multiplier * b[j];
			}
		}
	}

	//-----------------------------------------------------------------------------
	Vector back_substitution(Matrix& A, Vector& b)
	{
		const Numeric_lib::Index n = A.dim1();
		Vector x(n);

		for (Numeric_lib::Index i = n - 1; i >= 0; --i)
		{
			double s = b(i) - dot_product(A[i].slice(i + 1), x.slice(i + 1));

			if (double m = A(i, i))
			{
				x(i) = s / m;
			}
			else	// zero or infinite number of solutions
			{
				std::stringstream ss;
				ss <<"Exception::Back substitution at i: "<< i;
				throw Back_subst_failure(ss.str());
			}
		}

		return x;
	}

	//-----------------------------------------------------------------------------

	//this has been as well copied, this is original code from book
	void elim_with_partial_pivot(Matrix& A, Vector& b)
	{
		const Index n = A.dim1();

		for (Index j = 0; j < n; ++j)
		{
			Index pivot_row = j;

			// find largest magnitude element in current column 
			for (Index k = j + 1; j < n; ++k)
			{
				if (abs(A(k, j)) > abs(A(pivot_row, j)))
					pivot_row = j;

				// place new pivot on main diagonal
				if (pivot_row != j)
				{
					A.swap_rows(j, pivot_row);
					// reflect row changes in rhs
					std::swap(b(j), b(pivot_row));
				}

				// proceed with elimination from j + 1 and on
				for (Numeric_lib::Index i = j + 1; i < n; ++i)
				{
					const double pivot = A(j, j);
					if (pivot == 0)
					{
						stringstream ss;
						ss <<"Exception::Eliminate with partial pivot at j: "<< j;
						throw Elim_failure(ss.str());
					}

					const double multiplier = A(i, j) / pivot;
					A[i].slice(j) = scale_and_add(A[j].slice(j), -multiplier, A[i].slice(j));
					b(i) -= multiplier * b(j);
				}
			}
		}
	}
	//-----------------------------------------------------------------------------

	Vector classical_gaussian_elimination(Matrix& A, Vector& b)
	{
		classical_elimination(A, b);
		//elim_with_partial_pivot(A, b);
		return back_substitution(A, b);
	}
}

//1
/*
   "Freestanding" function:
   Does not modify the input parameter.
   The, copy of, the result is meant to be
   used as an initialization value.
*/
int triple(int src) { return src*3; }

/*
	"Broadcast" function:
	Modifies the input parameter.
	The result is the modified input parameter,
	i.e. an already existing value.
*/
int one(int& src) { return src += 1;}
int tripleRef(int& src) { return src *= 3; }

//2
template<class T> struct Triple
{T operator()(T& a) { return a *= 3; }};

//3 I literally don't know what to do in this task


void MatTest()
{
	Matrix<int, 1> mat(5);

	mat.apply(one);
	//freestanding function use
	mat=apply(triple,mat);
	//broadcast function use
	mat.apply(tripleRef);
	mat = apply(Triple<int>(), mat);
	mat.apply(Triple<int>());

	cout << mat[0];
}

//10
void default_random_enigne_check(int rightlim, int amount)
{
	static default_random_engine eng;
	eng.seed({ (unsigned int)chrono::system_clock::now().time_since_epoch().count() });
	static uniform_int_distribution<> dist(1, rightlim);

	for (int x = 0; x < amount; x++)
	{
		int randNum = dist(eng);
		for (int x = 0; x < randNum;++x)
			cout << "*";
		cout << "\n";
	}
}

//11
template<class T, size_t N>
void swap_columns2D(Matrix<T, N>& matrix, Index i, Index j)
{
	if (i == j) return;

	Index size = matrix.dim1();

	for (Index r = 0; r < size; ++r)
		swap(matrix[r][i], matrix[r][j]);
}

//11
template<class T, size_t N>
void swap_columns3D(Matrix<T, N>& matrix, Index i, Index j)
{
	if (i == j) return;

	Index size = matrix.dim3();

	for (Index r = 0; r < size; ++r)
		swap_columns2D(matrix[r], i, j);
}


Matrix<double> operator*(Matrix<double,2>& matrix, Matrix<double> mult)
{
	Index vec_size = mult.size();

	if (vec_size != matrix.dim1())
		throw exception("Matrix multiplication: matrix size and vector sizes are different!");

	Matrix<double> output(vec_size);

	for (Index i = 0; i < vec_size; ++i)
		output[i] = dot_product(matrix[i], mult);

	return output;
}

template<size_t N>
Matrix<double, N> operator+(Matrix<double, N>& mat1, Matrix<double, N>& mat2)
{
	Index size = mat2.size();

	if (mat1.size() != size)
		throw exception("Matrix addition: matrix sizes are different!");

	Matrix<double, N> output = mat1;

	double* data = mat2.data();
	double* accum = output.data();

	for (Index x = 0; x < size; x++)
		accum[x] += data[x];

	return output;
}
