#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main()
{
    int liczba;
    int minimalna;
    int maksymalna;
    srand(time(NULL));
    cout<<"Witaj w programie 'zgadnij liczbe'.\nAby rozpoczac wprowadz liczbe minimalna i maksymalna\n";
    cout<<"Wprowadz liczbe minimalna\n";
    cin>>minimalna;
    cout<<"Wprowadz liczbe maksymalna\n";
    cin>>maksymalna;
    int losowaliczba= rand()%(maksymalna-minimalna+1)+minimalna;
    do
    {
        cout<<"Zgadnij liczbe !\n";
        cin>>liczba;
        if (liczba>losowaliczba)
        {
            cout<<"Liczba jest za duza, sproboj inna !\n";
        }
        else if(liczba<losowaliczba)
        {
            cout<<"Liczba jest za mala, sproboj inna !\n";
        }
        else
        {
            cout<<"Brawo zgadles liczbe !\n";
        }
    }while(liczba!=losowaliczba);
    cin.ignore();
    cin.get();
}



