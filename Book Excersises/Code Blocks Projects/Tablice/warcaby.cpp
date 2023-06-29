#include <iostream>
#include <string>

using namespace std;
int x;        int blad;          int bozena=0;
int y;        int opcja;         int bicie=0;
int z;        int bialePionki;   int remis=0;
int h;        int czarnePionki;  int a=z-x;//Zmienna pomagajaca obliczyc ruch damek
int proby=0;  int ruchDamka=0;//MEH MOGLEM SOBIE UPROSCIC ZADANIE TYM, ALE ZAPOMNIALEM O TYM xD


int tablica[9][9];
int main();
int czarne();
int biale();
void formulkaRozpoczynajaca()
{
    cout<<"Witaj w warcabach napisanych przez Oskara Niedzwiedzkiego !\n\n\n"
    <<"Aby rozpoczac gre wcisnij 1\n"
    <<"Aby zaznajomic sie z zasadami rozgrywki wcisnij 2\n"
    <<"Aby wejsc w menu opcji gry wcisnij 3\n"
    <<"Aby zakonczyc dzialanie programu wcisnij 4\n\n";
}
void zasady()
{
  cout<<"\n\n"
  <<"A oto i zasady:\n\n-Plansza ma rozmiary 8x8\n-rozgrywke zaczyna kolor bialy (oznaczony B)\n"
  <<"-Poruszamy sie pionkami po przekatnych\n-Gdy dotrzemy do koncowego pola przeciwnika zdobywamy damke mogaca pzemierzyc dowolna ilosc pol w linii prostej\n"
  <<"-Podczas rozgrywki mozna zaglosowac na remis, wystarczy przy pierwszej wartosci podac 0,\n gdy obaj gracze zgodza sie na remis gra zostanie zakonczona remisem\n"
  <<"-Warto zajrzec w opcje i dostosowac opcjonalne zasady rozgrywki pod siebie\n\n";
    cout<<"\n\n"
    <<"Jak poruszac sie i zbijac na planszy\n\n-Aby poruszyc pionek, trzeba wpisac najpierw wartosc x (liczby ustawione pionowo) wcisnac Enter,\n"
    <<" potem podac wartosc y (liczby ustawione poziomo) wcisnac enter,\n wtedy nasz pionek powinien sie poruszyc na wyznaczone pole (o ile mozemy).\n\n"
    <<"Aby zbic pionek trzeba postepowac tak jak powyzej, jednak przy podawaniu wartosci gdzie chcemy umiescic nasz pionek,\n"
    <<"nalezy wybrac wartosc pionka, ktory chcemy zbic\n\nMilej Zabawy !\n\n";
    cout<<"Aby rozpoczac gre wcisnij 1\n"
    <<"Aby zaznajomic sie z zasadami rozgrywki wcisnij 2\n"
    <<"Aby wejsc w menu opcji gry wcisnij 3\n"
    <<"Aby zakonczyc dzialanie programu wcisnij 4\n\n";
}
int plansza()
{
    int sl;//smieszna liczba
    string yy;
  cout<<"       1     2     3     4     5     6     7     8   \n"
  <<"    |-----|-----|-----|-----|-----|-----|-----|-----|";
   for(x=1;x<9;x++)
   {   if(x==1)
       {
       cout<<"\n";
       }
       if(x%2==1)//PRZYPADEK 1/////////////////////////////////////////////////
       {
           for(y=1;y<9;y++)
       {
           if (x<4)//PIONKI BIALE /////////////////////////////////////////////
           {
           if (y%2==1)
           {
               if (proby==0)
               {
               yy="B";
               sl=1;
               if(sl==1)
               {
                   tablica[x][y]=10;
               }
               }
               else
               {
                   switch (tablica[x][y])
                   {
                   case 1:
                    yy=" ";
                    break;
                   case 13:
                    yy="C";
                    break;
                   case 10:
                    yy="B";
                    break;
                   case 20:
                    yy="*";
                    break;
                   case 26:
                    yy="&";
                    break;
                   default:
                    yy="blad";
                    break;
                   }

               }
           }
           else
           {
               yy=" ";
           }
           }
           else if(x==5)//PUSTE POLA NA SRODKU
           {
               if (y%2==1)
               {
                    if (proby==0)
               {
               yy=" ";
               sl=1;
               if(sl==1)
               {
                   tablica[x][y]=1;
               }
               }
               else
               {
                   switch (tablica[x][y])
                   {
                   case 1:
                    yy=" ";
                    break;
                   case 13:
                    yy="C";
                    break;
                   case 10:
                    yy="B";
                    break;
                    case 20:
                    yy="*";
                    break;
                   case 26:
                    yy="&";
                    break;
                   default:
                    yy="blad";
                    break;
                   }

               }
               }
               else
               {
                    yy=" ";
               }
           }
           else if(x>5)//PIONKI CZARNE /////////////////////////////////////
           {
               if (y%2==1)
           {
                if (proby==0)
               {
               yy="C";
               sl=1;
               if(sl==1)
               {
                   tablica[x][y]=13;
               }
               }
               else
               {
                   switch (tablica[x][y])
                   {
                   case 1:
                    yy=" ";
                    break;
                   case 13:
                    yy="C";
                    break;
                   case 10:
                    yy="B";
                    break;
                    case 20:
                    yy="*";
                    break;
                   case 26:
                    yy="&";
                    break;
                   default:
                    yy="blad";
                    break;
                   }

               }
           }
           else
           {
               yy=" ";
           }
           }
           if (y==1)
           {
           cout<<"  "<<x<<" |  "<<yy<<"  ";
           }
           else
           {
               cout<<"|  "<<yy<<"  ";
           }
           if(y==8)
           {
               cout<<"|\n    |-----|-----|-----|-----|-----|-----|-----|-----|\n";
           }
       }
       }
       if(x%2==0)//PRZYPADEK 2/////////////////////////////////////////////////
       {
           for(y=1;y<9;y++)
       {
           if (x<4)//PIONKI BIALE /////////////////////////////////////////////
           {
           if(y%2==0)
           {
                if (proby==0)
               {
               yy="B";
               sl=1;
               if(sl==1)
               {
                   tablica[x][y]=10;
               }
               }
               else
               {
                   switch (tablica[x][y])
                   {
                   case 1:
                    yy=" ";
                    break;
                   case 13:
                    yy="C";
                    break;
                   case 10:
                    yy="B";
                    break;
                    case 20:
                    yy="*";
                    break;
                   case 26:
                    yy="&";
                    break;
                   default:
                    yy="blad";
                    break;
                   }

               }
           }
           else
           {
               yy=" ";
           }
           }
           else if(x==4)//PUSTE POLA NA SRODKU
           {
               if (y%2==0)
               {
                    if (proby==0)
               {
               yy=" ";
               sl=1;
               if(sl==1)
               {
                   tablica[x][y]=1;
               }
               }
               else
               {
                   switch (tablica[x][y])
                   {
                   case 1:
                    yy=" ";
                    break;
                   case 13:
                    yy="C";
                    break;
                   case 10:
                    yy="B";
                    break;
                    case 20:
                    yy="*";
                    break;
                   case 26:
                    yy="&";
                    break;
                   default:
                    yy="blad";
                    break;
                   }

               }
               }
               else
               {
                    yy=" ";
               }
           }
           else if(x>5)//PIONKI CZARNE /////////////////////////////////////
           {
               if (y%2==0)
           {
                if (proby==0)
               {
               yy="C";
               sl=1;
               if(sl==1)
               {
                   tablica[x][y]=13;
               }
               }
               else
               {
                   switch (tablica[x][y])
                   {
                   case 1:
                    yy=" ";
                    break;
                   case 13:
                    yy="C";
                    break;
                   case 10:
                    yy="B";
                    break;
                    case 20:
                    yy="*";
                    break;
                   case 26:
                    yy="&";
                    break;
                   default:
                    yy="blad";
                    break;
                   }

               }
           }
           else
           {
               yy=" ";
           }
           }
           if (y==1)
           {
           cout<<"  "<<x<<" |  "<<yy<<"  ";
           }
           else
           {
               cout<<"|  "<<yy<<"  ";
           }
           if(y==8)
           {
               cout<<"|\n    |-----|-----|-----|-----|-----|-----|-----|-----|\n";
           }
       }
       }
   }
   proby=1;
}
//B£ÊDY I OPCJE///////////

int sprawdzBiciePoBiciu()
{
    if(bicie==1)
    {

    }
}

int sprawdzMozliwoscRuchu()
{
    if(tablica[x][y]==10||tablica[x][y]==13)
    {
    if((z==x+1||z==x-1)&&(h==y+1||h==y-1))
    {
        return 0;
    }

    else
    {
        cout<<"\n\nNie mozesz wykonac takiego ruchu !\n";
        blad=1;
    }
    }
    else if(tablica[x][y]==1||tablica[x][y]==0)
    {
        cout<<"\n\nNa tym polu nie ma pionka lub takie bicie jest nie mozliwe !\n\n";
        blad=1;
    }
    else if(tablica[x][y]==20||tablica[x][y]==26)//RUCH DAMEK////////////////////////
    {
        //Ruchy damkami nie dziala poprawnie, nalezy to naprawic
        if(z==(x+a))
        {
            if((y>h)&&(y+a==h))
            {
           switch(tablica[x][y])
           {
           case 20:
            tablica[z][h]==20;
            tablica[x][y]==1;
            break;
           case 26:
            tablica[z][h]==26;
            tablica[x][y]==1;
            break;
           }
            }
            else if((y<h)&&(y-a==h))
            {
                switch(tablica[x][y])
           {
           case 20:
            tablica[z][h]==20;
            tablica[x][y]==1;
            break;
           case 26:
            tablica[z][h]==26;
            tablica[x][y]==1;
            break;
           }
            }
        }
        else
        {
            cout<<"\n\nTaki ruch damka nie jest mozliwy !\n\n";
            blad=1;
        }
    }
}

int sprawdzBicieBiale()
{
    if(tablica[z][h]==13||tablica[z][h]==26)
    {
     if((z==x+1)&&(h==y+1))
     {
         if (tablica[z+1][h+1]==10||tablica[z+1][h+1]==13||tablica[z+1][h+1]==20||tablica[z+1][h+1]==26)
         {

            cout<<"\n\nNie mozesz wykonac takiego bicia !\n\n";
         blad=1;
         }
         else
         {
             bicie=1;
             tablica[x][y]=1;
              tablica[z][h]=1;
              if(z+1==8)
              {
              tablica[z+1][h+1]=20;
              }
              else
                tablica[z+1][h+1]=10;
         }
     }
     else if((z==x+1)&&(h==y-1))
     {
         if (tablica[z+1][h-1]==10||tablica[z+1][h-1]==13||tablica[z+1][h-1]==20||tablica[z+1][h-1]==26)
         {
            cout<<"\n\nNie mozesz wykonac takiego bicia !\n\n";
         blad=1;
         }
         else
         {
             bicie=1;
             tablica[x][y]=1;
              tablica[z][h]=1;
              if(z+1==8)
              {
              tablica[z+1][h-1]=20;
              }
              else
                tablica[z+1][h-1]=10;
         }
     }
    }
    else if(tablica[z][h]==1)
    {
        return 0;
    }
    else
    {
        cout<<"\nNie mozesz zbic swojego wlasnego pionka !\n\n";
        blad=1;
    }
}

int sprawdzBicieBialeDamki()
{
    if(tablica[z][h]==13||tablica[z][h]==26)
    {
        if(h==y-(x-z))
        {
            if(tablica[z-1][h+1]==10||tablica[z-1][h+1]==13||tablica[z-1][h+1]==20||tablica[z-1][h+1]==26)
            {
                cout<<"\nTakie bicie nie jest mozliwe !\n\n";
                blad=1;
                bozena=1;
            }
            else if(bozena==0)
            {
                tablica[z][h]=1;
                tablica[z-1][h+1]==20;
            }
            else if(1)
            {
            bozena=0;
            blad=0;
            }
            else if(tablica[z-1][h-1]==10||tablica[z-1][h-1]==13||tablica[z-1][h-1]==20||tablica[z-1][h-1]==26)
            {
                cout<<"\nTakie bicie nie jest mozliwe !\n\n";
                blad=1;
                bozena=1;
            }
            else if(bozena==0)
            {
                tablica[z][h]=1;
                tablica[z-1][h-1]==20;
            }
            else if(1)
            {
            bozena=0;
            blad=0;
            }
        }
        else if (h==y+(x-z))
        {
            if(tablica[z+1][h-1]==10||tablica[z+1][h-1]==13||tablica[z+1][h-1]==20||tablica[z+1][h-1]==26)
            {
                cout<<"\nTakie bicie nie jest mozliwe !\n\n";
                blad=1;
                bozena=1;
            }
            else if(bozena==0)
            {
                tablica[z][h]=1;
                tablica[z+1][h-1]==20;
            }
            else if(1)
            {
            bozena=0;
            blad=0;
            }
            else if(tablica[z+1][h+1]==10||tablica[z+1][h+1]==13||tablica[z+1][h+1]==20||tablica[z+1][h+1]==26)
            {
                cout<<"\nTakie bicie nie jest mozliwe !\n\n";
                blad=1;
            }
            else if(bozena==0)
            {
                tablica[z][h]=1;
                tablica[z+1][h+1]==20;
            }
            bozena=0;
        }
        else
        {
            cout<<"\nNie mozesz zbic swojego wlasnego pionka !\n\n";
            blad=1;
        }
    }
}

int sprawdzBicieCzarneDamki()
{
   if(tablica[z][h]==10||tablica[z][h]==20)
    {
        if(h==y-(x-z))
        {
            if(tablica[z-1][h+1]==10||tablica[z-1][h+1]==13||tablica[z-1][h+1]==20||tablica[z-1][h+1]==26)
            {
                cout<<"\nTakie bicie nie jest mozliwe !\n\n";
                blad=1;
                bozena=1;
            }
            else if(bozena==0)
            {
                tablica[z][h]=1;
                tablica[z-1][h+1]==26;
            }
            else if(1)
            {
            bozena=0;
            blad=0;
            }
            else if(tablica[z-1][h-1]==10||tablica[z-1][h-1]==13||tablica[z-1][h-1]==20||tablica[z-1][h-1]==26)
            {
                cout<<"\nTakie bicie nie jest mozliwe !\n\n";
                blad=1;
                bozena=1;
            }
            else if(bozena==0)
            {
                tablica[z][h]=1;
                tablica[z-1][h-1]==26;
            }
            else if(1)
            {
            bozena=0;
            blad=0;
            }
        }
        else if (h==y+(x-z))
        {
            if(tablica[z+1][h-1]==10||tablica[z+1][h-1]==13||tablica[z+1][h-1]==20||tablica[z+1][h-1]==26)
            {
                cout<<"\nTakie bicie nie jest mozliwe !\n\n";
                blad=1;
                bozena=1;
            }
            else if(bozena==0)
            {
                tablica[z][h]=1;
                tablica[z+1][h-1]==26;
            }
            else if(1)
            {
            bozena=0;
            blad=0;
            }
            else if(tablica[z+1][h+1]==10||tablica[z+1][h+1]==13||tablica[z+1][h+1]==20||tablica[z+1][h+1]==26)
            {
                cout<<"\nTakie bicie nie jest mozliwe !\n\n";
                blad=1;
            }
            else if(bozena==0)
            {
                tablica[z][h]=1;
                tablica[z+1][h+1]==26;
            }
            bozena=0;
        }
        else
        {
            cout<<"\nNie mozesz zbic swojego wlasnego pionka !\n\n";
            blad=1;
        }
    }
}

int sprawdzBicieCzarne()
{
    if(tablica[z][h]==10||tablica[z][h]==20)
    {
     if((z==x-1)&&(h==y+1))
     {
         if (tablica[z-1][h+1]==10||tablica[z-1][h+1]==13||tablica[z-1][h+1]==20||tablica[z-1][h+1]==26)
         {

            cout<<"\n\nNie mozesz wykonac takiego bicia !\n\n";
         blad=1;
         }
         else
         {
             bicie=1;
             tablica[x][y]=1;
              tablica[z][h]=1;
              if(z-1==1)
              {
              tablica[z-1][h+1]=26;
              }
              else
                tablica[z-1][h+1]=13;
         }
     }
     else if((z==x-1)&&(h==y-1))
     {
         if (tablica[z-1][h-1]==10||tablica[z-1][h-1]==13||tablica[z-1][h-1]==20||tablica[z-1][h-1]==26)
         {
            cout<<"\n\nNie mozesz wykonac takiego bicia !\n\n";
         blad=1;
         }
         else
         {
              bicie=1;
              tablica[x][y]=1;
              tablica[z][h]=1;
              if(z-1==1)
              {
              tablica[z-1][h-1]=26;
              }
              else
                tablica[z-1][h-1]=13;
         }
     }
    }
    else if(tablica[z][h]==1)
    {
        return 0;
    }
    else
    {
        cout<<"\nNie mozesz zbic swojego wlasnego pionka !\n\n";
        blad=1;
    }
}

int sprawdzIloscPionkow()
{
    czarnePionki=0;
    bialePionki=0;
    for(int i=1;i<9;i++)
    {
        for (int k=1;k<9;k++)
        {
            if (tablica[i][k]==10||tablica[i][k]==20)
            {
                bialePionki++;
            }
            if (tablica[i][k]==13||tablica[i][k]==26)
            {
                czarnePionki++;
            }
        }
    }
}

//B³ÊDY I OPCJE/////////////
int biale()
{
    cout<<"\n\nRuch bialych\n\n";
    plansza();
    if(remis==1)
       {
           cout<<"\n\nPrzeciwnik glosuje za remisem, aby zaglosowac za, wcisnij 0\n";
           cin>>x;
           if(x==0)
           {
               remis++;
               if (remis==2)
               {
                   cout<<"\n\nRozgrywka zakonczona remisem !\n\n\n\n";
                   remis=0;
                   main();
               }
           }
           else
           {
            remis=0;
            czarne();
           }

       }
    do
    {
        do
        {
       bicie=0;
       blad=0;
       ruchDamka=0;
       cout<<"\nWybierz pole, na ktorym znajduje sie pionek, ktorym chcesz sie poruszyc\n";
       cin>>x;
       if (x==0)
       {
        cout<<"Zaglosowales na remis, czekanie na glos przeciwnika...\n\n";
        remis++;
        czarne();
       }
       cin>>y;
       if(tablica[x][y]==13||tablica[x][y]==26)
       {
           cout<<"\nNie mozesz poruszac sie pionkami przeciwnika !\n\n";
           blad=1;
       }
       else if(tablica[x][y]==20)
       {
           ruchDamka=1;
       }
       if(blad==0)
       {
       cout<<"Wybierz pole, na ktore chcesz przejsc\n";
       cin>>z>>h;
       }
       //SPRAWDZANIE CZY RUCH JEST DOZWOLONY/////////////////////
       if(ruchDamka==1)
       {
           sprawdzMozliwoscRuchu();
           if(blad==0)
           {
           sprawdzBicieBialeDamki();
           }
       }
        }while (blad!=0);
       if (ruchDamka==0)
       {
       for(int j=0;j<5;j++)
        switch(j)
       {
       case 0:
        sprawdzMozliwoscRuchu();
        break;
       case 1:
           if(blad==0)
           {
        sprawdzBicieBiale();
           }
        break;
       default:
        break;
       }
       if (blad==0&&bicie==0)
          {
             tablica[x][y]=1;
             if(z==8)
             {
             tablica[z][h]=20;
             }
             else
             {
                 tablica[z][h]=10;
             }
          }
       }
    }while(blad!=0);
}

int czarne()
{

       cout<<"\n\nRuch czarnych\n\n";
       plansza();
       if(remis==1)
       {
           cout<<"\n\nPrzeciwnik glosuje za remisem, aby zaglosowac za, wcisnij 0\n";
           cin>>x;
           if(x==0)
           {
               remis++;
               if (remis==2)
               {
                   cout<<"\n\nRozgrywka zakonczona remisem !\n\n\n\n";
                   remis=0;
                   main();
               }
           }
           else
           {
            remis=0;
            czarne();
           }

       }
    do
    {
        do
        {
       blad=0;
       bicie=0;
       ruchDamka=0;
       cout<<"\nWybierz pole, na ktorym znajduje sie pionek, ktorym chcesz sie poruszyc\n";
       cin>>x;
       if (x==0)
       {
           cout<<"Zaglosowales na remis, czekanie na glos przeciwnika...\n\n";
           remis++;
           biale();

       }
       cin>>y;
       if (tablica[x][y]==10||tablica[x][y]==20)
       {
           cout<<"\nNie mozesz sie poruszac pionkami przeciwnika !\n\n";
           blad=1;
       }
       else if(tablica[x][y]==26)
       {
           ruchDamka=1;
       }
       if(blad==0)
       {
       cout<<"Wybierz pole, na ktore chcesz przejsc\n";
       cin>>z>>h;
       }
       //SPRAWDZANIE CZY RUCH JEST DOZWOLONY/////////////////////
       if(ruchDamka==1)
       {
           sprawdzMozliwoscRuchu();
           if(blad==0)
           {
           sprawdzBicieCzarneDamki();
           }
       }
       }while(blad!=0);
       if (ruchDamka==0)
       {
       for(int j=0;j<5;j++)
        switch(j)
       {
       case 0:
        sprawdzMozliwoscRuchu();
        break;
       case 1:
           if(blad==0)
           {
        sprawdzBicieCzarne();
           }
       default:
        break;
       }
  if (blad==0&&bicie==0)
          {
             tablica[x][y]=1;
             if(z==1)
             {
             tablica[z][h]=26;
             }
             else
             {
                 tablica[z][h]=13;
             }
          }
       }
}while(blad!=0);
}
int opcje()
{
    cout<<"Opcje beda wkrotce dodane !\n\n";
}

int gra()
{
  while(1)
  {
      biale();
      sprawdzIloscPionkow();
      if (bialePionki==0)
      {
          cout<<"\n\n\nCzarne wygraly !\n\n";
          break;
      }
      else if (czarnePionki==0)
      {
          cout<<"\n\n\nBiale wygraly !\n\n";
          break;
      }
      czarne();
      sprawdzIloscPionkow();
      if (bialePionki==0)
      {
          cout<<"\n\n\nCzarne wygraly !\n\n";
          break;
      }
      else if (czarnePionki==0)
      {
          cout<<"\n\n\nBiale wygraly !\n\n";
          break;
      }
  }
}

int main()
{
    formulkaRozpoczynajaca();
    do
    {
    cin>>opcja;
    switch (opcja)
    {
    case 1:
        gra();
        cout<<"Dziekuje za gre, jesli masz ochote to nic nie przeszkadza, by zagrac jeszcze raz\n\nWcisnij dowolny przycisk, aby kontynuowac";
        cin.ignore();
        cin.get();
        formulkaRozpoczynajaca();
        break;
    case 2:
        zasady();
        break;
    case 3:
        opcje();
        break;
    case 4:
        break;
    default:
        cout<<"Musisz wybrac odpowiednia opcje !\n";
        break;
    }
    }while(opcja!=4);
}
