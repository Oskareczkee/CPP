#include <iostream>
#include <ctime>
#include <cstdlib>

struct lista
{
    int x;
    lista *nastepny;
};

int random()
{
    return rand()%(100-1+1)+1;
}

using namespace std;
////////////////////////////////////////zadanie 1//////////////////////////////////////////////
int pot(int &x, int&y)
{
    if(y==0)
    {
        return 1;
    }
    return x=x*pot(x, --y);
}

void potegowanie()
{
    int x;
    int y;
    cout<<"Wpisz liczbe, ktora chcesz potegowac: ";
    cin>>x;
    cout<<"\nIle razy chcesz spotegowac ta liczbe :";
    cin>>y;
    cout<<"Wynik potegowania to: "<<pot(x,y);
}
/////////////////////////////////////zadanie 1//////////////////////////////////////////////////
/////////////////////////////////////zadanie 2//////////////////////////////////////////////////
int tabodwr(int tablica[], int rozmiar, int x)
{
    if(x<rozmiar-1)
    {
        tabodwr(tablica, 10, x+1);
    }
    cout<<"\n"<<tablica[x];
}

void zadanie2()
{
    int tablica[10];
    for(int x=0;x<10;x++)
    {
        tablica[x]=random();
    }
    cout<<"Normalna tablica: \n";
    for(int x=0;x<10;x++)
    {
        cout<<x+1<<"."<<tablica[x]<<"\n";
    }
    cout<<"\n\nOdwrocona tablica: \n";
    tabodwr(tablica, 10, 0);
}
///////////////////////////////////zadanie 2///////////////////////////////////////////////////
///////////////////////////////////zadanie 3///////////////////////////////////////////////////
lista *generujliste(lista *&elementylisty)
{
  lista *nowyelement=new lista;
  nowyelement->x=random();
  nowyelement->nastepny=elementylisty;
  return nowyelement;
}

void wyswietlliste(lista *&elementylisty)
{
    lista *biezacy=elementylisty;
    for(int x=1;biezacy!=NULL;x++)
    {
        cout<<x<<"."<<biezacy->x<<"\n";
        biezacy=biezacy->nastepny;
    }
}

lista *usunelementlisty(lista*&elementylisty, int place, lista*&biezacy, lista*&poprzedni, int wyk)
{
    int x=1;
    if(place==1&&wyk==0)
    {
        elementylisty=elementylisty->nastepny;
        delete biezacy;
        return elementylisty;
    }
    if(x<=place-1)
    {
        wyk=1;
        poprzedni=biezacy;
        biezacy=biezacy->nastepny;
        usunelementlisty(elementylisty, place-1, biezacy, poprzedni, wyk);
    }
    poprzedni->nastepny=biezacy->nastepny;
    delete biezacy;
    return elementylisty;
}

lista *dodajelementlisty(lista *&elementylisty, int place, int &wartosc, lista*&biezacy, lista *&poprzedni,int wyk)
{
   int x=1;
   if(place==1&&wyk==0)
   {
       lista *nowyelement= new lista;
       nowyelement->x=wartosc;
       nowyelement->nastepny=elementylisty;
       elementylisty=nowyelement;
       return nowyelement;
   }
   if(x<=place-1)
   {
       wyk=1;
     poprzedni=biezacy;
     biezacy=biezacy->nastepny;
     dodajelementlisty(elementylisty, place-1, wartosc, biezacy, poprzedni,wyk);
   }
   lista *nowyelement=new lista;
   poprzedni->nastepny=nowyelement;
   nowyelement->x=wartosc;
   nowyelement->nastepny=biezacy;
   return nowyelement;
}

void zadanie3()
{
  int opcja;
  int liczba;
  int place;
  int wartosc;
  lista *elementylisty=NULL;
  lista *poprzedni=NULL;
  lista *biezacy=NULL;



  cout<<"Wpisz rozmiar listy, ktora chcesz wygenerowac: ";
  cin>>liczba;
  for(int x=0; x<liczba;x++)//Tworzenie listy
  {
  elementylisty=generujliste(elementylisty);
  }
  biezacy=elementylisty;
  cout<<"Wygenerowana lista:\n\n";
  wyswietlliste(elementylisty);
  biezacy=elementylisty;
  while(opcja!=0)
  {
  cout<<"\n\nCo chcesz zrobic z lista: \n1.Dodaj element do listy\n2.Usun element z listy\n0.Wyjdz z programu\n";
  cin>>opcja;
  switch (opcja)
  {
  case 1:
      {
    cout<<"Wybierz miejsce, gdzie chcesz dodac nowy element: ";
    cin>>place;
    if(place<=0)
    {
        cout<<"\nNie mozesz dodawac ujemnych elementow !\n";
        break;
    }
    else if(place>liczba)
    {
        cout<<"\nNie mozesz dodawac elementow listy poza liste !\n";
        break;
    }
    cout<<"Wpisz wartosc elementu: ";
    cin>>wartosc;
    dodajelementlisty(elementylisty, place, wartosc, biezacy, poprzedni, 0);
    liczba++;
    biezacy=elementylisty;
    poprzedni=elementylisty;
    cout<<"Nowa lista:\n\n";
    wyswietlliste(elementylisty);
    cout<<"\n\n";
    break;
      }
  case 2:
      cout<<"Ktory element chcesz usunac ? \n";
      cin>>place;
       if(place<=0)
    {
        cout<<"\nNie mozesz usuwac ujemnych elementow !\n";
        break;
    }
    else if(place>liczba)
    {
        cout<<"\nNie mozesz usuwac elementow listy spoza listy !\n";
        break;
    }
    usunelementlisty(elementylisty, place, biezacy, poprzedni, 0);
    liczba--;
    biezacy=elementylisty;
    poprzedni=elementylisty;
    cout<<"Nowa lista:\n\n";
    wyswietlliste(elementylisty);
    cout<<"\n\n";
    break;
  case 0:
    break;
  default:
    cout<<"\nWpisales nieodpowiednia wartosc !\n\n";
  }
  }
  //usuwanie listy z pamieci
  while(elementylisty!=NULL)
  {
      biezacy=elementylisty;
      elementylisty=biezacy->nastepny;
      delete biezacy;
  }
  delete biezacy;
  delete poprzedni;
  delete elementylisty;//na wszelki wielki wypadek
}
//////////////////////////////////zadanie 3///////////////////////////////////////////////////
//////////////////////////////////zadanie 4///////////////////////////////////////////////////

void wyswietltablice(int **tablica, int w1, int w2)
{
     for(int x=0;x<w1;x++)
   {
       cout<<"\n";
       for(int y=0;y<w2;y++)
       {
           cout<<x+1<<"."<<y+1<<"  "<<tablica[x][y]<<"\n";
       }
   }
}

int znajdzelementywtablicy(int **tablica, int &w1, int &w2, int liczba, int x, int y)//moze kiedys to naprawie, bo mi sie juz nie chce hehhe
{
  if(x<=w1&&y<=w2)
  {
      if(tablica[x][y]==liczba)
      {
          cout<<"\nSzukana przez ciebie liczba zostala znaleziona w ["<<x+1<<"]["<<y+1<<"]"<<"\n";
          return 0;
      }
     if(y<=w2)
     {
        znajdzelementywtablicy(tablica, w1,w2,liczba,x,y+1);

     }
      y=0;
      else
      {
        y=0;
        znajdzelementywtablicy(tablica, w1,w2,liczba,x+1,y);
      }

  }
}


void zadanie4()
{
    int **tablica=NULL;
    int w1;
    int w2;
    int liczba;


    cout<<"Podaj pierwszy wymiar swojej tablicy: ";
    cin>>w1;
    tablica=new int*[w1];
    cout<<"Podaj drugi wymiar swojej tablicy: ";
    cin>>w2;
    for(int x=0;x<=w1;x++)
    {
        tablica[x]=new int[w2];
    }
    for(int x=0;x<w1;x++)
    {
        for(int y=0;y<w2;y++)
        {
            tablica[x][y]=random();
        }
    }
    cout<<"Tablica:\n ";
    wyswietltablice(tablica, w1, w2);
    while(liczba!=-1)
    {
        cout<<"\nJaka wartosc w tablicy chcesz wyszukac ?(-1 wylacza program)\n";
        cin>>liczba;
        znajdzelementywtablicy(tablica, w1, w2, liczba, 0,0);
    }

}

/////////////////////////////////zadanie 4///////////////////////////////////////////////////
int main()
{
    srand(time(NULL));
    int opcja;
   cout<<"Witaj w programie do wyswietlania rekurencji\n";
   while(1)
   {
   cout<<"\nWcisnij 0 aby wyjsc\n1-3 odpala zadania\n\n";
   cin>>opcja;
   if(opcja==0)
    break;
   switch(opcja)
   {
   case 1:
    potegowanie();
    break;
   case 2:
    zadanie2();
    break;
   case 3:
    zadanie3();
    break;
   case 4:
    zadanie4();
    break;
   default:
    cout<<"Wpisales nieodpowiednia wartosc !\n";
    break;
   }
   }
}
