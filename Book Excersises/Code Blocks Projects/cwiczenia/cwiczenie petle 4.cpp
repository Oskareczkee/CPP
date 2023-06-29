#include <iostream>
#include <string>

using namespace std;

void sprawdzhaslo(string nazwa, string haslo)
{
  int probylogowania=0;

  if((nazwa==oskar)&&(haslo==niedzwiedzki)||(nazwa==admin)&&(haslo==siemanczek))
     {
        cout<<"Przyznano dostep.\n";
        break;
    }
  else
    {
        if (proby_logowania>=3)
                {
                    cout<<"Wykorzystales limit 3 prob, sproboj sie zalogowac pozniej";
                    break;
                }
                proby_logowania++;
        cout<<"Logowanie nieudane, sproboj ponownie\n";
        cout<<"Podaj swoja nazwe\n ";
            }
}

int main()
{
    string nazwa;
    string haslo;
    int proby_logowania=0;
    cout<<"Witaj w systemie logowania hehe.org \n Podaj swoja nazwe\n ";
    do
    {
    getline (cin, nazwa, '\n');
    cout<<"Podaj swoje haslo\n";
    getline (cin, haslo, '\n');
    sprawdzhaslo();
    }while(1);
    }





