#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Naglowek.h"

using namespace std;

int random()
{
    return rand() % (10000 - (-10000) + 1) + (-10000);
}


int main()
{
    //przyklad uzycia funkcji
    int chuuuj;
    wezel* drzewo = wstaw(NULL, 0); //poczatek drzewa, bede przechowywal liczby od -10000 do 10000
    for (int x = 0; x < 255; x++)
    {
        wstaw(drzewo, random());

        //aby recznie wstawiac wartosci zakomentuj linijke wyzej i usun komentarz z 2 linijek nizej

        //cin>>chuuuj;
        //wstaw(drzewo, chuuuj);
    }
    wyswietl_zawartosc(drzewo);
    cout << "\nLiczba wezlow w tym drzewie to: " << liczba_wezlow(drzewo);
    cout << "\n" << rownowaga_drzewa(drzewo) << "\n" << czy_drzewo_jest_posortowane(drzewo);
    drzewo = zniszcz_drzewo(drzewo);
    wyswietl_zawartosc(drzewo);
}

