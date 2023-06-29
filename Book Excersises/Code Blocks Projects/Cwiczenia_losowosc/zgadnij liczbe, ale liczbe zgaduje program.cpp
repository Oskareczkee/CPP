#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main()
{
    int liczba;
    int minimalna;
    int maksymalna;
    int proby=0;
    srand(time(NULL));
    cout<<"Witaj w programie 'zgadnij liczbe'.\nAby rozpoczac wprowadz liczbe minimalna i maksymalna\n";
    cout<<"Wprowadz liczbe minimalna\n";
    cin>>minimalna;
    cout<<"Wprowadz liczbe maksymalna\n";
    cin>>maksymalna;
    int losowaliczba= rand()%(maksymalna-minimalna+1)+minimalna;
    do
    {
        int liczba= rand()%(maksymalna-minimalna+1)+minimalna;
        cout<<"Zgadnij liczbe !\n";
        if (liczba>losowaliczba)
        {
            cout<<"Liczba jest za duza, sproboj inna !\n";
            proby++;
        }
        else if(liczba<losowaliczba)
        {
            cout<<"Liczba jest za mala, sproboj inna !\n";
            proby++;
        }
        else
        {
            cout<<"Brawo zgadles liczbe !\nProgramowi zajelo to "<<proby+1<<" prob";
            break;
        }
    }while(liczba!=losowaliczba);
    cin.ignore();
    cin.get();
}


