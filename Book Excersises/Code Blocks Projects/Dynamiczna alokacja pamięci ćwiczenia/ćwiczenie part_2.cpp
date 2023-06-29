#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>

using namespace std;

int rand_1(int szerokosc)//TYLKO DO GENEROWANIA LOSOWEJ SZEROKOSCI
{
    return rand()%szerokosc;
}

int rand_2(int szerokosc, int wysokosc)//TYLKO DO GENEROWANIA LOSOWEJ WYSOKOSCI, GDY MAMY WYLOSOWANA SZEROKOSC
{
    int randi;
    if(rand_1==0||szerokosc)
       return rand()%wysokosc;
    if(rand_1!=0||szerokosc)
    {
        while(1)
        {
        randi = rand()%wysokosc;
        if(rand!=0||wysokosc)
        continue;
        else
            return randi;
        }
    }
}

void labirynt()
{
  int szerokosc;
  int wysokosc;
  int **tablica_labirynt=NULL;
  srand(time(NULL));

  cout<<"Wpisz szerokosc labiryntu: ";
  cin>>szerokosc;
  szerokosc--;
  tablica_labirynt=new int*[szerokosc];
  cout<<"Wpisz wysokosc labiryntu: ";
  cin>>wysokosc;
  wysokosc--;
  for(int i=0;i<=wysokosc;i++)
  {
      tablica_labirynt[i]=new int[szerokosc];
  }
  //Nadawanie polom wartosci "Nieodwiedzonych"
  for(int i=0;i<=szerokosc;i++)
  {
      for(int j=0;j<=wysokosc;j++)
      {
          tablica_labirynt[i][j]=0;
      }
  }
  /*Oznaczenia w tablicy:
  0-pole nieodwiedzone;
  1-pole odwiedzone;
  */
  cout<<"Generowanie labiryntu...\n\n";


}


int main()
{
    int opcja;
    cout<<"1. Generator labiryntu\n\n";
    do
    {
        cout<<"Wybierz opcje: ";
        cin>>opcja;
        switch(opcja)
        {
        case 1:
            labirynt();
            break;
        default:
            cout<<"Musisz wpisac odpowiednia wartosc !\n";
            break;
        }
    }while(1);
}
