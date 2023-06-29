#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

//Struktury3

struct Dane//cwiczenie 1
{
    string nazwisko;
    string adres_2;
    string adres;
    string numer_tel;
};
struct StatkiKosmiczne
{
    int x;//wspolrzedna x
    int y;//wpsolrzedna y
};
struct Wyniki
{
    string imie_gracza;
    int wynik[20];
    int v=0;
    int wynik_najw;
};

int losowaliczba()
{
    return rand()%(100-10+1)+ 10;
}

//Cwiczenia

void cwiczenie1()
{
    Dane osoba;
        cout<<"Podaj swoje nazwisko\n\n";
        cin>>osoba.nazwisko;
        cout<<"\n\nPodaj swoj adres zamieszkania\n\n";
        cin>>osoba.adres;
        cout<<"\n\nPodaj swoj numer telefonu\n\n";
        cin>>osoba.numer_tel;
        cout<<"\nDziekuje, dane zostaly zapisane\n\n";
    cout<<"\n\n\n\nWczytywanie zapisanych danych...\n\n";
    cout<<"Nazwisko: "<<osoba.nazwisko<<"\nAdres: "<<osoba.adres<<"\nNumer telefonu: "<<osoba.numer_tel<<"\n\n\n";
    cin.ignore();
    cin.get();
    cout<<"Witaj, wybierz cwiczenie, ktore chcesz wczytac (1-4), wcisniecie 0 wylacza program\n";
}

void cwiczenie2()
{
    int opcjastatki;
    int statekn;//numer statku
    int liczbastatkow;
    srand(time(NULL));
  StatkiKosmiczne statek[11];
  liczbastatkow=10;
  cout<<"\nZ kazdym wprowadzeniem liczby, statki na ekranie (tak, nie widzisz ich, wyobraz sobie)\nPoruszaja sie "
  <<"losowo od 10 do 100 pol w osi x i y\nPlansza ma wymiary 1024x768\nWszystkie statki zaczynaja z koordynatow 0,0\nMozesz sprawdzic aktualna pozycje kazdego statku, klikajac 1 i wybierajac numer statku\n"
  <<"Jest lacznie 10 statkow\nJesli jakis statek zniknie z ekranu, zostaniesz powiadomiony stosownym komunikatem\n"
  <<"Program domyslnie konczy dzialanie, gdy wszystkie statki znikna z ekranu\nAby skonczyc dzialanie programu wprowadz 0\nWcisnij enter, aby zaczac zabawe\n";
  for(int b=1;b<11;b++)//Nadawanie wszystkim statkom koordynatow 0,0
  {
      statek[b].x=0;
      statek[b].y=0;
  }
  cin.ignore();
  cin.get();
  while(1)
  {
    do
    {
        if (liczbastatkow==0)
        {
            break;
        }
        cout<<"\nWprowadz jakakolwiek wartosc, lub 1, aby sprawdzic pozycje wybranego statku\n";
        cin>>opcjastatki;
        if((opcjastatki!=1)&&(opcjastatki!=0))
        {
        for(int b=1;b<11;b++)
        {
            if(statek[b].x==-1)
            {
                continue;
            }
           statek[b].x=statek[b].x + losowaliczba();
           statek[b].y=statek[b].y + losowaliczba();
           if((statek[b].x>1024)||(statek[b].y>768))
           {
               cout<<"Statek "<<b<<" Znika z planszy\n";
               statek[b].x=-1;
               statek[b].y=-1;
               liczbastatkow--;
           }
           if(liczbastatkow==0)
           {
            break;
           }
        }
        }
        else
        {
            break;
        }
    }while(opcjastatki!=1,0);
    if(liczbastatkow==0)
    {
        break;
    }
    if(opcjastatki==1)
    {
        do
        {
    cout<<"Wprowadz numer statku, ktorego chcesz zobaczyc koordynaty\n";
    cin>>statekn;
    if((statekn<=0)||(statekn>10))
               {
                   cout<<"Taki statek nie istnieje !\n";
               }
    else if((statek[statekn].x==-1)||(statek[statekn].y==-1))
    {
        cout<<"Ten statek jest juz poza ekranem\n";
    }
    else
    {
    cout<<"Koordynat x statku "<<statekn<<" Wynosi: "<<statek[statekn].x<<"\n"
    <<"Koordynat y statku "<<statekn<<" Wynosi: "<<statek[statekn].y<<"\n";
    }
    }while((statekn<=0)||(statekn>10));
    }
    else if(opcjastatki==0)
    {
        break;
    }

}
cout<<"Gra sie zakonczyla, wcisnij cokolwiek, aby przejsc do menu zadan\n\n";
cin.ignore();
cin.get();
cout<<"Witaj, wybierz cwiczenie, ktore chcesz wczytac (1-4), wcisniecie 0 wylacza program\n";
}

void cwiczenie3()
{
    int id;
    int x=0;
  int opcja;
  Dane osoba[15];
  x=1;
  cout<<"\nWitaj w programie imitujacym ksiazke adresowa, aby dodac nowa pozycje wcisnij 1\nAby sprawdzic pozycje w ksiazce adresowej wcisnij 2 i wpisz odpowiednie id\n"
  <<"Aby wyjsc z programu wpisz 0\n\n\n";
  while(1)
  {
      if(opcja==0)
      {
          break;
      }
  do
  {
       cout<<"Co chcesz zrobic\n\n";
        cin>>opcja;
        if(opcja==0)
        {
            break;
        }
        switch(opcja)
        {
      case 1:
          cout<<"Dodawanie nowej pozycji...\n\n";
             cout<<"Podaj swoje nazwisko\n";
             cin>>osoba[x].nazwisko;
             cout<<"Podaj pierwsza czesc swojego adresu zamieszkania\n";
             cin>>osoba[x].adres;
             cout<<"Podaj numer swojego domu\n";
             cin>>osoba[x].adres_2;
             cout<<"Podaj numer swojego telefonu\n";
             cin>>osoba[x].numer_tel;
             cout<<"\n\nPomyslnie dodano adres do ksiazki adresowej\n"
             <<"Twoj adres ma id :"<<x<<"\n\n";
             x++;
             break;
      case 2:
          cout<<"Wyszukiwanie pozycji... \n";
          do
          {
          cout<<"Wpisz id pozycji, ktora chcesz sprawdzic\n";
          cin>>id;
          if(id>x-1||id<0)
          {
              cout<<"Taka pozycja nie istnieje !\n";
          }
          else
          {
          cout<<"\n\nWyszukiwanie pozycji...\n\n";
          cout<<"Nazwisko: "<<osoba[id].nazwisko<<"\nAdres zamieszkania: "<<osoba[id].adres<<" "<<osoba[id].adres_2<<"\n"
          <<"Numer telefonu: "<<osoba[id].numer_tel<<"\n\n";
          cout<<"Jesli chcesz wyszukac jeszcze jakas pozycja, wcisnij 2\n";
          cin>>opcja;
          }
          }while(opcja!=1);
          break;
      default:
        cout<<"Musisz wybrac odpowiednia wartosc !\n\n";
        break;
        }
  }while(opcja!=1,2);
}
}

void cwiczenie4()
{
    Wyniki hehe[90];
    int opcjac4;
    int id;
    int h=1;
    cout<<"Witaj w programie pozwalajacym wprowadzac swoje wyniki w nieistniejacej grze\n\n"
    <<"Jesli chcesz stworzyc nowe konto i wprowadzic wynik wcisnij 1\n\nAby dodac nowe wyniki do istniejacego konta wcisnij 2\n\nAby przeglaac wyniki innych wcisnij 3\n\nAby wylaczyc program wcisnij 0\n\n";
    do
    {
    cout<<"Wybierz opcje: \n";
    cin>>opcjac4;
        switch(opcjac4)
        {
        case 1:
            cout<<"Wprowadz swoj wynik: ";
            cin>>hehe[h].wynik[hehe[h].v];
            hehe[h].v++;
            cout<<"\n";
            cout<<"Wprowadz swoje imie: ";
            cin>>hehe[h].imie_gracza;
            cout<<"\n\n";
            cout<<"Dane zostaly pomyslnie wprowadzone !\n";
            cout<<"Twoje id to: "<<h<<"\n";
            h++;
            cout<<"Wcisnij enter, aby kontynuowac\n";
            cin.ignore();
            cin.get();
            break;
        case 2:
            while(1)
            {
            cout<<"Wprowadz swoje id: ";
            cin>>id;
            if(id>h-1||id<1)
            {
                cout<<"Takie id nie istnieje !\n";
            }
            else
            {
            cout<<"\nWprowadz nowy wynik do swojej tabeli wynikow: ";
            cin>>hehe[id].wynik[hehe[id].v];
            cout<<"\nPomyslnie dodano nowy wynik !\n\n";
            hehe[id].v++;
            break;
            }
            }
            break;
        case 3:
            cout<<"\nWitaj w tablicy wynikow, co chcesz, aby wyswietlono:\n1-Najwyzsze wyniki wszystkich graczy\n"
            <<"2-Wszystkie wyniki wybranego gracza\n3-Lista graczy\n4-Wszystkie wyniki wszystkich graczy\n";
            cin>>opcjac4;
            switch(opcjac4)
            {
                case 1:
                    cout<<"Najwyzsze wyniki wszystkich graczy: \n\n";
                    for(int y=1;y<=h-1;y++)
                    {
                        cout<<hehe[y].imie_gracza<<": ";
                       for(int o=0;o<=hehe[y].v-1;o++)
                       {
                         if(hehe[y].wynik[o]>hehe[y].wynik_najw)
                         {
                             hehe[y].wynik_najw=0;
                             hehe[y].wynik_najw=hehe[y].wynik_najw+hehe[y].wynik[o];
                         }
                       }
                       cout<<hehe[y].wynik_najw<<"\n";
                    }
                    cout<<"\n";
                    break;
                case 2:
                    while(1)
                    {
                    cout<<"Wpisz id gracza, ktorego wyniki chcesz zobaczyc (Wyniki ustawione w kolejnosci ich dodania): ";
                    cin>>id;
                    if(id>h-1||id<1)
                       {
                          cout<<"Takie id nie istnieje !\n";
                       }
                       else
                       {
                    cout<<"\n\n";
                    cout<<"Wyniki gracza "<<hehe[id].imie_gracza<<":\n";
                    for(int j=0;j<=hehe[id].v-1;j++)
                    {
                        for(int l=j+1;l==j+1;l++)
                        {
                            cout<<l<<". "<<hehe[id].wynik[j]<<"\n";
                        }
                    }
                       }
                    }
                    cout<<"\n";
                    break;
                case 3:
                    cout<<"\n\nLista graczy (numer w kolejnosci reprezentuje id):\n\n";
                    for(int j=1;j<=h-1;j++)
                    {
                        cout<<j<<". "<<hehe[j].imie_gracza<<"\n";
                    }
                    cout<<"\n";
                    break;
                case 4:
                    cout<<"\n\nWszystkie wyniki wszystkich graczy:\n\n";
                    for(int u=1;u<h;u++)
                    {
                        cout<<hehe[u].imie_gracza<<"\n";
                          for(int j=0;j<=hehe[u].v-1;j++)
                           {
                             for(int l=j+1;l==j+1;l++)
                             {
                                cout<<l<<". "<<hehe[u].wynik[j]<<"\n";
                             }
                             cout<<"\n";
                           }
                    }
                    cout<<"\n";
                    break;
            }
            break;
        default:
            cout<<"Musisz wpisac odpowiednia wartosc !\n\n";
            break;
        }
    }while(opcjac4!=0);
}

//Program glowny

int main()
{
    int cwiczenie;
    cout<<"Witaj, wybierz cwiczenie, ktore chcesz wczytac (1-4), wcisniecie 0 wylacza program\n";
    do
    {
     cin>>cwiczenie;
     switch(cwiczenie)
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
     }
    }while(cwiczenie!=0);
}
