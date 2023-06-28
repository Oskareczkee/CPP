#pragma once
#include <iostream>
#include <vector>
using namespace std;


namespace C8 {

void print(const vector<int>& Vector)
{
	for (int i : Vector)
		cout << i << "\n";
}

//I didn't know how to name IloscIteracji in English
vector<int> Fibonacci(unsigned int IloscIteracji)
{
	if (IloscIteracji == 0)
		return vector<int>();

	if (IloscIteracji == 1)
		return vector<int>{0};
	else if (IloscIteracji == 2)
		return vector<int>{0, 1};

	//first 2 numbers are in vector by defalut calculated
	IloscIteracji -= 2;

	int prevprevNum=0, prevNum=1;
	int CurrentNum = 2;
	vector<int>NumbersVector{ 0,1 };

	for (int x = 0; x < IloscIteracji; x++)
	{
		CurrentNum = prevprevNum + prevNum;
		NumbersVector.push_back(CurrentNum);
		prevprevNum = prevNum;
		prevNum = CurrentNum;
	}

	return NumbersVector;
}

vector<int> swap_vector(const vector<int>& Vector)
{
	vector<int> output = Vector;

	for (int x = 0; x < Vector.size()-1; x++)
		swap(output[x], output[x + 1]);

	return output;
}

void swap_vector(vector<int>& vector)
{
	for (int x = 0; x < vector.size() - 1; x++)
		swap(vector[x], vector[x + 1]);
}



}
