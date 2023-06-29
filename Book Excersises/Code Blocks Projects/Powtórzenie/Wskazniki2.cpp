#include <iostream>
#include <ctime>
#include <cstdlib>


using namespace std;

struct Dane
{
    int iloscznajomych=0;
    int rozmiarznaj=5;
    string imie;
    string *znajomi;
    int *liczbadni;
};



Dane utworznowekonto(int &rozmiar)
{
    Dane nowekonto;
    int *opcja=new int;
    cout<<"Podaj swoje imie: ";
    cin>>nowekonto.imie;
    nowekonto.znajomi=new string[nowekonto.rozmiarznaj];
    nowekonto.liczbadni=new int[nowekonto.rozmiarznaj];
    while(1)
    {
    cout<<"Czy chcesz dodac nowych znajomych ?\n1.Tak\n2.Nie\n";
    cin>>*opcja;
    if(*opcja==2)
    {
        delete opcja;
        break;
    }
    switch(*opcja)
    {
    case 1:
        if(nowekonto.iloscznajomych>=nowekonto.rozmiarznaj-1)
        {
            string *zapasowatablica=new string[nowekonto.rozmiarznaj];
            int *zapasowatablica2=new int[nowekonto.rozmiarznaj];
            for(int x=0;x<nowekonto.rozmiarznaj;x++)
            {
                zapasowatablica[x]=nowekonto.znajomi[x];
                zapasowatablica2[x]=nowekonto.liczbadni[x];
            }
            int *rozmstary=new int(nowekonto.rozmiarznaj);
            delete[]nowekonto.znajomi;
            delete[]nowekonto.liczbadni;
            nowekonto.rozmiarznaj*=2;
            nowekonto.znajomi=new string[nowekonto.rozmiarznaj];
            nowekonto.liczbadni=new int[nowekonto.rozmiarznaj];
            for(int x=0;x<*rozmstary;x++)
            {
                nowekonto.znajomi[x]=zapasowatablica[x];
                nowekonto.liczbadni[x]=zapasowatablica2[x];
            }
            delete[]zapasowatablica;
            delete[]zapasowatablica2;
            delete rozmstary;
        }
        cout<<"Wpisz imie znajomego: ";
        cin>>nowekonto.znajomi[nowekonto.iloscznajomych];
        cout<<"Wpisz liczbe dni od ostatniego kontaktu ze znajomym: ";
        cin>>nowekonto.liczbadni[nowekonto.iloscznajomych];
        nowekonto.iloscznajomych++;
        break;
    case 2:
        break;
    default:
        cout<<"Wybrales nieodpowiednia opcje !\n";
        break;
    }
    }
    return nowekonto;
}

void przegladajkonto(Dane uzytkownicy)
{
    int *opcja=new int;
   cout<<"Twoje imie to: "<<uzytkownicy.imie<<"\n";
   while(1)
   {
   cout<<"Co chcesz zrobic:\n\n1.Lista znajomych\n2.Dodaj znajomego\n3.Aktualizuj liczbe dni od ostatniego kontaktu ze znajomym\n0.Przejdz do menu glownego\n";
   cin>>*opcja;
   switch(*opcja)
   {
   case 1:
       cout<<"Lista znajomych: \n";
    for(int x=0; x<=uzytkownicy.iloscznajomych;x++)
    {
        cout<<x+1<<"."<<uzytkownicy.znajomi[x]<<", "<<uzytkownicy.liczbadni[x]<<"\n";
    }
    cout<<"\n\n";
    break;
   case 2:
       ///////////////////
       if(uzytkownicy.iloscznajomych>=uzytkownicy.rozmiarznaj-1)
        {
            string *zapasowatablica=new string[uzytkownicy.rozmiarznaj];
            int *zapasowatablica2=new int[uzytkownicy.rozmiarznaj];
            for(int x=0;x<uzytkownicy.rozmiarznaj;x++)
            {
                zapasowatablica[x]=uzytkownicy.znajomi[x];
                zapasowatablica2[x]=uzytkownicy.liczbadni[x];
            }
            int *rozmstary=new int(uzytkownicy.rozmiarznaj);
            delete[]uzytkownicy.znajomi;
            delete[]uzytkownicy.liczbadni;
            uzytkownicy.rozmiarznaj*=2;
            uzytkownicy.znajomi=new string[uzytkownicy.rozmiarznaj];
            uzytkownicy.liczbadni=new int[uzytkownicy.rozmiarznaj];
            for(int x=0;x<*rozmstary;x++)
            {
                uzytkownicy.znajomi[x]=zapasowatablica[x];
                uzytkownicy.liczbadni[x]=zapasowatablica2[x];
            }
            delete[]zapasowatablica;
            delete[]zapasowatablica2;
            delete rozmstary;
        }
        ///////////////
    cout<<"\nWpisz imie znajomego: ";
    cin>>uzytkownicy.znajomi[uzytkownicy.iloscznajomych];
    cout<<"\nWpisz liczbe dni od ostatniego kontaktu ze znajomym: ";
    cin>>uzytkownicy.liczbadni[uzytkownicy.iloscznajomych];
    uzytkownicy.iloscznajomych++;
    cout<<"\n\n";
    break;
   case 3:
    cout<<"Wpisz id znajomego: ";
    cin>>*opcja;
    cout<<"\nImie znajomego: "<<uzytkownicy.znajomi[*opcja]<<"\n";
    cout<<"Wpisz liczbe dni od ostatniego kontaktu: ";
    cin>>uzytkownicy.liczbadni[*opcja];
    cout<<"\n\n";
    break;
   default:
       cout<<"Wybrales nieodpowiednia opcje !\n";
       break;

   }
   }
}

void ksiazkazaiscietelefoniczna()
{
    int opcja;
    string imie;
    int rozmiar=5;
    int id=0;
    int wid;
  Dane *uzytkownicy;
  uzytkownicy=new Dane[rozmiar];
  cout<<"Witaj w Programie do zapisywania swoich znajomych i sprawdzania liczby dni od ostatniego kontaktu !\n\n";
  while(1)
  {
cout<<"Aby utworzyc konto nowego uzytkownika wcisnij 1\nAby sprawdzic konto uzytkownika wcisnij 2\n0 Wylacza program\n\n";
cin>>opcja;
if(opcja==0)
{
  break;
}
switch(opcja)
{
case 1:
    uzytkownicy[id]=utworznowekonto(rozmiar);
    id++;
    break;
case 2:
    cout<<"Wpisz id swojego konta: ";
    cin>>wid;
    przegladajkonto(uzytkownicy[wid]);
    break;
default:
    cout<<"Wpisana przez ciebie wartosc jest niepoprawna !\n";
    break;
}
  }



}

void jimmyjociechwyca()
{
    cout<<"\n\n";
    int **wd40;
    int x=3;
    int y=3;
    wd40=new int*[x];
    for(int c=0;c<x;c++)
    {
       wd40[c]=new int[y];
    }
    for(int i=0; i<x;i++)
    {
        for(int w=0;w<y;w++)
       {
          wd40[i][w]=(i+1)*(w+1);
          cout<<wd40[i][w]<<"\n";
       }
    }
    cout<<"Adresy podanych liczb to (w kolejnosci liczb):\n";
    for(int i=0; i<x;i++)
    {
        for(int w=0;w<y;w++)
       {
          wd40[i][w]=(i+1)*(w+1);
          cout<<&wd40[i][w]<<"\n";
       }
    }
    for(int i=0;i<y;i++)
    {
        delete[] wd40[i];
    }
    delete[] wd40;
    wd40=NULL;
    if(wd40==NULL)
    {
        cout<<"Tablica zostala usunieta pomyslnie z pamieci !\n";
    }
    cout<<wd40<<"\n";
}

void jeszczewiekszemnozeniedlauposledzonych()
{
    int ***wx;
    int x;
    int y;
    int z;
    //poczatek tworzenia tablicy wskaznikowej
    cout<<"Wpisz 1 zakres: ";
    cin>>x;
    wx=new int**[x];
    cout<<"Wpisz 2 zakres: ";
    cin>>y;
   for(int c=0;c<x;c++)
   {
       for(int d=0;d<y;d++)
       {
           wx[c]=new int*[d];
       }
   }
   cout<<"Wpisz 3 zakres: ";
   cin>>z;
      for(int c=0;c<x;c++)
   {
       for(int d=0;d<y;d++)
       {
           wx[c][d]=new int [z];
       }
   }
   //nadawanie wartosci, m
   for(int i=0;i<x;i++)
   {
       for(int t=0;t<y;t++)
       {
           for(int r=0; r<z;r++)
           {
               wx[i][t][r]=(i+1)*(t+1)*(r+1);
               cout<<wx[i][t][r]<<"\n";
           }
       }
   }
   //koniec tworzenia tablicy wskaznikowej
   //zwalnianie pamieci
   for(int i=0;i<z;i++)
   {
       for(int u=0;u<y;u++)
       {
           delete[] wx[i][u];
       }
   }
   for(int i=0;i<y;i++)
   {
       delete[] wx[i];
   }
   delete[] wx;
   wx=NULL;
   //koniec zwalniania pamieci
   if(wx==NULL)
   {
       cout<<"\nTablica zostala usunieta pomyslnie z pamieci !\n";
   }
}

void mnozeniedlauposledzonych()
{
    int **wwx;
    int x;
    int y;
    cout<<"Wpisz 1 zakres mnozonych liczb (1-zakres)";
    cin>>x;
    cout<<"\n";
    wwx=new int*[x];
    cout<<"Wpisz 2 zakres mnozonych liczb (1-zakres)";
    cin>>y;
    cout<<"\n";
    for(int a=0; a<x;a++)
    {
        wwx[a]=new int[y];
    }
    for(int i=0; i<x;i++)
    {
        for(int j=0;j<y;j++)
        {
            wwx[i][j]=(i+1)*(j+1);
            cout<<wwx[i][j]<<"\n";

        }
    }
    //zwalnianie pamieci
    for(int i=0; i<y;i++)
    {
        delete[]wwx[i];
    }
    delete[]wwx;
    wwx=NULL;
    //koniec zwalniania pamieci
}

void normalnatabliczka()
{
    int x;
    int y;
    cout<<"Wpisz 1 zakres mnozonych liczb (1-zakres)";
    cin>>x;
    cout<<"Wpisz 2 zakres mnozonych liczb (1-zakres)";
    cin>>y;
    for(int i=0;i<x;i++)
    {
        for(int o=0;o<y;o++)
        {
            cout<<(i+1)*(o+1)<<"\n";
        }
    }
}

int main()
{
    int opcja;
    while(1)
    {
    cin>>opcja;
    if(opcja==0)
        break;
    switch(opcja)
    {
    case 1:
   mnozeniedlauposledzonych();
   break;
    case 2:
        normalnatabliczka();
        break;
    case 3:
        jeszczewiekszemnozeniedlauposledzonych();
        break;
    case 4:
        jimmyjociechwyca();
        break;
    case 5:
        ksiazkazaiscietelefoniczna();
        break;
   default:
   cout<<"Wpisana wartosc jest niepoprawna !\n";
   break;
    }
    }
}
