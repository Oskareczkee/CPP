#include <iostream>

using namespace std;

int dodawanie(int x, int y)
{
    int wynik=x+y;
    cout<<"Wynik: "<<wynik;
    return 0;
}
int odejmowanie(int x, int y)
{
    int wynik=x-y;
    cout<<"Wynik: "<<wynik;
    return 0;
}
int dzielenie(int x, int y)
{
    int wynik=x/y;
    cout<<"Wynik: "<<wynik;
    return 0;
}
int mnozenie(int x, int y)
{
    int wynik=x*y;
    cout<<"Wynik: "<<wynik;
    return 0;
}

int main()

{
    int liczba1;
    int liczba2;
    int dzialanie;
    cout<<"Podaj pierwszy argument: ";
    cin>>liczba1;
    cout<<"Podaj drugi argument: ";
    cin>>liczba2;
    cout<<"Jakie dzialanie chcesz wykonac ?\n1=dodawanie\n2=odejmowanie\n3=dzielenie\n4=mnozenie\n";
    cin>>dzialanie;
  if (dzialanie==1)
    dodawanie(liczba1, liczba2);
  else
  {
      if (dzialanie==2)
        odejmowanie(liczba1, liczba2);
        else
        {
            if (dzialanie==3)
                dzielenie(liczba1, liczba2);
                else
                {
                    if (dzialanie==4)
                        mnozenie(liczba1, liczba2);
                }
        }
  }

        cin.ignore ( );
        cin.get ( );


}
