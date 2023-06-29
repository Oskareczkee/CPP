#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>


using namespace std;

string pole1="0";
string pole2="0";
string pole3="0";
//wp - wartosc pola
int wp1;
int wp2;
int wp3;
int wygrane=0;

void zasady()
{
  cout<<"Oto zasady tego mini jednorekiego bandyty  !\nGre zaczyna sie po wcisnieciu 1, po zagraniu mozna powtarzac az do znudzenia\n\n"
  <<"Wygrana nastepuje, gdy wylosowane kombinacje beda mialy laczna wartosc 3,6,9 lub 12\n\n"
  <<"Symbole maja wartosc:\n*-1\n$-2\n@-3\n&-4\n\nIm wieksza laczna wartosc tym wygrana jest wieksza !\n\n";
}


void plansza()
{
    cout<<"["<<pole1<<"]["<<pole2<<"]["<<pole3<<"]";
}

int wygrana()
{
  int wygrana=wp1+wp2+wp3;
  switch (wygrana)
  {
  case 3:
    cout<<"Brawo wygrales !\n\n";
    cout<<"Laczna wartosc to: "<<wygrana<<"\n";
    wygrane++;
    break;
  case 6:
    cout<<"Brawo wygrales !\n\n";
    cout<<"Laczna wartosc to: "<<wygrana<<"\n";
    wygrane++;
    break;
  case 9:
    cout<<"Brawo wygrales !\n\n";
    cout<<"Laczna wartosc to: "<<wygrana<<"\n";
    wygrane++;
    break;
  case 12:
    cout<<"Brawo wygrales !\n\n";
    cout<<"Laczna wartosc to: "<<wygrana<<"\n";
    wygrane++;
    break;
  }

}

int losowanie()
{
    int kolumna1=rand()%(4-1+1)+1;
    switch (kolumna1)
    {
    case 1:
        pole1="*";
        wp1=1;
        break;
    case 2:
        pole1="$";
        wp1=2;
        break;
    case 3:
        pole1="@";
        wp1=3;
        break;
    case 4:
        pole1="&";
        wp1=4;
        break;
    }
    int kolumna2=rand()%(4-1+1)+1;
      switch (kolumna2)
    {
    case 1:
        pole2="*";
        wp2=1;
        break;
    case 2:
        pole2="$";
        wp2=2;
        break;
    case 3:
        pole2="@";
        wp2=3;
        break;
    case 4:
        pole2="&";
        wp2=4;
        break;
    }
    int kolumna3=rand()%(4-1+1)+1;
      switch (kolumna3)
    {
    case 1:
        pole3="*";
        wp3=1;
        break;
    case 2:
        pole3="$";
        wp3=2;
        break;
    case 3:
        pole3="@";
        wp3=3;
        break;
    case 4:
        pole3="&";
        wp3=4;
        break;
    }
}


int jdnrb()//jednoreki bandyta
{
    int zagraj;
    cout<<"Kliknij cokolwiek aby rozpoczac losowanie !\n";
  do
  {
      cin.get();
      losowanie();
      wygrana();
      plansza();
      cout<<"\nAby zagrac jeszcze raz wcisnij 1, aby nie grac wcisnij jakakolwiek liczbe\n";
      cin>>zagraj;
  }while(zagraj==1);
  cout<<"Dziekuje za gre wygrales "<<wygrane<<" razy\n\n";
}

int main()
{
    int wybor;

    srand(time(NULL));

    cout<<"Witaj w programie symulujacym jednorekiego bandyte !\n";
    while(1)
    {
    cout<<"Aby rozpoczac zabawe wcisnij 1\nAby zapoznac sie z zasadami wcisnij 2\nAby wyjsc wcisnij 3\n\n";
    cin>>wybor;
    if (wybor==3)
        break;
    switch(wybor)
    {
    case 1:
        jdnrb();
        break;
    case 2:
        zasady();
        break;
    default:
        cout<<"Musisz wybrac odpowiednia opcje !\n\n";
        break;
    }
    }
}
