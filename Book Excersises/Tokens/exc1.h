#pragma once
#include <iostream>
#include <cmath>
using namespace std;

//chapter 4
double calculateDelta(double a, double b, double c)
{
	return pow(b, 2) - (4 * a * c);
}

struct ZeroPlaces
{
	ZeroPlaces(double a, double b) :x1(a), x2(b) {};
	double x1, x2;
};

ZeroPlaces calculateZeroPlaces(double Delta, double a, double b)
{
	if (Delta > 0)
	{
		double x1 = (-b + sqrt(Delta)) / (2 * a);
		double x2 = (-b - sqrt(Delta)) / (2 * a);
		return ZeroPlaces(x1, x2);
	}
	else if (Delta == 0)
	{
		double x1 = -b / (2 * a);
		return ZeroPlaces(x1, NAN);
	}
	else
		return ZeroPlaces(NAN, NAN);
}

void QuadraticEquasionSolver()
{
	double a, b, c;
	cout << "Pass the parameters: \na: ";
	cin >> a;
	cout << "b: ";
	cin >> b;
	cout << "c: ";
	cin >> c;
	ZeroPlaces zp = calculateZeroPlaces(calculateDelta(a, b, c), a, b);
	if (!isnan(zp.x1))
	{
		cout << "First zero place is: " << zp.x1<<"\n";
	}
	else
	{
		cerr << "There are no zero places in this function !";
		return;
	}
	if (!isnan(zp.x2))
		cout << "Second zero place is: " << zp.x2;
	else
	{
		cerr << "There is no second zero place in this function !";
	    return;
	}

	return;
}


//check Notes, for some more info on errors
void ErrorsTest()
{
	throw new exception("hej");
}




//chapter 5


