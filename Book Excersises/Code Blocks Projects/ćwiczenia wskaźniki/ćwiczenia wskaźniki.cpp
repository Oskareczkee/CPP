#include <iostream>
#include <string>

using namespace std;

void cwiczenie1()
{
    string imie;
    string nazwisko;
    string *w_imie=NULL;
    string *w_nazwisko=NULL;

    cout<<"Podaj swoje imie: ";
    cin>>imie;
    if(w_nazwisko==NULL)
    {
    cout<<"Podaj swoje nazwisko: ";
    cin>>nazwisko;
    w_imie=&imie;
    w_nazwisko=&nazwisko;
    cout<<"\n\nTwoje imie to: "<<*w_imie<<"\nTwoje nazwisko to: "<<*w_nazwisko<<"\n\n";
    }
}

void cwiczenie2()
{
    string imie;
    string nazwisko;
    string &refimie=imie;
    string &refnazwisko=nazwisko;

    cout<<"Podaj swoje imie: ";
    cin>>imie;
    cout<<"Podaj swoje nazwisko: ";
    cin>>nazwisko;
    cout<<"\n\nTwoje imie to: "<<refimie<<"\nTwoje nazwisko to: "<<refnazwisko<<"\n\n";
}

void cwiczenie3()
{
  int arg1;
  int arg2;
  int wynik=arg1*arg2;
  int *w_wynik=&wynik;
  cout<<"Wpisz pierwszy argument: ";
  cin>>arg1;
  cout<<"Wpisz drugi argument: ";
  cin>>arg2;
  cout<<"Mnozenie argumentow daje wynik: "<<wynik<<"\n";//Dziwnym trafem, mnozenie wychodzi zle, i nie jest to moj blad
  *w_wynik=arg1+arg2;
  cout<<"Dodawanie argumentow daje wynik: "<<wynik<<"\n";
}

void cwiczenie4()
{
  int zmiennastosu1=990;
  int zmiennastosu2=1;
  int *w_zmiennastosu1=&zmiennastosu1;
  int *w_zmiennastosu2=&zmiennastosu2;
  cout<<"Adres zmiennej 1 to: "<<w_zmiennastosu1<<"\n";
  cout<<"Adres zmiennej 2 to: "<<w_zmiennastosu2<<"\n\n\n";
  cout<<"Adresy zmiennych uporzadkowane: \n\n";
  if(w_zmiennastosu1>w_zmiennastosu2)
  {
      cout<<"Adres zmiennej 1 to: "<<w_zmiennastosu1<<"\n";
      cout<<"Adres zmiennej 2 to: "<<w_zmiennastosu2<<"\n";
  }
  else
  {
      cout<<"Adres zmiennej 2 to: "<<w_zmiennastosu2<<"\n";
      cout<<"Adres zmiennej 1 to: "<<w_zmiennastosu1<<"\n";
  }
  cin.ignore();
  cin.get();
}

int main()
{
    int opcja;
    cout<<"Cwiczenia wskazniki, wybierz opcje od 1-3, 0 wylacza program\n";
    do
    {
    cout<<"Wybierz opcje: ";
    cin>>opcja;
        if(opcja==0)
        {
            break;
        }
    switch(opcja)
    {
    case 1:
        cwiczenie1();
        break;
    case 2:
        cwiczenie2();
        break;
    case 3:
        cwiczenie3();
        break;
    case 4:
        cwiczenie4();
        break;
    default:
        cout<<"Musisz wpisac odpowiednia wartosc !\n";
        break;
    }
    }while(1);
    cin.ignore();
    cin.get();
}
