#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

//zadania
void z_1();
void z_2();
void z_3();
void panel_uzytkownika(map<string, string> &uzytkownik);
///////////
void ksiazka_adresowa_poczatek()
{
    cout<<"Wybierz opcje:\n"
        <<"1.Dodaj uzytkownika\n"
        <<"2.Usun uzytkownika\n"
        <<"3.Zmien email uzytkownika\n"
        <<"4.Wyszukaj uztykownika\n"
        <<"0.Wyjdz\n";
}

void wyniki_poczatek()
{
    cout<<"Wybierz opcje:\n"
        <<"1.Dodaj wynik\n"
        <<"2.Wyswietl tablice wynikow\n"
        <<"0.Wyjdz\n";
}

void rejestracja_logowanie()
{
    cout<<"Wybierz opcje:\n"
        <<"1.Zarejestruj sie\n"
        <<"2.Zaloguj sie\n"
        <<"0.Wyjdz\n";
}
void panel_uzytkownika()
{
    cout<<"Wybierz opcje:\n"
        <<"1. Zmiana hasla\n"
        <<"2. Wyloguj sie\n";
}

void cls()
{
    cin.get();
    system("cls");
}
//////////

int main()
{
   int opcja;
   do
   {
       cout<<"Wybierz zadanie 1-3(0 wylacza program): ";
       cin>>opcja;
       switch(opcja)
       {
       case 1:
        {
            z_1();
            break;
        }
       case 2:
        {
            z_2();
            break;
        }
       case 3:
        {
           z_3();
           break;
        }
       case 0:
        {
            cls();
            break;
        }
       default:
        {
            cout<<"Wpisales nieodpowiednia wartosc !\n";
            break;
        }
       }
   }while(opcja!=0);
}

void z_1()
{
  int opcja;
  string imie_i_nazwisko;
  string email;
  map<string, string> ksiazka_adresowa;
  ksiazka_adresowa["Oskar Niedzwiedzki"]="zuzytychlebak@o2.pl";
  map<string, string>::iterator itr=ksiazka_adresowa.begin();
  do
  {
      ksiazka_adresowa_poczatek();
      cin>>opcja;
      switch(opcja)
      {
      case 1:
        {
            cout<<"Podaj swoje imie i nazwisko: ";
            cin.ignore();
            getline(cin, imie_i_nazwisko,'\n');
            itr=ksiazka_adresowa.find(imie_i_nazwisko);
            if(itr==ksiazka_adresowa.end())
            {
            cout<<"Podaj swoj adres email: ";
            getline(cin, email, '\n');
            ksiazka_adresowa[imie_i_nazwisko]=email;
            cls();
            break;
            }
            else
            {
                cout<<"Wpisane przez ciebie imie i nazwisko znajduje sie juz w bazie danych !\n";
                cls();
                break;
            }
        }
      case 2:
        {
            cout<<"Podaj imie i nazwisko uzytkownika, ktorego chcesz usunac: ";
            cin.ignore();
            getline(cin, imie_i_nazwisko,'\n');
            itr=ksiazka_adresowa.find(imie_i_nazwisko);
            if(itr!=ksiazka_adresowa.end())
            {
            ksiazka_adresowa.erase(imie_i_nazwisko);
            cls();
            break;
            }
            else
            {
                cout<<"Konto, ktore chcesz usunac nie istnieje !\n";
                cls();
                break;
            }
        }
      case 3:
        {
            cout<<"Podaj imie i nazwisko uzytkownika, ktorego email chcesz zmienic: ";
            cin.ignore();
            getline(cin, imie_i_nazwisko,'\n');
            itr=ksiazka_adresowa.find(imie_i_nazwisko);
            if(itr!=ksiazka_adresowa.end())
            {
                cout<<"Podaj nowy email: ";
                getline(cin, email,'\n');
                ksiazka_adresowa[imie_i_nazwisko]=email;
                cls();
                break;
            }
            else
            {
               cout<<"Nie odnaleziono uzytkownika !\n";
               cls();
               break;
            }
        }
      case 4:
        {
            cout<<"Podaj imie i nazwisko uzytkownika, ktorego chcesz znalezc ";
            cin.ignore();
            getline(cin, imie_i_nazwisko,'\n');
            itr=ksiazka_adresowa.find(imie_i_nazwisko);
            if(itr!=ksiazka_adresowa.end())
            {
               cout<<"Imie i nazwisko: "<<imie_i_nazwisko<<"\n"
                   <<"Email: "<<ksiazka_adresowa[imie_i_nazwisko]<<"\n";
               cls();
               break;
            }
            else
            {
                cout<<"Nie odnaleziono uzytkownika !\n";
                cls();
                break;
            }
        }
      case 0:
        {
            ksiazka_adresowa.clear();
            cls();
            break;
        }
        default:
        {
            cout<<"Wpisales nieodpowiednia wartosc !\n";
            cin.ignore();
            cls();
            break;
        }
      }
  }while(opcja!=0);
}

void z_2()
{
    int opcja;
    int wynik;
    vector<int>wyniki;
    do
    {
       wyniki_poczatek();
       cin>>opcja;
       switch(opcja)
       {
       case 1:
       {
           cout<<"Podaj swoj wynik: ";
           cin>>wynik;
           wyniki.push_back(wynik);
           sort(wyniki.begin(), wyniki.end());
           cout<<"Pomyslnie dodano wynik !\n";
           cin.ignore();
           cls();
        break;
       }
       case 2:
        {
            //chce wyswietlac wyniki od najwiekszego do najmniejszego
            for(vector<int>::iterator itr=wyniki.end()-1,koniec=wyniki.begin()-1;itr!=koniec;--itr)
            {
                cout<<*itr<<"\n";
            }
            cin.ignore();
            cls();
            break;
        }
       case 0:
        {
            wyniki.clear();
            cls();
            break;
        }
       default:
        {
            cout<<"Wpisales nieodpowiednia wartosc !\n";
            cin.ignore();
            cls();
            break;
        }
       }
    }while(opcja!=0);

}

void panel_uzytkownika(map<string, string> &uzytkownik, string nazwa)
{
    cls();
   int opcja;
   int proby;
   string haslo;
   cout<<"Witaj "<<nazwa<<" !\n";
   do
   {
    panel_uzytkownika();
    cin>>opcja;
    switch(opcja)
    {
    case 1:
        {
            do
            {
            cout<<"Wpisz swoje stare haslo: ";
            cin.ignore();
            getline(cin, haslo, '\n');
            if(uzytkownik[nazwa]!=haslo)
            {
                cout<<"Niepoprawne haslo !\n";
                cin.ignore();
                proby++;
            }
            else
            {
                cout<<"Wpisz nowe haslo: ";
                getline(cin, haslo, '\n');
                uzytkownik[nazwa]=haslo;
                cout<<"Zmiana hasla powiodla sie !\n";
                cls();
                break;
            }
            }while(proby!=3);
            break;
        }
    case 2:
        {
            cls();
            break;
        }
    default:
        {
            cout<<"Wpisales nieodpowiednia wartosc !\n";
            cls();
        }
    }
   }while(opcja!=2);
}

void z_3()
{
   int opcja;
   string nazwa;
   string haslo;
   map<string, string> uzytkownik;
   uzytkownik["Pierwszy uzytkownik"]="cojaturobie";
   map<string, string>::iterator itr=uzytkownik.begin();
   do
   {
     rejestracja_logowanie();
     cin>>opcja;
     switch(opcja)
     {
     case 1:
        {
            cout<<"Wpisz swoja nazwe uztykownika: ";
            cin.ignore();
            getline(cin, nazwa,'\n');
            itr=uzytkownik.find(nazwa);
            if(itr==uzytkownik.end())
            {
                cout<<"Wpisz swoje haslo: ";
                getline(cin, haslo, '\n');
                uzytkownik[nazwa]=haslo;
                cout<<"Rejestracja powiodla sie !\n";
                cls();
                break;
            }
            else
            {
                cout<<"Wpisana przez ciebie nazwa uzytkownika jest juz zajeta !\n";
                cls();
                break;
            }
        }
     case 2:
        {
            cout<<"Wpisz swoja nazwe uztykownika: ";
            cin.ignore();
            getline(cin, nazwa,'\n');
            itr=uzytkownik.find(nazwa);
            if(itr!=uzytkownik.end())
            {
                for(int x=0;x!=3;x++)
                    {
                       cout<<"Wpisz swoje haslo: ";
                       getline(cin, haslo, '\n');
                       cin.ignore();
                       if(x==3)
                       {
                           cout<<"Osiagnieto limit wpisywania hasla !\n";
                           cls();
                           break;
                       }
                       if(uzytkownik[nazwa]!=haslo)
                       {
                           cout<<"Wpisales niepoprawne haslo !\n";
                           cls();
                           continue;
                       }
                       else
                       {
                           panel_uzytkownika(uzytkownik, nazwa);
                           break;
                       }

                    }
                    break;
            }
            else
            {
                cout<<"Podana nazwa uzytkownika nie istnieje !\n";
                cls();
                break;
            }
        }
     case 0:
        {
            break;
        }
     default:
        {
            cout<<"Wpisales nieodpowiednia wartosc !\n";
            cls();
            break;
        }
     }
   }while(opcja!=0);
}
