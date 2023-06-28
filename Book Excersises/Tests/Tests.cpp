#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <thread>
#include "Libs\CrackTimer.h"

using namespace std;

//iterates through all possibilities, returns time
CrackTimer crack_password_lower(unsigned int charnum = 1)
{
	CrackTimer timer;
	int maxrow = charnum-1;

	timer.StartTimer();

	string pass(charnum, 'a');

	for (int x=0;x<charnum;x++)
	{
		//
	}

	timer.EndTimer();

	return timer;

}

int main()
{
	crack_password_lower(3);

	/*
	string str(6, 'a');
	cout << string(6, 'a')<<"\n";
	str[0] = 'b';
	cout << str;

	for (char ch : str)
	{
		for (int x = 0; x < 25; x++)
			cout << (char)(ch + x);
		cout << "\n";
	}
	*/
}

