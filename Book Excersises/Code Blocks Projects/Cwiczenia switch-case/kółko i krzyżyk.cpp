#include <iostream>
#include <string>
using namespace std;

int pole;
int wygrana;
//wp - wartosc pola
int wp1=100;int wp2=100; int wp3=100; int wp4=100;int wp5=100;
int wp6=100; int wp7=100; int wp8=100; int wp9=100;

 string pole1="1";string pole2="2";string pole3="3";
    string pole4="4";string pole5="5";
    string pole6="6";string pole7="7";
    string pole8="8";string pole9="9";

void reset()
{
   wp1=100; wp2=100;  wp3=100;  wp4=100; wp5=100;
 wp6=100;  wp7=100;  wp8=100;  wp9=100;

     pole1="1";
     pole2="2";
     pole3="3";
     pole4="4";
     pole5="5";
     pole6="6";
     pole7="7";
     pole8="8";
     pole9="9";
     pole=0;
     wygrana=0;
}

void zasady()
{
    cout<<"Plansza sklada sie z 9 pol oznaczonych 1-9.\nGre zaczynamy kolkiem\nW kazde pole mozna wstawic kolko lub krzyzyk (w zaleznosci kim gramy)\nWygrywa gracz ktory ustawi pelen rzad znakow lub ustawi je po przekatnej\n";
}
void pole_do_gry()
{
    //Pole do gry
    cout<<"                                           -----------------\n";
    cout<<"                                          |  "<<pole1<<"  |"<<"  "<<pole2<<"  |"<<"  "<<pole3<<"  |\n";
    cout<<"                                          |-----|-----|-----|\n";
    cout<<"                                          |  "<<pole4<<"  |"<<"  "<<pole5<<"  |"<<"  "<<pole6<<"  |\n";
    cout<<"                                          |-----|-----|-----|\n";
    cout<<"                                          |  "<<pole7<<"  |"<<"  "<<pole8<<"  |"<<"  "<<pole9<<"  |\n";
    cout<<"                                           -----------------\n";
    //Koniec pola do gry

}

int wygrana_gra()
{
    //wpp oznacza zliczona wartosc 3 pol, wszystkie mozliwosci wygranej
    int wpp1=wp1+wp2+wp3;
    int wpp2=wp4+wp5+wp6;
    int wpp3=wp7+wp8+wp9;
    int wpp4=wp1+wp4+wp7;
    int wpp5=wp2+wp5+wp8;
    int wpp6=wp3+wp6+wp9;
    int wpp7=wp1+wp5+wp9;
    int wpp8=wp3+wp5+wp7;

    if((wpp1==6)||(wpp2==6)||(wpp3==6)||(wpp4==6)||(wpp5==6)||(wpp6==6)||(wpp7==6)||(wpp8==6))
    {
        wygrana=1;
        cout<<"Krzyzyk wygral !\n\n";
    }
    if((wpp1==0)||(wpp2==0)||(wpp3==0)||(wpp4==0)||(wpp5==0)||(wpp6==0)||(wpp7==0)||(wpp8==0))
    {
        wygrana=1;
        cout<<"Kolko wygralo !\n\n";
    }
    if((0<wpp1&&wpp2&&wpp3&&wpp4&&wpp5&&wpp6&&wpp7&&wpp8)&&(wpp1&&wpp2&&wpp3&&wpp4&&wpp5&&wpp6&&wpp7&&wpp8<6))
    {
        wygrana=1;
        cout<<"Tura zakonczyla sie remisem !\n\n";
    }

}

int kolko()
{
  cout<<"Tura: Kolko\n";
  do
  {
  cout<<"Wybierz pole 1-9\n";
  cin>>pole;
 switch(pole)
 {
case 1:
  if ((wp1==0)||(wp1==2))
    {
        cout<<"Te pole jest zajete !\n\n";
        pole=11;
    }
    pole1="O";
    wp1=0;
    break;
case 2:
      if ((wp2==0)||(wp2==2))
    {
        cout<<"Te pole jest zajete !\n\n";
        pole=11;
    }
    pole2="O";
    wp2=0;
    break;
case 3:
      if ((wp3==0)||(wp3==2))
    {
        cout<<"Te pole jest zajete !\n\n";
        pole=11;
    }
    pole3="O";
    wp3=0;
    break;
case 4:
      if ((wp4==0)||(wp4==2))
    {
        cout<<"Te pole jest zajete !\n\n";
        pole=11;
    }
    pole4="O";
    wp4=0;
    break;
case 5:
      if ((wp5==0)||(wp5==2))
    {
        cout<<"Te pole jest zajete !\n\n";
        pole=11;
    }
    pole5="O";
    wp5=0;
    break;
case 6:
      if ((wp6==0)||(wp6==2))
    {
        cout<<"Te pole jest zajete !\n\n";
        pole=11;
    }
    pole6="O";
    wp6=0;
    break;
case 7:
      if ((wp7==0)||(wp7==2))
    {
        cout<<"Te pole jest zajete !\n\n";
        pole=11;
    }
    pole7="O";
    wp7=0;
    break;
case 8:
      if ((wp8==0)||(wp8==2))
    {
        cout<<"Te pole jest zajete !\n\n";
        pole=11;
    }
    pole8="O";
    wp8=0;
    break;
case 9:
      if ((wp9==0)||(wp9==2))
    {
        cout<<"Te pole jest zajete !\n\n";
        pole=11;
    }
    pole9="O";
    wp9=0;
    break;

default:
    cout<<"Musisz wybrac odpowiednie pole !\n\n";
 }
  }while ((1>pole)||(pole>9));
  pole_do_gry();
}

int krzyzyk()
{
  cout<<"Tura: Krzyzyk\n";
  do
  {
  cout<<"Wybierz pole 1-9\n";
  cin>>pole;
 switch(pole)
 {
case 1:
  if ((wp1==0)||(wp1==2))
    {
        cout<<"Te pole jest zajete !\n\n";
        pole=11;
    }
    pole1="X";
    wp1=2;
    break;
case 2:
  if ((wp2==0)||(wp2==2))
    {
        cout<<"Te pole jest zajete !\n\n";
        pole=11;
    }
    pole2="X";
    wp2=2;
    break;
case 3:
      if ((wp3==0)||(wp3==2))
    {
        cout<<"Te pole jest zajete !\n\n";
        pole=11;
    }
    pole3="X";
    wp3=2;
    break;
case 4:
      if ((wp4==0)||(wp4==2))
    {
        cout<<"Te pole jest zajete !\n\n";
        pole=11;
    }
    pole4="X";
    wp4=2;
    break;
case 5:
  if ((wp5==0)||(wp5==2))
    {
        cout<<"Te pole jest zajete !\n\n";
        pole=11;
    }
    pole5="X";
    wp5=2;
    break;
case 6:
  if ((wp6==0)||(wp6==2))
    {
        cout<<"Te pole jest zajete !\n\n";
        pole=11;
    }
    pole6="X";
    wp6=2;
    break;
case 7:
  if ((wp7==0)||(wp7==2))
    {
        cout<<"Te pole jest zajete !\n\n";
        pole=11;
    }
    pole7="X";
    wp7=2;
    break;
case 8:
  if ((wp8==0)||(wp8==2))
    {
        cout<<"Te pole jest zajete !\n\n";
        pole=11;
    }
    pole8="X";
    wp8=2;
    break;
case 9:
  if ((wp9==0)||(wp9==2))
    {
        cout<<"Te pole jest zajete !\n\n";
        pole=11;
    }
    pole9="X";
    wp9=2;
    break;

default:
    cout<<"Musisz wybrac odpowiednie pole !\n\n";
 }
  }while ((1>pole)||(pole>9));
  pole_do_gry();
}


int gra()
{
    pole_do_gry();
    do
    {
    kolko();
    wygrana_gra();
  if (wygrana==0)
  {
      krzyzyk();
      wygrana_gra();
  }
    }while(wygrana==0);
}

int main()
{
    int rozpoczecie;
    int rozpoczecie_gra;

    cout<<"Witaj w grze w kolko i krzyzyk napisanej przez Oskara Niedzwiedzkiego\nWcisniecie litery gdziekolwiek spowoduje 'crash' programu\nAby rozpoczac wcisnij 1\n";
    do
    {
    cin>>rozpoczecie;
    if (rozpoczecie==1)
    {
        cout<<"Milej zabawy !\n\nUruchamianie...\n\n";
        cout<<"Witaj w grze !\nAby rozpoczac gre kliknij 1\nJesli nie jestes zaznajomiony z zasadami kliknij 2\nAby zakonczyc dzialanie programu wcisnij 3\n\n\n\n";
        pole_do_gry();
        cout<<"\n\n";
        do{
        cin>>rozpoczecie_gra;
        switch(rozpoczecie_gra)
        {
        case 1:
            gra();
            reset();
            cout<<"Dziekuje za gre !\nAby zagrac jeszcze raz wcisnij 1\nJesli dalej nie rozumiesz zasad (jakims cudem) kliknij 2\nAby zakonczyc dzialanie programu wcisnij 3\n\n";
            break;
        case 2:
            zasady();
            cout<<"\n";
            cout<<"Aby rozpoczac gre kliknij 1\nAby ponownie przeczytac zasady kliknij 2\n\n";
            rozpoczecie_gra=1;
        }
        if((rozpoczecie_gra<1)||(rozpoczecie_gra>3))
        {
            cout<<"Musisz wprowadzic odpowiednia wartosc !\n";
        }
        if(rozpoczecie_gra==3)
        {
            break;
        }
        }while((1<=rozpoczecie_gra)||(rozpoczecie_gra<=2));
    }
    else
    {
      cout<<"Aby rozpoczac gre musisz koniecznie wprowadzic 1 !\n";
    }
    }while((rozpoczecie<1)||(rozpoczecie>1));
}
