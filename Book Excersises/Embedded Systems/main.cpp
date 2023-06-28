#include <iostream>
//#include "text processing.h"
//#include "Numeric operations.h"
//#include <bitset>
//#include "Embedded systems.h"
#include "TEA.h"
#include "Testing.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <chrono>
#include <thread>
#include "C language.h"
#include "Intrusive list.h"
#include "CrackTimer.h"
using namespace std;

int NWDITER(int a, int b)
{
    while (a != b)
        if (a > b)
            a -= b; //lub a = a - b;
        else
            b -= a; //lub b = b-a
    return a; // lub b - obie zmienne przechowuj¹ wynik NWD(a,b)
}

int NWDREC(int a, int b)
{
    if (a != b)
        return NWDREC(a > b ? a - b : a, b > a ? b - a : b);
    return a;
}


int main()
{
    try
	{
        encipher("input.txt", "output.txt", "sraka");
    }
    catch (exception& ex)
    {
        cerr << ex.what();
    }
}

