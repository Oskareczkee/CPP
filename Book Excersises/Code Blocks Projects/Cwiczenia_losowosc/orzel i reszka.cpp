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
    cout<<"To jest program symulujacy rzut moneta !\n"
    <<"Aby rozpoczac wcisnij cokolwiek";
    cin.get();
    srand(time(NULL));
    while (1)
    {
            switch(zakreslos(0,1))
            {
            case 0:
                cout<<"Wypadla reszka";
                break;
            case 1:
                cout<<"Wypadl orzel";
                break;
            }
            cin.get();
    }
}
