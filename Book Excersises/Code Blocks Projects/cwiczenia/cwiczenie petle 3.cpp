#include <iostream>

using namespace std;
int main()
{
    int liczba1;
    int liczba2;
    int liczba0;
    int kontynuacja;

    cout<<"Wprowadz liczbe 1 ";
    cin>>liczba1;
    cout<<"Wprowadz liczbe 2 ";
    cin>>liczba2;
    while (1)
    {
        cout<<liczba1+liczba2;
        liczba1++;
        cout<<"Czy chcesz kontunuowac ? \n1-tak\n0-nie\n ";
        cin>>kontynuacja;
        if (kontynuacja==0)
        {
            break;
        }
    }
}
