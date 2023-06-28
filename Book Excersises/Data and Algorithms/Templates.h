#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

//to keep overloaded vector operators in isolation... Brrr
namespace Excercise
{
//requires c++ 20 to use concepts and requirements
//Properties>C/C++>Language>C++ Language standard > Features from the latest C++ working draft
//voila
template <typename T>
concept Printable = requires(std::ostream & os, T a)
{
	os << a;
};

template <typename T>
concept Readable = requires(std::istream & is, T a)
{
	is >> a;
};

template<typename T>
	requires Readable<T>
void read_val(T& val, istream& is = cin)
{
	is >> val;
}


template<typename T>
	requires Printable<T>
ostream& operator<<(ostream& os, const vector<T>& vec)
{
	ostringstream oss{ string() };
	oss << "{ ";
	for (const T& val : vec)
	{
		oss << val << " ";
	}
	oss << "}";

	return os << oss.str();
}

//just exercise, do not overload this operator for vectors !!!!!!!
template<typename T>
	requires Readable<T>
istream& operator>>(istream& is, vector<T>& vec)
{
		T val;
		while (true)
		{
			is >> val;
			if (!is)
				return is;
			vec.push_back(val);
		}

		//this code should be never able to reach here
		return is;
}


template <typename T>
struct S
{
	S(T Val): val(Val) {};
	T& get();
	T& get()const { return val;}

	void set(T Value) { val = Value; }
	T& operator=(const T& other) {
		if (*this == other)
			return *this;
		val = other;
		return *this;
	}
private:
	T val;
};

template<typename T> T& S<T>::get()
{
	return val;
}

void STest()
{
	S<int> s1(1);
	S<char>s2('s');
	S<double>s3(3.0);
	S<string> s4("ssss");
	S<vector<int>>s5(vector<int>{1, 2, 3, 4, 5});

	read_val(s1.get());
	read_val(s2.get());
	read_val(s3.get());
	read_val(s4.get());
	cin >> s5.get();

	cout << s1.get() << " " << s2.get() << " " << s3.get() << " " << s4.get() << "\n";
	cout << s5.get();
}
}

//1
//adds elements from vec2 to vec 1
template<typename T> 
	requires requires(T x) { x += x; }
void f(vector<T>& vec1, vector<T>& vec2)
{
	for (int x = 0; x < vec1.size() && x < vec2.size(); x++)
		vec1[x] += vec2[x];

}

//2
//multiplies elements from vec1 by elements from vec2
template<typename T, typename U>
	requires requires(T x, U y) { x*= y; }
void vector_multiply(vector<T>& vec1, vector<U>& vec2)
{
	for (int x = 0; x < vec1.size() && x < vec2.size(); x++)
		vec1[x] *= vec2[x];
}


template<class T> struct Allocator
{
	T* allocate(int n) { return malloc(n * sizeof(T)); }

	void deallocate(T* p, int n)
	{ 
		T* pp = p+n;
		for (int x = 0; x < n; x++)
		{
			free(pp);
			pp--;
		}
	}

	void construct(T* p, const T& v){ new (p) T(v); }
	void destroy(T* p) { p->~T(); }
};

template<class T> class Unique_ptr
{
	public:
		Unique_ptr(T obj) { pointer = new T(obj); }
		~Unique_ptr() { delete pointer; }

		T& operator*()const { return *pointer; }
		T* operator->()const  { return pointer; }
		T* release() { return pointer; }
	private:
		T* pointer;
};

template<class T> 
class Counted_ptr
{
public:
	Counted_ptr(const T& obj): pointer(new T(obj)), Count(new int(1)){}
	explicit Counted_ptr(Counted_ptr<T>& ptr) : pointer(ptr.release()), Count(ptr.Count) { ++*Count; }
	~Counted_ptr() { if (*Count == 0)delete pointer; else --*Count; }

	T& operator*()const { return *pointer; }
	T* operator->()const { return pointer; }
	T* release() { return pointer; }
	int count() { return *Count; }
private:
	T* pointer;
	int* Count;
};


//tracer exercise done here as well
class File_handle
{
public:
	File_handle(const string& fileName) : name(fileName)
	{
		cout << "\nCreated file handle !\n";
		file = new fstream{ fileName };

		if (!*file)
		{
			delete file;
			throw exception("File has not been found !");
		}
	}

	explicit File_handle(const File_handle& other) { cout << "\nFile handle copying constructor\n"; file = new fstream(other.Name()); name = other.Name(); }
	File_handle& operator=(File_handle other) { cout << "\nFile handle copying operator\n"; file = new fstream(other.Name()); name = other.Name(); return *this; }

	fstream& File()const{ return *file; }
	string Name()const { return name; }

	~File_handle() { cout << "\nFile handle has been deleted\n"; file->close(); delete file; }


private:
	string name;
	fstream* file;
};