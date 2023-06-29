#include <iostream>
#include <string>
using namespace  std;
//zmienne
int wysokosc;                                 int v;
int szerokosc;                                int wszerokosc;
int **tablica=NULL;                           int wygrana;
int zolte=0;
int czerwone=0;
int sprawdz_mozliwosc_ruchu(int szerokosc, int zolte, int czerwone);
int sprawdz_wygrana(int zwrot, int wszerokosc, int v);
int zwrot=0;
//koniec zmiennych
void plansza(int wysokosc, int szerokosc)
{
    for(int i=0;i<=wysokosc;i++)
  {
      for(int j=0;j<=szerokosc;j++)
      {
          if(j==0)
          {
              cout<<"|";
          }
          switch(tablica[i][j])
          {
          case 0:
            cout<<" |";
            break;
          case 1:
            cout<<"$|";//zolte
            break;
          case 2:
            cout<<"@|";//czerwone
            break;
          default:
            cout<<"*|";
            break;
          }
          if(j==szerokosc)
          {
              cout<<"\n";
          }
      }
  }
}

int sprawdz_mozliwosc_ruchu(int wszerokosc, int zolte, int czerwone)
{
    for(int i=wysokosc;i>=0;i--)
    {
        if(zolte==1)
        {
        if(tablica[i][wszerokosc]==0)
        {
            tablica[i][wszerokosc]=1;
            i=v;
            zwrot=1;
            return 0;
        }
        else if(tablica[i][wszerokosc]==1||tablica[i][wszerokosc]==2)
        {
            continue;
        }
        if(i==wysokosc)
        {
            if(tablica[i][wszerokosc]==1||tablica[i][wszerokosc]==2)
            {
                cout<<"Osiagnieto limit wysokosci !\n\n";
                i=v;
                zwrot=0;
            return 0;
            break;
            }
        }
        }
        if(czerwone==1)
        {
            if(tablica[i][wszerokosc]==0)
        {
            tablica[i][wszerokosc]=2;
            i=v;
            zwrot=1;
            return 0;
        }
        else if(tablica[i][wszerokosc]==1||tablica[i][wszerokosc]==2)
        {
            continue;
        }
        if(i==wysokosc)
        {
            if(tablica[i][wszerokosc]==1||tablica[i][wszerokosc]==2)
            {
                cout<<"Osiagnieto limit wysokosci !\n\n";
                zwrot=1;
                return 0;
                break;
            }
        }
        }
    }
}

int sprawdz_wygrana(int zwrot, int wszerokosc, int v)//Do porawki !!!!!!!!!!!!!!!!!!!!!!!!
{
    int lz=1;
    int bs1=0;
    int bs2=0;//liczba zetonow, ktore spelniaja warunek, sumuje sie je, jesli jest wiecej lub rowno 4 nastepuje wygrana
    if(zwrot==1)
    {
        //przypadek góra dol///////////////////////////////////////////////
        for(int g=1;g<=3;g++)
        {
        if(bs1==0)
        {
            if(tablica[v+g][wszerokosc]==tablica[v][wszerokosc])
            {
                lz++;
            }
            else
            {
                bs1=1;
            }
        }
            if(bs2==0)
            {
                if(tablica[v-g][wszerokosc]==tablica[v][wszerokosc])
                {
                    lz++;
                }
                else
                {
                    bs2=1;
                }
            }
        }
        if(lz>=4)
        {
            wygrana=1;
            return 0;
        }
        else
        {
            bs1=0;
            bs2=0;
        }
        //przypadek lewo prawo/////////////////////////////////////////
        for(int g=1;g<=3;g++)
        {
        if(bs1==0)
        {
            if(tablica[v][wszerokosc+g]==tablica[v][wszerokosc])
            {
                lz++;
            }
            else
            {
                bs1=1;
            }
        }
            if(bs2==0)
            {
                if(tablica[v][wszerokosc-g]==tablica[v][wszerokosc])
                {
                    lz++;
                }
                else
                {
                    bs2=1;
                }
            }
        }
        if(lz>=4)
        {
            wygrana=1;
            return 0;
        }
        else
        {
            bs1=0;
            bs2=0;
        }
        //przeypadek przekotna zwrocona w lewo/////////////////////////////////////////////
        for(int g=1;g<=3;g++)
        {
        if(bs1==0)
        {
            if(tablica[v+g][wszerokosc+g]==tablica[v][wszerokosc])
            {
                lz++;
            }
            else
            {
                bs1=1;
            }
        }
            if(bs2==0)
            {
                if(tablica[v-g][wszerokosc-g]==tablica[v][wszerokosc])
                {
                    lz++;
                }
                else
                {
                    bs2=1;
                }
            }
        }
        if(lz>=4)
        {
            wygrana=1;
            return 0;
        }
        else
        {
            bs1=0;
            bs2=0;
        }
        //przypadek przekotna zwrocona w prawo///////////////////////////////////////////
        for(int g=1;g<=3;g++)
        {
        if(bs1==0)
        {
            if(tablica[v+g][wszerokosc+g]==tablica[v][wszerokosc])
            {
                lz++;
            }
            else
            {
                bs1=1;
            }
        }
            if(bs2==0)
            {
                if(tablica[v+g][wszerokosc+g]==tablica[v][wszerokosc])
                {
                    lz++;
                }
                else
                {
                    bs2=1;
                }
            }
        }
        if(lz>=4)
        {
            wygrana=1;
            return 0;
        }
        else
        {
            bs1=0;
            bs2=0;
            return 0;
        }
        }
    else
    {
        return 0;
    }
    }


void gra()
{
    while(1)
    {
  while(1)
  {
      cout<<"Ruch zoltych\n";
      plansza(wysokosc, szerokosc);
      do
      {
      cout<<"Wpisz, gdzie chcesz wrzucic zeton: ";
      cin>>wszerokosc;
      if(wszerokosc>szerokosc||wszerokosc<0)
      {
          cout<<"\n\nNie mozesz wrzucic zetonu poza plansze !\n\n";
          continue;
      }
      zolte=1;
      czerwone=0;
      sprawdz_mozliwosc_ruchu(wszerokosc, zolte, czerwone);
      if(zwrot==0)
      {
          continue;
      }
      else if(zwrot==1)
      {
          sprawdz_wygrana(zwrot, wszerokosc , v);
          break;
      }
      }while(1);
      break;
  }
  while(1)
  {
      cout<<"Ruch czerwonych\n";
      plansza(wysokosc, szerokosc);
      do
      {
      cout<<"Wpisz, gdzie chcesz wrzucic zeton: ";
      cin>>wszerokosc;
         if(wszerokosc>szerokosc||wszerokosc<0)
      {
          cout<<"\n\nNie mozesz wrzucic zetonu poza plansze !\n\n";
          continue;
      }
      zolte=0;
      czerwone=1;
      sprawdz_mozliwosc_ruchu(wszerokosc, zolte, czerwone);
      if(zwrot==0)
      {
          continue;
      }
      else if(zwrot==1)
      {
          sprawdz_wygrana(zwrot, wszerokosc, v);
          break;
      }
      }while(1);
      break;
  }
    }
}

void czworki()
{
  cout<<"\nWitaj w grze w czworki, aby rozpoczac wcisnij cokolwiek\n";
  cin.ignore();
  cin.get();
  cout<<"Podaj szerokosc planszy: ";
  cin>>szerokosc;
  cout<<"Podaj wysokosc planszy(liczba wierszy): ";
  cin>>wysokosc;
  szerokosc--;
  wysokosc--;
  //inicjacja tabeli
  tablica=new int*[wysokosc];
  for(int i=0;i<=wysokosc;i++)
  {
      tablica[i]=new int[szerokosc];
  }
  //nadawanie wstepnych wartosci tablicy
  for(int i=0;i<=wysokosc;i++)
  {
      for(int j=0;j<=szerokosc;j++)
      {
          tablica[i][j]=0;
      }
  }
  gra();
}



int main()
{
    int opcja;
   cout<<"Witaj w grze w czworki\n";
   do
   {
   cout<<"Aby rozpoczac wcisnij 1, aby wyjsc wcisnij 0\n";
   cin>>opcja;
   if(opcja==0)
    break;
   switch(opcja)
   {
   case 1:
    czworki();
    break;
   default:
    cout<<"Musisz wprowadzic 1 !\n";
    break;
   }
   }while(1);
}

