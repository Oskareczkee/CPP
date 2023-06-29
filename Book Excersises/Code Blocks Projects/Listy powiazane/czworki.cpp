#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>

using namespace std;


int random()
{
    return rand()%(50-0+1)+0;
}

struct Lista
{
    int x;
    Lista *nastepny;
};


Lista *utworzliste(Lista *elementylisty, Lista *poprzednielement)
{
    Lista* nowyelement= new Lista;
    nowyelement->x=random();
    nowyelement->nastepny=elementylisty;
    return nowyelement;
}

Lista *usunelementlisty(Lista *&elementylisty, int &liczba, int&ilosc)
{
    Lista *biezacy=elementylisty;
    Lista *nastepny=elementylisty;
    Lista *poprzedni=elementylisty;
    if(liczba<1)
    {
        cout<<"Nie mozna usuwac elementow, przed pierwszym elementem !\n";
        return 0;
    }
    else if(liczba==1)
    {
        elementylisty=biezacy->nastepny;
        delete biezacy;
        return elementylisty;
    }
    else if(liczba>1&&liczba<ilosc)
    {
        for (int x=0;x<liczba;x++)
    {
        if(x==liczba-1)
        {
          poprzedni->nastepny=nastepny;
          delete biezacy;
          return elementylisty;
        }
        poprzedni=biezacy;
        biezacy=biezacy->nastepny;
        nastepny=biezacy->nastepny;
    }
    }
    else if(liczba==ilosc)
    {
                for (int x=0;x<liczba;x++)
    {
        if(x==liczba-1)
        {
          poprzedni->nastepny=NULL;
          delete biezacy;
          return elementylisty;
        }
        poprzedni=biezacy;
        biezacy=biezacy->nastepny;
        nastepny=biezacy->nastepny;
    }
    }
    else if(liczba>ilosc)
    {
        cout<<"Nie mozna usunac elementu spoza listy !!\n\n";
        return 0;
    }
}

Lista *dodajelementlisty(Lista *&elementylisty, int &liczba, int &ilosc)
{
    Lista *nowyelement = new Lista;
    Lista *biezacy=elementylisty;
    Lista *poprzedni=elementylisty;

    if(liczba<1)
    {
        cout<<"Nie mozna dodawac elementow, przed pierwszym elementem !\n";
        return 0;
    }
    else if(liczba==1)
    {
        nowyelement->x=random();
        nowyelement->nastepny=elementylisty;
        elementylisty=nowyelement;
        ilosc++;
        return elementylisty;
    }
    else if(liczba==ilosc)
    {
        for(int x=1; x<=liczba;x++)
    {
        if(biezacy->nastepny==NULL)
        {
            nowyelement->x=random();
            nowyelement->nastepny=NULL;
            biezacy->nastepny=nowyelement;
            ilosc++;
            return elementylisty;
        }
        poprzedni=biezacy;
        biezacy=biezacy->nastepny;
    }
    }
    else if(liczba>1&&liczba<ilosc)
    {
    for(int x=0; x<liczba;x++)
    {
        if(x==liczba-1)
        {
            nowyelement->x=random();
            nowyelement->nastepny=biezacy;
            poprzedni->nastepny=nowyelement;
            ilosc++;
            return elementylisty;
        }
        poprzedni=biezacy;
        biezacy=biezacy->nastepny;
    }
    }
}

void znajdzelementlisty(Lista *&elementylisty, int &wartosc, int &ilosc)
{
    Lista *biezacy=elementylisty;
  for(int x=1;x<=ilosc;x++)
  {
      if(biezacy->x==wartosc)
      {
          cout<<"Szukana przez ciebie wartosc jest w "<<x<<" elemencie listy i ma adres : "<<biezacy<<"\n\n";
          break;
      }
      else if(biezacy->nastepny==NULL)
      {
          cout<<"W liscie nie znaleziono szukanej przez ciebie wartosci !\n\n";
          break;
      }
      biezacy=biezacy->nastepny;
  }
}

int main()
{
    srand(time(NULL));
    int ilosc;
    int liczba;
    int opcja;
    int wartosc;
    Lista *elementylisty=NULL;
    Lista *poprzednielement=NULL;



    cout<<"Wpisz ilosc elementow listy, ktorych chcesz utworzyc: ";
    cin>>ilosc;
    for(int x=0;x<ilosc;x++)
    {
        elementylisty=utworzliste(elementylisty, poprzednielement);
    }
    cout<<"Wygenerowana Lista: \n";
    Lista *biezacy=elementylisty;
    for(int x=1;biezacy!=NULL;x++)
    {
        cout<<x<<"."<<biezacy->x<<"\n";
        biezacy=biezacy->nastepny;
    }
    while(1)
    {
    cout<<"Co chcesz zrobic\n1. Usun element z listy\n2. Dodaj element do listy\n3. Szukaj elementu w liscie\n4. Wyjdz\n";
    cin>>opcja;
    if(opcja==4)
    {
        break;
    }
    switch(opcja)
    {
    case 1:
        {
            cout<<"Ktory element listy chcesz usunac: ";
        cin>>liczba;
    cout<<"\nLista z usunietym elementem: \n\n";
    elementylisty=usunelementlisty(elementylisty, liczba, ilosc);
    biezacy=elementylisty;
    for(int x=1;biezacy!=NULL;x++)
    {
        cout<<x<<"."<<biezacy->x<<"\tAdres pamieci tego elementu to: "<<biezacy<<"\n";
        biezacy=biezacy->nastepny;
    }
        break;
        }
    case 2:
        cout<<"W ktorym miejscu chcesz dodac element: ";
        cin>>liczba;
        cout<<"\nLista z dodanym elementem:\n\n";
        elementylisty=dodajelementlisty(elementylisty, liczba, ilosc);
        biezacy=elementylisty;
            for(int x=1;biezacy!=NULL;x++)
    {
        cout<<x<<"."<<biezacy->x<<"\tAdres pamieci tego elementu to: "<<biezacy<<"\n";
        biezacy=biezacy->nastepny;
    }
    break;
    case 3:
        cout<<"Wpisz wartosc jaka chcesz znalezc w liscie: ";
        cin>>wartosc;
        znajdzelementlisty(elementylisty, wartosc, ilosc);
        break;
    case 0:
        break;
    default:
        cout<<"Wpisales nieodpowiednia wartosc !\n";
        break;

    }
    }
}
