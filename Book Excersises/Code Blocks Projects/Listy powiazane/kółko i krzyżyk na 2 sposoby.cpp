#include <iostream>

using namespace std;

struct pole
{
    int wartosc;//0 - puste //1- kolko//10- krzyzyk
    int numerpola;
    pole *nastepne;
};

void kolkoikrzyzyktablica()
{

}

pole *Generujpole(pole *&poczatek, int &liczbapol)
{

        pole *nowepole=new pole;
        nowepole->wartosc=0;
        liczbapol++;
        nowepole->nastepne=poczatek;
}

void drukujTablice(pole *&poczatek)
{
    pole *biezacy=poczatek;
    for(int x=1;x<=9;x++)
    {
        biezacy->numerpola=x;
       switch(biezacy->wartosc)
       {
       case 0:
        cout<<"  "<<biezacy->numerpola<<"  ";
        break;
       case 1:
        cout<<"  O  ";
        break;
       case 10:
        cout<<"  X  ";
        break;
       default:
        cout<<"Blad!";
        break;
       }
       if(x%3==0)
       {
           cout<<"\n";
       }
       biezacy=biezacy->nastepne;
    }
}

pole *postawznak(pole *&poczatek, int &numer, int &gracz)
{
    pole *biezacy=poczatek;
    for(int x=1;x<=numer;x++)
    {
        if(x==numer)
        {
            if(biezacy->wartosc!=0)
            {
                cout<<"Te pole jest zajete !\n";
                gracz=2;
                break;
            }
            switch(gracz)
            {
            case 0:
                biezacy->wartosc=1;
                return poczatek;
                break;
            case 1:
                biezacy->wartosc=10;
                return poczatek;
                break;
            }
        }
        biezacy=biezacy->nastepne;
    }
}


//Projekt nie dokonczony, bo nie chcialo mi sie pisac beznadziejnego algorytmu do szukania wygranej
void kolkoikrzyzyklista()
{
    cout<<"Witaj w kolko i krzyzyk napisanym na listach powiazanych !\nWprowadzenie wartosci 0 w grze wylaczy ja !\nWcisnij cokolwiek, aby rozpoczac zabawe\n\n";


    int liczbapol=1;
    int wygrana;
    int numer;
    int gracz;//0 - kolko// 1-krzyzyk
    pole *poczatek=NULL;
    int wyjdz;


    //genereacja planszy
    for(int x=0;x<9;x++)
    {
        poczatek=Generujpole(poczatek, liczbapol);
    }
    cout<<"Poczatkowy stan tablicy:\n";
    while(wygrana!=1)
    {
        if(wyjdz==1)
        {
            break;
        }
        cout<<"Tura kolka !\n";
        while(1)
        {
        gracz=0;
        drukujTablice(poczatek);
        cout<<"Wybierz pole na ktorym chcesz postawic znak: ";
        cin>>numer;
        if(numer==0)
        {
            wyjdz=1;
            break;
        }
        postawznak(poczatek, numer, gracz);
        if(gracz==2)
        {
            system("cls");
            continue;
        }
        drukujTablice(poczatek);
        system("cls");
        break;
        }
        if(wyjdz==1)
        {
            break;
        }
        cout<<"Tura krzyzyka !\n";
        while(1)
        {
           gracz=1;
        drukujTablice(poczatek);
        cout<<"Wybierz pole na ktorym chcesz postawic znak: ";
        cin>>numer;
           if(numer==0)
        {
            wyjdz=1;
            break;
        }
        postawznak(poczatek, numer, gracz);
        if(gracz==2)
        {
            system("cls");
            continue;
        }
        drukujTablice(poczatek);
        system("cls");
        break;
        }
    }
}

int main()
{
    int opcja;
  cout<<"Witaj w kolko i krzyzyk !\n\nWcisnij 1 aby zagrac w wersje na tablicach\nWcisnij 2 aby zagrac w wersje na listach powiazanych\nWcisnij 3 aby wylaczyc program\n";
  while(1)
  {
      cin>>opcja;
      if(opcja==3)
      {
          break;
      }
      switch(opcja)
      {
      case 1:
        kolkoikrzyzyktablica();
        break;
      case 2:
        kolkoikrzyzyklista();
        break;
      default:
        cout<<"Wpisana przez ciebie wartosc jest nieprawidlowa !\n";
        break;
      }
  }
}
