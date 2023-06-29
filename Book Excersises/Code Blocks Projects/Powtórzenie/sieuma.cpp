#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int random(int min, int maks)
{
	return rand() % (maks - min + 1) - min;
}

int z1()
{
	int liczba;
	int maks;
	cout << "Wpisz liczbe :";
	cin >> liczba;
	maks=liczba;
	while (liczba != 0)
	{
		cout << "\nWpisz liczbe :";
		cin >> liczba;
		if (liczba > maks)
			maks = liczba;
	}
	return maks;
}

int z2(int n)
{
	int liczba;
	int min = random(-5, 40);
	for (int x = 0; x < n - 1; x++)
	{
		liczba= random(-5, 40);
		if (liczba < min)
			min = liczba;
	}
	return min;
}

int z3(int n)
{
	int liczba;
	int tab[n];
return liczba;
}

int main()
{
	srand(time(NULL));
	cout << z1();
	cout << z2(5);
}
