#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

int losowa_liczba()
{
  return rand()%(9000-3000)+3000;
}

int funkcja_1()
{
    int liczba;
    fstream plik;
    string wyraz;
    string litera;
    string literaz;
    plik.open("slowa.txt", ios::in);
    cout<<"\n\n";
    if(plik.good()==false)
    {
        cout<<"Plik, ktory chcesz wczytac nie istnieje !\n";
        return 0;
    }
    for(int i=1;i<15;i++)
    {
        plik>>wyraz;
        litera=wyraz[0];
        if(litera=="A"||litera=="a")
        {
            for(int j=0;j<=30;j++)
            {
                literaz=wyraz[j];
                if(literaz=="&")
                {
                    liczba=j-1;
                    break;
                }
            }
        for(int j=0;j<=liczba;j++)
        {
            cout<<wyraz[j];
        }
        cout<<"\n";
        }
    }
    cout<<"\n";
    plik.close();
}
int funkcja_2()
{
    int liczba;
  fstream plik;
    string wyraz;
    string litera;
    string literaz;
    char znak='&';
    plik.open("slowa.txt", ios::in);
    cout<<"\n\n";
    if(plik.good()==false)
    {
        cout<<"Plik, ktory chcesz wczytac nie istnieje !\n";
        return 0;
    }
    for(int i=1;i<15;i++)
    {
        plik>>wyraz;
        for(int j=0;j<30;j++)
        {
            literaz=wyraz[j];
            if (literaz=="&")
            {
            litera=wyraz[j-1];
            liczba=j-1;
            break;
            }
        }
        if(litera=="A"||litera=="a")
        {
        for(int j=0;j<=liczba;j++)
        {
            cout<<wyraz[j];
        }
        cout<<"\n";
        }
    }
    cout<<"\n";
    plik.close();
}

int funkcja_3()
{
  fstream plik;
    plik.open("slowa.txt", ios::out | ios::app);
    if(plik.good()==false)
    {
        cout<<"Plik, ktory chcesz wczytac nie istnieje !\n";
        return 0;
    }
    for(int i=1;i<=1000;i++)
    {
        if(i==1)
        {
            plik<<"\n"<<losowa_liczba()<<"\n";
        }
        else
        {
        plik<<losowa_liczba()<<"\n";
        }

    }
    cout<<"\n";
    plik.close();
}

void menu()
{
cout<<"    #############################################################################\n"
<<"      Zaczynajace - Wczytaj wyrazy zaczynajace sie na litere A\n"
<<"      Konczace - Wczytaj wyrazy konczace sie na litere a\n"
<<"      Generuj - wygeneruj 1000 losowych liczb z przedzialu 3000-9000 i zapisz je w pliku\n"
<<"      Wyjdz - Wyjdz z programu\n"
<<"    #############################################################################\n";
}

int main()
{
    srand(time(NULL));
  string wartosc;
  menu();
  while(1)
  {
      cout<<"Wpisz, co chcesz zrobic: ";
      cin>>wartosc;
    if (wartosc=="zaczynajace"||wartosc=="Zaczynajace")
    {
        funkcja_1();
    }
    else if(wartosc=="konczace"||wartosc=="Konczace")
    {
        funkcja_2();
    }
    else if(wartosc=="generuj"||wartosc=="Generuj")
    {
        funkcja_3();
    }
    else if(wartosc=="wyjdz"||wartosc=="Wyjdz")
    {
        break;
    }
    else
    {
        cout<<"Podana przez ciebie funkcja nie istnieje !\n\n";
    }
  }
  cout<<"\nDziekuje za korzystanie z programu, aby zakonczyc jego dzialanie wcisnij cokolwiek !\n\n";
  cin.ignore();
  cin.get();
}
