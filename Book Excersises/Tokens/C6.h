#pragma once
#include <iostream>
#include <random>
#include <vector>
#include <cmath>
using namespace std;

void NumberDistribution()
{
	int number;
	int DistributionParts[4]{ 0,0,0,0 };
	cout << "Pass a number: ";
	cin >> number;
	if (number > 9999 || number < 0)
		cout << "Number is bigger than 9999 or lower than 0";
	for (int x = 3; x >= 0; x--)
	{
		int dist = number /(pow(10, x));
		if (dist != 0)
			DistributionParts[x] = dist;
		number -= dist * pow(10, x);
	}
	cout << "\nLiczba tysiecy: " << DistributionParts[3]<<"\n";
	cout << "Liczba setek: " << DistributionParts[2] << "\n";
	cout << "Liczba dziesiatek: " << DistributionParts[1] << "\n";
	cout << "Liczba jednosci: " << DistributionParts[0] << "\n";
}

int Factorial(int x)
{
	int val=1;
	if (x < 0)
		throw runtime_error("Factorial argument is lower than 0 !");
	if (x == 0)
		return 1;
	else
	{
		for (; x > 0; x--)
			val *= x;
	}
	return val;
}

int Permutation(int a,int b)
{
	if (a - b < 0)
		throw runtime_error("A-B is lower than 0, Factorial cannot be calculated !");
	return Factorial(a) / Factorial(a - b);
}

int Combination(unsigned int a, unsigned int b)
{
	return Permutation(a, b) / Factorial(b);
}

void CombinationPermutationProgram()
{
	int a, b, choice;
	cout << "Pass the A parameter: ";
	cin >> a;
	cout << "Pass the B parameter: ";
	cin >> b;

	if (a < 0 || b < 0)
		throw runtime_error("Arguments are not positive numbers !");


	cout << "What do you wish to calculate:\n1. Permutation\n2. Combination\n";
	cin >> choice;

		switch (choice)
		{
		case 1:
			cout << "The permutation result is: " << Permutation(a, b);
			break;
		case 2:
			cout << "The Combination result is: " << Combination(a, b);
			break;
		default:
			throw runtime_error("Wrong argument (choice hehe) !");
		}
}

