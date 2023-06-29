#include <iostream>
#include <string>
using namespace std;
int main ()
{
    string nazwa;
    string haslo;
    cout<<"Podaj nazwe uzytkownika:\n";
    getline (cin, nazwa, '\n');

    cout<<"Podaj haslo\n";
    getline (cin, haslo, '\n');
    if (nazwa=="admin"&& haslo=="hwdp"||(nazwa=="oskar"&&haslo=="niedzwiedzki"))
        cout<<"Przyznano dostep";

    else
    {
        cout<<"Zla nazwa uzytkownika lub haslo. Sproboj ponownie.\n";
         cout<<"Podaj nazwe uzytkownika:\n";
    getline (cin, nazwa, '\n');

    cout<<"Podaj haslo\n";
    getline (cin, haslo, '\n');
    if (nazwa=="admin"&& haslo=="mandarynka"||(nazwa=="oskar"&&haslo=="niedzwiedzki"))
        cout<<"Przyznano dostep";
        else
        {
            cout<<"Zla nazwa uzytkownika lub haslo. Wylaczam program...";
        }
    }
}


