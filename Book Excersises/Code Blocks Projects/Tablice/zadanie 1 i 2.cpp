#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;
int rozmiar;
int znajdzNajmniejszyPozostalyElement (int tabilca[], int rozmiar, int indeks);
void zamien (int tablica[], int pierwszy_indeks, int drugi_indeks);

void sortuj (int tablica[], int rozmiar)
{
    for (int i=0;i<rozmiar;i++)
    {
        int indeks=znajdzNajmniejszyPozostalyElement(tablica, rozmiar, i);
        zamien(tablica, i, indeks);
    }
}
int znajdzNajmniejszyPozostalyElement(int tablica[], int rozmiar, int indeks)
{
    int indeks_najmniejszej_wartosci=indeks;
    for(int i=indeks+1;i<rozmiar;i++)
    {
        if(tablica[i]<tablica[indeks_najmniejszej_wartosci])
        {
            indeks_najmniejszej_wartosci=i;
        }
    }
    return indeks_najmniejszej_wartosci;
}

void zamien(int tablica[], int pierwszy_indeks, int drugi_indeks)
{
    int tymczas=tablica[pierwszy_indeks];
    tablica[pierwszy_indeks]=tablica[drugi_indeks];
    tablica[drugi_indeks]=tymczas;
}

void wyswietlTablice(int tablica[], int rozmiar)
{
    cout<<"{";
    for(int i=0; i<rozmiar; i++)
    {
        if (i!=0)
            {
                cout<<",";
            }
        cout<<tablica[i];
    }
    cout<<"}";
}



int main()
{
  int tablica[5000];
  srand(time(NULL));
  for (int i=0; i<5000; i++)
   {
      tablica[i]=rand()%100;
   }
   cout<<"Witaj, wybierz rozmiar tablicy, jaka chcesz uzyskac:\n";
   cin>>rozmiar;
  cout<<"Tablica wejsciowa: ";
  wyswietlTablice(tablica, rozmiar);
  cout<<"\n";
  sortuj(tablica, rozmiar);
  cout<<"Tablica posortowana: ";
  wyswietlTablice(tablica, rozmiar);
  cout<<"\n\n";
  cout<<"Najmniejsza wartosc: "<<tablica[0]<<"\n";
  cout<<"Wartosc srednia: "<<tablica[rozmiar/2]<<"\n";
  cout<<"Wartosc najwyzsza: "<<tablica[rozmiar-1]<<"\n";
  cin.ignore();
  cin.get();
}





