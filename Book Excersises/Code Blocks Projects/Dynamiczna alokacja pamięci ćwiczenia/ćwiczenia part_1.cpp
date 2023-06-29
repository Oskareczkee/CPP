#include <iostream>
#include <string>

using namespace std;

void tabliczka_mnozenia_wskazniki()
{
    int zakres;
    int ww_zakres;
    int zakres2;
    int w_zakres;
    int odpowiedz;
    int *w_w_zakres;
  cout<<"\nWitaj w programie do cwiczenia tabliczki mnozenia !\n\nWpisz zakres liczb (od-do), na jakich chcesz cwiczyc tabliczke mnozenia\n\n";
  cout<<"Wpisz zakres od: ";
  cin>>zakres;
  cout<<"Wpisz zakres do: ";
  cin>>zakres2;
  w_zakres=zakres2-zakres;
  w_w_zakres=new int[w_zakres];
  ww_zakres=zakres;
      for(int j=0;j<=w_zakres;j++)
      {
          w_w_zakres[j]=ww_zakres;
          ww_zakres++;
      }
      for(int i=0;i<=w_zakres;i++)
      {
          for(int j=zakres; j<=zakres2; j++)
          {
          cout<<w_w_zakres[i]<<"*"<<j<<"to: ";
          do
          {
              cin>>odpowiedz;
              if(odpowiedz!=w_w_zakres[i]*j)
              {
                  cout<<"Bledna odpowiedz";
              }
              else
              {
                  break;
              }
          }while(1);
          }
      }
  delete[] w_w_zakres;
  w_w_zakres=NULL;
  cout<<"Gra zakonczona, wcisnij enter, aby przejsc do menu\n";
  cin.ignore();
  cin.get();
}

void trojwymiarowa_tablica()
{
   int dlugosc;
   int szerokosc;
   int wysokosc;
   int ***tablica=NULL;
   int odpowiedz;

   cout<<"Witaj w programie do tworzenia trojwymiarowych tablic z tabliczka mnozenia\n\n"
   <<"Wpisz dlugosc, szerokosc i wysokosc tablicy(w podanej kolejnosci)\n";
   cin>>dlugosc;
   cin>>szerokosc;
   cin>>wysokosc;
   //1
   tablica=new int**[dlugosc];
   //2
     for(int j=0;j<=dlugosc;j++)
      {
       tablica[j]=new int*[szerokosc];
      }
      //3
      for(int j=0;j<=dlugosc;j++)
      {
          for(int i=0;i<=szerokosc;i++)
          {
              tablica[j][i]=new int[wysokosc];
          }
      }
      for(int i=1;i<=dlugosc;i++)
      {
          for(int j=1;j<=szerokosc;j++)
          {
              for(int k=1;k<=wysokosc;k++)
              {
                  tablica[i][j][k]=i*j*k;
                  cout<<i<<"*"<<j<<"*"<<k<<"=";
                  do
                  {
                  cin>>odpowiedz;
                  if(odpowiedz==tablica[i][j][k])
                  {
                      break;
                  }
                  else
                  {
                      cout<<"To nie jest poprawna odpowiedz\n";
                  }
                  }while(1);
              }
          }
      }
      cout<<"Dzialanie programu zakonczylo sie...\nCzyszczenie pamieci...\n";

      //Czyszczenie pamieci

      for(int i=0;i<szerokosc;i++)
      {
          for(int j=0; j<wysokosc;j++)
          {
              delete[]tablica[i][j];
              tablica[i][j]=NULL;
              if(j==wysokosc)
              {
                  delete[]tablica[i];
                  tablica[i]=NULL;
              }
          }
      }
      delete[] tablica;
      tablica=NULL;
      cout<<"\nCzyszczenie zakonczone, wcisnij enter, aby kontynuowac\n";
      cin.ignore();
      cin.get();
}

void adresy_pamieci_tablicy_dwuwymiarowej()
{
    int dlugosc;
    int szerokosc;
    int **tablica=new int*[dlugosc];
    cout<<"\nProgram ten tworzy tablice dwuwymiarowa, dowolnej wielkosci,\n"
    <<"I pokazuje adresy danych poszczegolnych elementow tablicy\n\n";
    cout<<"Podaj dlugosc: ";
    cin>>dlugosc;
    cout<<"Podaj szerokosc: ";
    cin>>szerokosc;
    for(int i=0;i<=dlugosc;i++)
       {
             tablica[i]=new int[szerokosc];
       }
       for(int i=0;i<=dlugosc;i++)
       {
           for(int j=0;j<=szerokosc;j++)
           {
              cout<<"Adres tablicy: "<<i<<"."<<j<<": "<<&tablica[i][j]<<"\n";
           }
       }
       cout<<"\nWcisnij enter, aby wyczyscic pamiec\n";
       cin.ignore();
       cin.get();
       for(int i=0;i<=szerokosc;i++)
       {
           delete[] tablica[i];
       }
       delete[] tablica;
       tablica=NULL;
       cout<<"Czyszczenie zakonczone, wcisnij enter, aby przejsc do menu\n";
       cin.get();
}

void ala_ksiazka_telefoniczna()
{   //Wymaga dopracowania...
    struct Dane
    {
        string imie;
        string nazwisko;
        int ldoor;
    };
    string imie;
    string nazwisko;
    int ldoor;//liczba dni od ostatniej rozmowy
   int liczba_znajomych_maks=2;//w rzeczywistosci wynosi 3
   int liczba_znajomych_rzecz=0;
   int opcja;
   int &id=opcja;
   Dane **tablica=NULL;
   Dane **tablica_tymczas=NULL;
   tablica=new Dane*[liczba_znajomych_maks];
   for(int i=0;i<=liczba_znajomych_maks;i++)
   {
       tablica[i]=new Dane[0];//i oznacza numer uzytkownika, dajemy nowy blok tablicy 0, aby przechowywac ldoor
   }
   cout<<"Witaj\nAby dodac nowego znajomego wpisz 1\nAby zaktualizowac liczbe dni od ostatniej rozmowy wpisz 2\n"
   <<"Aby sprawdzic liczbe dni od ostatniej rozmowy z twoimi znajomymi wpisz 3\nAby wyjsc z programu wcisnij 0\n\n";
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
       if(liczba_znajomych_rzecz==liczba_znajomych_maks)
       {
           tablica_tymczas=new Dane*[liczba_znajomych_rzecz];
           for(int i=0; i<=liczba_znajomych_rzecz;i++)
           {
               tablica_tymczas[i]=new Dane[0];
           }
           for(int i=0;i<=liczba_znajomych_rzecz;i++)
           {
               tablica_tymczas[i][0]=tablica[i][0];
           }
           for(int i=0;i<=liczba_znajomych_maks;i++)
           {
               delete[] tablica[i];
           }
           delete[] tablica;
           tablica=NULL;
           liczba_znajomych_maks+=4;
            tablica=new Dane*[liczba_znajomych_maks];
            for (int i=0;i<=liczba_znajomych_maks;i++)
            {
                tablica[i]=new Dane[0];
            }
            for(int i=0;i<=liczba_znajomych_rzecz;i++)
            {
               tablica[i][0]=tablica_tymczas[i][0];
            }
            //Zwalnianie pamieci z tablicy tymczasowej
            for(int i=0;i<=liczba_znajomych_rzecz;i++)
            {
                delete[] tablica_tymczas[i];
            }
            delete[] tablica_tymczas;
            tablica_tymczas=NULL;
         }
       cout<<"\nPodaj imie swojego znajomego: ";
       cin>>imie;
       tablica[liczba_znajomych_rzecz][0].imie=imie;
       cout<<"Podaj nazwisko swojego znajomego: ";
       cin>>nazwisko;
       tablica[liczba_znajomych_rzecz][0].nazwisko=nazwisko;
       cout<<"Ile dni uplynelo od ostatniej rozmowy: ";
       cin>>ldoor;
       tablica[liczba_znajomych_rzecz][0].ldoor=ldoor;
       cout<<"Pomyslnie dodano znajomego, twoj znajomy ma id: "<<liczba_znajomych_rzecz<<"\n";
       liczba_znajomych_rzecz++;
    break;
   case 2:
       while(1)
       {
       cout<<"Wpisz id swojego znajomego, ktorego dni bez rozmowy chcesz zaktualizowac: ";
       cin>>id;
       if((id<liczba_znajomych_rzecz)||(id>liczba_znajomych_rzecz-1))
       {
           cout<<"Wpisales niepoprawne id !\n";
       }
       else
        break;
       }
       do
       {
       cout<<"Wpisz liczbe dni od ostatniej rozmowy: ";
       cin>>ldoor;
       if(ldoor<0)
       {
           cout<<"Nie mozesz wpisac wartosci ujemnej !\n";
       }
       else
       {
        tablica[id][0].ldoor=ldoor;
        break;
       }
       }while(1);
    break;
   case 3:
       cout<<"Wybierz opcje:\n1. Wszyscy znajomi posortowani wedlug nazwiska\n2. Wszyscy znajomi posortowani"
       <<"Wedlug dni od ostatniej rozmowy\n3. Dni od ostatniej rozmowy dokladnego znajomego\n";
       cin>>opcja;
       switch(opcja)
       {
       case 1:
        break;
       case 2:
        break;
       case 3:
         while(1)
          {
             cout<<"Wpisz id swojego znajomego: ";
             cin>>id;
             if((id<liczba_znajomych_rzecz)||(id>liczba_znajomych_rzecz))
               {
                 cout<<"Wpisales niepoprawne id !\n";
               }
            else
              break;
           }
           cout<<"Liczba dni od ostatniej rozmowy ze znajomym: "<<tablica[id][0].ldoor<<"\n";
        break;
       default:
        cout<<"Wprowadziles nieodpowiednia wartosc !\n";
        break;
       }
    break;
   default:
    cout<<"Wpisales niepoprawna wartosc !\n";
    break;
   }
   }while(1);
}

int main()
{
    int opcja;
   cout<<"Witaj wpisz liczbe programu, ktory chcesz odpalic (0 wylacza program):\n"
   <<"\n1. tabliczka_mnozenia_wskazniki\n2. trojwymiarowa_tablica\n3. adresy_pamieci_tablicy_dwuwymiarowej"
   <<"\n4. Kiedy_ostatnio_rozmawiales_ze_swoimi_znajomymi(nie dziala, porzucam projekt)";
   do
   {
       cout<<"\n\nWybierz program, ktory chcesz odpalic: ";
       cin>>opcja;
       if (opcja==0)
       {
           break;
       }
   switch (opcja)
   {
       case 1:
           tabliczka_mnozenia_wskazniki();
           break;
       case 2:
           trojwymiarowa_tablica();
           break;
       case 3:
        adresy_pamieci_tablicy_dwuwymiarowej();
        break;
       case 4:
        ala_ksiazka_telefoniczna();
        break;
       default:
        cout<<"Wpisales nieodpowiednia wartosc !\n";
   }
   }while(1);
   cout<<"Wychodzenie z programu...\nWcisnij enter, aby zamknac program.\n";
   cin.ignore();
   cin.get();
}
