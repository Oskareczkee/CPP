
#include <iostream>
#include <math.h>



using namespace std;




int main()
{
    double x;
    double y;
    int opcja;
    cout<<"Witaj w kalkulatorze, wpisz liczby na ktorych chcesz wykonac dzialania:\n";
    while(1)
    {
    cout<<"Wpisz pierwsza liczbe: ";
    cin>>x;
    cout<<"Wpisz druga liczbe: ";
    cin>>y;
    cout<<"Co chcesz z podanymi liczbami zrobic ?\n"
    <<"1. Dodawanie\n"
    <<"2. Odejmowanie\n"
    <<"3. Mnozenie\n"
    <<"4. Dzielenie\n"
    <<"5. Pierwiastki z obu liczb\n"
    <<"6. Wyjdz z programu\n\n"
    <<"Wybierz opcje: ";
    cin>>opcja;
    switch (opcja)
    {
    case 1:
        {
            cout<<x+y<<"\n\n";
            break;
        }
    case 2:
        {
            cout<<x-y<<"\n\n";
            break;
        }
    case 3:
        {
            cout<<x*y<<"\n\n";
            break;
        }
    case 4:
        {
            if(y==0)
            {
                cout<<"Nie dzielimy przez 0 !\n";
                break;
            }
            cout<<x/y<<"\n\n";
            break;
        }
    case 5:
        {
            cout<<"Pierwiastek liczby x wynosi: \n"<<sqrt(x)<<"\nPierwiastek liczby y wynosi:\n"<<sqrt(y)<<"\n";
            break;
        }
        if(opcja==5)
            break;
    }
     if(opcja==6)
            break;
    }
    cout<<"Dziekuje za korzystanie z programu\nWcisnij cokolwiek aby zamknac program\n\n";
    cin.ignore();
    cin.get();


}





