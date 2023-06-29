#include <iostream>
#include <string>

using namespace std;

void beer()
{
    {
    int beer=99;
    while (0<beer)
    {
        cout<<beer<< "bottles of beer on the wall,"<<beer<< "bottles of beer.\n";
        beer--;
        cout<<"Take one down and pass it around,"<< beer<< "bottles of beer on the wall.\n";
        if (beer==1)
        {
            cout<<beer<< "bottle of beer on the wall,"<< beer <<"bottle of beer.\n""Take one down and pass it around, no more bottles of beer on the wall.\n";
            break;
        }

    }
    cout<<"No more bottles of beer on the wall, no more bottles of beer."<<endl<<"Go to the store and buy some more, 99 bottles of beer on the wall.\n\n";


}

}
int kalkulator()
{

    double liczba1;
    double liczba2;
    int dzialanie;
    cout<<"Podaj pierwszy argument: ";
    cin>>liczba1;
    cout<<"Podaj drugi argument: ";
    cin>>liczba2;
    cout<<"Jakie dzialanie chcesz wykonac ?\n1=dodawanie\n2=odejmowanie\n3=dzielenie\n4=mnozenie\n";
    cin>>dzialanie;
  if (dzialanie==1)
    cout<<liczba1+liczba2;
  else
  {
      if (dzialanie==2)
        cout<<"Wynik : "<<liczba1-liczba2;
        else
        {
            if (dzialanie==3)
                cout<<"Wynik : "<<liczba1/liczba2;
                else
                {
                    if (dzialanie==4)
                        cout<<"Wynik : "<<liczba1*liczba2;
                }
        }
  }

        cin.ignore ( );
        cin.get ( );




return 0;
}


int main()
{
    int opcja;
    int korzystanie;

    cout<<"Witaj w menu glownym.\n\nWybierz odpowiednia opcje, aby wybrac program.\n1-99 bottles of beer.exe\n2-kalkulator.exe\n\n";
    do
    {
    cin>>opcja;
    switch(opcja)
    {
    case 1:
        cout<<"Wybrales program 1.\n\nUruchamianie...\n\n";
        beer();
        cout<<"Dzialanie programu zakonczylo sie. Czy chcesz jeszcze raz uruchomic jakis program ?\nWcisniecie czegokolwiek spowoduje wylaczenie programu\nWcisnij 1 aby kontynuowac.\n";
        cin>>korzystanie;
        if (korzystanie==1)
        {
        cout<<"Wybierz odpowiednia opcje, aby wybrac program.\n1-99 bottles of beer.exe\n2-kalkulator.exe\n\n";
        continue;
        }
        break;
    case 2:
        cout<<"Wybrales program 2.\n\nUruchamianie...\n\n";
        kalkulator();
        cout<<"Dzialanie programu zakonczylo sie. Czy chcesz jeszcze raz uruchomic jakis program ?\nWcisniecie czegokolwiek spowoduje wylaczenie programu\nWcisnij 1 aby kontynuowac.\n";
        cin>>korzystanie;
        if (korzystanie==1)
        {
        cout<<"Wybierz odpowiednia opcje, aby wybrac program.\n1-99 bottles of beer.exe\n2-kalkulator.exe\n\n";
        continue;
        }
        break;
    }
    }while(korzystanie==1);
}
