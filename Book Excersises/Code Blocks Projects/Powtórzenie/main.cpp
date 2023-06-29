#include <iostream>
#include <ctime>
#include <string>

using namespace std;

int rand(int min, int max)
{
    return rand()%(max-min+1)+min;
}
void jednorekibandyta()
{
    int wl=0;//wartosc losowania
   for(int x=0;x<3;x++)
   {
       int los=rand(1,3);
       switch(los)
       {
       case 1:
        cout<<"[#]";
        wl++;
        break;
       case 2:
        cout<<"[$]";
        wl+=2;
        break;
       case 3:
        cout<<"[%]";
        wl+=3;
        break;
       }
   }
  if (wl==3||wl==6||wl==9||wl==12)
  cout<<"\nBrawo wygrales !\n\n";
  else cout<<"\n";
}
void a()
{
    string heh;
    string zdanie;
    cin>>zdanie;
    getline(cin, heh, 'i');
    cout<<zdanie<<"\n"<<heh<<"\n";
    cin.get();
}
void b()
{
   enum xd{a,b,c,d,e};
   cout<<"Wpisz liczbe od 0-4\n";
   xd wybrana_literka=a;
   switch(wybrana_literka)
   {
   case a:
    cout<<"A\n";
    break;
   case b:
    cout<<"B\n";
    break;
   case c:
    cout<<"C\n";
    break;
   case d:
    cout<<"D\n";
    break;
    case e: cout<<"E\n";break;
    default: cout<<"Cos poszlo zle... moze wpisz inna wartosc !\n\n";break;
   }
}
int c()
{
    int liczba;
    cout<<"Siema, dej no liczbe jakas: ";
    cin>>liczba;
  int los=rand()%(5-1+1)+1;
  cout<<liczba<<"\n\n\n";
  return los;

}
void d()
{
    int liczba;
   cout<<"Witaj w kolejnym prototypie jednorekiego bandyty !\n\nWcisnij 1 zeby zagrac\nWcisnij 0 zeby wyjsc z programu";
    while(1)
   {
   cin>>liczba;
       if(liczba==0)
       {
           cout<<"Dziekuje za gre w jednorekiego bandyte !\n\n\n";
           cin.ignore();
           cin.get();
           break;
       }
       switch(liczba)
       {
       case 1:
        jednorekibandyta();
        break;
       default:
        cout<<"Wprowadzona przez ciebie wartosc jest zla !\n\n";
        break;
       }
   }

int main()
{
    srand(time(NULL));
    int i;
    cout<<"0 Wylacza program\n\n\n";
    do
  {
  cout<<"Wybierz program: ";
  cin>>i;
  if(i==0)
    break;
      switch(i)
      {
        case 1:
            {
                cout<<"Inicjalizacja...\n\n";
             a();
             cout<<"...Koniec programu\n\n";
             break;
            }
                 case 2:
            {
                cout<<"Inicjalizacja...\n\n";
             b();
             cout<<"...Koniec programu\n\n";
             break;
            }
                 case 3:
            {
                cout<<"Inicjalizacja...\n\n";
             cout<<c();
             cout<<"...Koniec programu\n\n";
             break;
            }
                 case 4:
                    {
                        d();
                        break;
                    }
        default:
            {
                cout<<"Podana przez ciebie wartosc jest nieprawidlowa !";
                break;
            }
      }

  }while(1);
}
