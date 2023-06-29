#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int zakreslos(int minimum, int maksimum)
{
    return rand() % (maksimum-minimum+1)+minimum;
}

int main()
{
    cout<<"To jest program do AFK\nWcisnij cokolwiek, aby rozpoczac";
    cin.get();
    srand(time(NULL));
    while (1)
    {
         cout<<zakreslos(0,1);
    }
}

