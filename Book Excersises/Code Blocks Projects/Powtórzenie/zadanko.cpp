#include <iostream>
#include <windows.h>

using namespace std;

int main()
{
    for(int i=0;i<=1000000;i++)
    {
        cout<<"\a";
        Sleep(i);
    }
}
