#pragma once
#include "CrackTimer.h"
#include "Matrix.h"
#include <iterator>
#include<random>
#include <fstream>
#include <map>
#include <set>
#include <unordered_set>

using namespace std;

template<class ForwardIterator, class T>
bool Custom_Binary_Search(ForwardIterator first, ForwardIterator last, T value)
	requires forward_iterator<ForwardIterator>
{
	while (first != last)
	{
		auto offset = std::distance(first, last);
		ForwardIterator middle = first;
		advance(middle, offset / 2);

		if (value<*middle)
			last = middle;
		if (value == *middle)
			return true;
		else
		{
			first = middle;
			advance(first,1);
		}
	}
	return false;
}


template<class ForwardIterator, class T, class Comparator>
bool Custom_Binary_Search(ForwardIterator first, ForwardIterator last, T value, Comparator comp)
	requires forward_iterator<ForwardIterator>
{
	while (first != last)
	{
		auto offset = std::distance(first, last);
		ForwardIterator middle = first;
		advance(middle, offset / 2);

		if (value == *middle)
			return true;
		if (comp(value, *middle))
			last = middle;
		else
		{
			first = middle;
			advance(first, 1);
		}
	}
	return false;
}

int generate_random_number(int left, int right)
{
	static random_device rd;
	static mt19937 mt(rd());
	uniform_int_distribution dist(left, right);

	//generates int
	return { (dist(mt)) };

}

double generate_random_double(double left, double right)
{
	static random_device rd;
	static mt19937 mt(rd());
	uniform_real_distribution dist(left, right);

	//generates double
	return { (dist(mt)) };
}

template<class T>
concept Readable = requires(istream & is, T a) { is >> a; };
template<class T>
concept Printable = requires(ostream & os, T a) { os << a; };

//////////////////////////////////////////////////////////////////////////////////////////////////

//1
void test1()
{
	vector<int> empty = {};
	vector<int> small = { 1,2,3,5,6,7,8,9,10 };
	vector<int>big(2000);
	big.push_back(15);
	big.push_back(30);
	big.push_back(45);

	vector<int>extreme_dist = { 0,1000,10000,5,37473,1,87456,21,321992 };
	vector<int>duplicates = { 0,1,2,0,0,2,4,3,1,2,0 };
	vector<int>even = { 1,2,3,4 };
	vector<int>odd = { 1,2,3,4,5 };

	vector<int>random;
	
	for (int x = 0; x < 200; x++)
		random.push_back(generate_random_number(100, 200));

	sort(empty.begin(), empty.end());
	sort(small.begin(), small.end());
	sort(big.begin(), big.end());
	sort(extreme_dist.begin(), extreme_dist.end());
	sort(duplicates.begin(), duplicates.end());
	sort(even.begin(), even.end());
	sort(odd.begin(), odd.end());
	sort(random.begin(), random.end());

	cout << binary_search(empty.begin(), empty.end(), 120) << "\n"
		<< binary_search(small.begin(), small.end(), 2) << "\n"
		<< binary_search(big.begin(), big.end(), 30) << "\n"
		<< binary_search(extreme_dist.begin(), extreme_dist.end(), 87456) << "\n"
		<< binary_search(duplicates.begin(), duplicates.end(), 2) << "\n"
		<< binary_search(even.begin(), even.end(), 2) << "\n"
		<< binary_search(odd.begin(), odd.end(), 3) << "\n"
		<< binary_search(random.begin(), random.end(), 128);
}

//4
template<typename T>
struct TestData
{
	string label;
	T data;
	bool expected_result;
};

//Data format
//label "{"data"}" expected_result
template<typename T>
istream& operator>>(istream& is, TestData<T>& data)
	requires Readable<T>
{
	T Data;
	string label;
	bool result;

	char ch1, ch2;
	is >> label >> ch1 >> Data >> ch2 >> result;
	if (!is || ch1 != '{' || ch2 != '}')
	{
		is.setf(ios_base::failbit);
		return is;
	}

	data = TestData{ label, Data, result };
	return is;
}

template<class T>
ostream& operator<<(ostream& os, const TestData<T>& data)
	requires Printable<T>
{
	return os << data.label << " {" << data.data << "} expected result: " << data.expected_result << "\n";
}

void test_data_test(const string& fileName)
{
	ifstream ifs{ fileName };
	if (!ifs)
		throw exception("file not found!");

	int tests_passed = 0;
	TestData<int> temp;

	while (ifs >> temp)
	{
		if (temp.data == 10 || temp.data == 5 || temp.data == 15)
			tests_passed++;
		cout << temp;
	}

	cout << "\n\nTests passed: " << tests_passed;
}

//5
//returns true if value is being modified by function
bool modify_test()
{
	vector<int>vals = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 };
	vector<int>valccpy = vals;

	//do 15 tests for all values and print them
	for (int& i : vals)
		cout<<Custom_Binary_Search(vals.begin(), vals.end(), i);

	cout << "\n\nvector of values:\n";
	for (int& i : vals)
		cout << i<<" ";
	cout << "\n\ncopy of vector of values\n";
	for (int& i : valccpy)
		cout << i<<" ";

	for (int x = 0; x < 15; x++)
		if (vals[x] != valccpy[x])
			return true;
	return false;
}

//11
//fills with random values
void fill_matrix(Numeric_lib::Matrix<double, 2>& m)
{
	int size2 = m.dim2();
	int size1 = m.dim1();
	for (int i = 0; i < size1; i++)
		for (int y = 0; y < size2; y++)
			m[i][y]=generate_random_double(-10, 10);
}

double row_sum(Numeric_lib::Matrix<double, 2>& m, int n)
{
	double sum = 0;
	int size = m.dim2();
	for (int i = 0; i < size; ++i)
		sum += m[n][i];
	return sum;
}

double row_accum(Numeric_lib::Matrix<double, 2> m, int n)
{
	double s = 0;
	for (int i = 0; i < n; ++i) s += row_sum(m, i);
	return s;
}


//i literally don't know how to implement faster algorithm, it just iterates through all values in all rows ands adds them xD
void row_accum_test(unsigned long int matrix_size)
{
	Numeric_lib::Matrix<double, 2> m(matrix_size, matrix_size);
	CrackTimer fillTime;
	CrackTimer accumulateTime;

	fillTime.StartTimer();
	fill_matrix(m);
	fillTime.EndTimer();
	cout << "Matrix size: " << matrix_size << "x" << matrix_size << "\n";
	cout << "Fill time: " << fillTime.ShowTime(CrackTimer::TimeUnit::MILISECONDS) << "ms\n";

	accumulateTime.StartTimer();
	cout << "Accumulated row value: " << row_accum(m, matrix_size)<<"\n";
	accumulateTime.EndTimer();
	cout << "Accumulation time: " << accumulateTime.ShowTime() << "s\n";
	cout << "Total time: " << fillTime.ShowTime() + accumulateTime.ShowTime() << "s";
}

void random_number_test(const double& left, const double& right, const long int& size)
{
	vector<double>vec (size);
	CrackTimer genTime;
	genTime.StartTimer();
	for (auto& i : vec)
		i = generate_random_double(left, right);
	genTime.EndTimer();
	cout << "Fill time: " << genTime.ShowTime() << "s\n";

	CrackTimer sortTime;
	sortTime.StartTimer();
	sort(vec.begin(), vec.end());
	sortTime.EndTimer();
	cout << "Sort time: " << sortTime.ShowTime() << "s\n";
}

string generate_random_string(const unsigned int& string_size)
{
	string output;

	for (unsigned int x = 0; x < string_size; x++)
		output += (char)generate_random_number(97, 122);

	return output;
}

void random_string_test(const int& sizeLeft, const int& sizeRight, const long unsigned int& size)
{
	vector<string>vec(size);

	CrackTimer genTime;
	genTime.StartTimer();
	int random_string_size = 0;
	for (auto& i : vec)
	{
		random_string_size = generate_random_number(sizeLeft, sizeRight);
		i = generate_random_string(random_string_size);
	}
	genTime.EndTimer();
	cout << "Fill time (string): " << genTime.ShowTime() << "s\n";

	CrackTimer sortTime;
	sortTime.StartTimer();
	sort(vec.begin(), vec.end());
	sortTime.EndTimer();
	cout << "Sort time (string): " << sortTime.ShowTime() << "s\n";
}

void random_string_map_test(const int& sizeLeft, const int& sizeRight, const long unsigned int& size)
{

	unordered_set<string> set;

	CrackTimer genTime;
	genTime.StartTimer();
	int random_string_size = 0;
	for (unsigned int x=0;x<size;x++)
	{
		random_string_size = generate_random_number(sizeLeft, sizeRight);
		set.insert(generate_random_string(random_string_size));
	}
	genTime.EndTimer();
	cout << "Fill time (string): " << genTime.ShowTime() << "s\n";

	CrackTimer sortTime;
	sortTime.StartTimer();
	sortTime.EndTimer();
	cout << "Sort time (string): " << sortTime.ShowTime() << "s\n";
}