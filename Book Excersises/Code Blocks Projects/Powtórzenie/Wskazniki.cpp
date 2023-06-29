#include <iostream>
#include <ctime>
#include <string>
#include <cstdlib>

using namespace std;

void imieinazwisko(string &imie, string &nazwisko)
{
    cout<<imie<<" "<<nazwisko<<"\n";
}

void imieinazwiskoo(string *wimie, string *wnazwisko)
{
    cout<<*wimie<<" "<<*wnazwisko<<"\n";
}

void zadanie1()
{
        string imiee;
    string nazwiskoo;
    string *wimie=NULL;
    string *wnazwisko=NULL;
   cout<<"Podaj imie: ";
   cin>>imiee;
   cout<<"\nPodaj nazwisko: ";
   cin>>nazwiskoo;
   string &imie=imiee;
   string &nazwisko=nazwiskoo;
   wimie=&imiee;
   wnazwisko=&nazwiskoo;
   imieinazwisko(imie, nazwisko);
   if(wimie==NULL)
   {

   cout<<"\nPodaj imie: ";
   cin>>imiee;
   cout<<"\nPodaj nazwisko: ";
   cin>>nazwiskoo;
   }
   else
    cout<<"\nImie i nazwisko zostaly juz podane !\n";
   wimie=&imiee;
   wnazwisko=&nazwiskoo;
   imieinazwiskoo(wimie, wnazwisko);
}

void zadanie2()
{
    int w1;
    int w2;
    int wynik;
    int &wskaznik=wynik;
    cout<<"Wpisz pierwsza liczbe: ";
    cin>>w1;
    cout<<"\nWpisz druga liczbe: ";
    cin>>w2;
    wynik=w1*w2;
    cout<<"Iloczyn liczb: "<<wskaznik<<"\nSuma liczb: ";
    wynik=w1+w2;
    cout<<wskaznik<<"\n";
}

int random()
{
    return rand()%(50-40+1)+40;
}

void zadanie3()
{
    int a=random();
    int b=random();
    int *wskaznik=NULL;
    cout<<"Pierwsza liczba to: "<<a<<"\nDruga liczba to: "<<b<<"\n\n";
    wskaznik=&a;
    cout<<"Adres 1 zmiennej to: "<<wskaznik<<"\n";
    wskaznik=&b;
    cout<<"Adres 2 zmiennej to: "<<wskaznik<<"\n";
    delete wskaznik;
}

int main()
{
    srand(time(NULL));
    int zadanie;
    while(1)
    {
       cout<<"Wpisz numer zadania: ";
       cin>>zadanie;
       if(zadanie==0)
       {
           break;
       }
       switch(zadanie)
       {
   case 1:
    zadanie1();
    break;
   case 2:
    zadanie2();
    break;
   case 3:
    zadanie3();
    break;
   default:
    cout<<"Wpisales zly numer zadania !\n";
    break;
       }
    }

}
