#include <iostream>

using namespace std;

 int main()
{
int liczba1;
int liczba2;
int dzialanie;
cout<<"Podaj pierwsza liczbe: ";
cin>>liczba1;
cout<<"Podaj druga liczbe: ";
cin>>liczba2;
cout<<"Jakie dzialanie chcesz wykonac ? \n 1=dodawanie \n 2=odejmowanie\n 3=dzielenie \n 4=mnozenie";
cin>>dzialanie;
if (dzialanie=1)
{
    cout<<liczba1+liczba2;
}
else
{
    if (dzialanie=2)
    {
        cout<<liczba1-liczba2;
    }
}

}




