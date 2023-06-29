#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

int znajdz_litere(string tekst, char litera)
{
    int ile;
    for(int i=0;i<tekst.size();i++)
    {
        if(tekst[i]==litera)
            ile++;
    }
    return ile;
}


void brute_force(string napis)
{
      cout<<"Tekst oryginalny: \n"<<napis<<"\n\n";

      for(int x=1;x<=25;x++)
      {
          cout<<"\n\nKlucz: "<<x<<"\n";
      for (int i=0;i<napis.length();i++)
      {
         cout<<static_cast<char>((napis[i]-97+26-x)%26+97);
      }
      }
}
int frequency_analysis(string napis)
{
    int wynik;
   int maks=0;
   char litera;
   for(int x=97;x<=122;x++)
   {
       wynik=znajdz_litere(napis, x);
       if(wynik>maks)
       {
        maks=wynik;
        litera=x;
       }
   }
   return (litera-'a');
}

string deszyfrowanie(string kod, int klucz)
{
      string napis="";


      for (int i=0;i<kod.length();i++)
      {
          napis+=(kod[i]-97+26-klucz)%26+97;
      }

      return napis;
}

int main()
{
    string napis;
    int klucz;

    cout << "Podaj tekst do zaszyfrowania: ";
    getline(cin,napis);
    cout<<"Metoda \"brute force\": ";
    brute_force(napis);
    cout<<"\n\nMetoda statystyczna:\n";
    klucz=frequency_analysis(napis);
    cout<<"\n\nKlucz to najprawdopodobniej: "<<klucz<<"\nDeszyfrowanie z uzyciem klucza...";
    cout<<"\n\n"<<deszyfrowanie(napis, klucz)<<"\n";
    cout<<"\nJesli tekst nie jest czytelny, to znaczy ze jakiejs literki w nim jest wiecej niz \"a\". Znajdz klucz przy uzyciu metody brute force zatem :/\n\n";

    system("PAUSE");
}
