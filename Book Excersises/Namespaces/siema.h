#pragma once
#include <iostream>

using namespace std;


namespace Alicja
{
    namespace Rydel
    {

struct wezel
{
    int x;
    wezel* nastepny;
};

class vector
{

private:
    wezel* glowa;
    int ilosc_wezlow = 0;
    wezel* generuj_wezly(int wartosc);

public:
    vector();
    vector(int rozmiar);
    //tu powinien byc destruktor, ale tez go zapomnialem xD, potem dopisze, bo juz mi sie nie chce chuj00000101010
    vector& operator=(const vector& inny);//chuj wie jak z tego korzystac
    vector(const vector& inny);//chuuuj wie, co to robi


    int pobierz(int indeks);
    void ustaw(int indeks, int wart);
    void dodaj(int wart);
    void wstaw(int wart);

};


vector::vector(const vector& inny)
    :glowa(NULL)
{
    wezel* itr = inny.glowa;
    while (itr->nastepny != NULL)
    {
        wstaw(itr->x);
        itr = itr->nastepny;
    }
}

vector& vector::operator=(const vector& inny)
{
    if (this == &inny)
    {
        return *this;
    }
    delete this->glowa;
    this->glowa = NULL;
    wezel* itr = inny.glowa;
    while (itr->nastepny != NULL)
    {
        wstaw(itr->x);
        itr = itr->nastepny;
    }
    return *this;
}

wezel* vector::generuj_wezly(int wartosc)
{
    wezel* nowy_wezel = new wezel;
    nowy_wezel->x = wartosc;
    nowy_wezel->nastepny = NULL;
    ilosc_wezlow++;
    return nowy_wezel;
}

vector::vector()
{
    glowa = generuj_wezly(0);
    wezel* tymczas = glowa;
    for (int i = 0; i < 32; i++)
    {
        tymczas->nastepny = generuj_wezly(0);
        tymczas = tymczas->nastepny;
    }
}
vector::vector(int rozmiar)
{
    glowa = generuj_wezly(0);
    wezel* tymczas = glowa;
    for (int i = 0; i < rozmiar; i++)
    {
        tymczas->nastepny = generuj_wezly(0);
        tymczas = tymczas->nastepny;
    }
}

int vector::pobierz(int index)
{
    wezel* tymczas = glowa;
    if (index < 0 || index >= ilosc_wezlow)
    {
        cout << "Index is out of range !\n";
        return NULL;
    }
    for (int i = 0; i < index; i++)
    {
        tymczas = tymczas->nastepny;
    }
    return tymczas->x;
}

void vector::ustaw(int index, int wart)
{
    wezel* tymczas = glowa;
    if (index < 0 || index >= ilosc_wezlow)
    {
        cout << "Index is out of range !\n";
        return;
    }
    for (int i = 0; i < index; i++)
    {
        tymczas = tymczas->nastepny;
    }
    tymczas->x = wart;
}

void vector::dodaj(int wart)
{
    wezel* nowy_wezel = new wezel;
    nowy_wezel->x = wart;
    nowy_wezel->nastepny = NULL;


    wezel* tymczas = glowa;
    while (tymczas->nastepny != NULL)
    {
        tymczas = tymczas->nastepny;
    }
    ilosc_wezlow++;
    tymczas->nastepny = nowy_wezel;
}

void vector::wstaw(int wart)
{
    wezel* nowy_wezel = new wezel;
    nowy_wezel->x = wart;
    nowy_wezel->nastepny = glowa;
    glowa = nowy_wezel;
}

//byczq, operator "=" narazie nie dziala, chuj wie, pewnie kiedys to naprawie, ale nie teraz, bo jestem zmeczony, aha i ta metoda pod kopiowaniem to nawet nie wiem co robi xDDDD
/*
int main()
{
    //przyklad uzycia
    vector contact(5);
    contact.ustaw(2, 5);
    contact.dodaj(15);
    contact.wstaw(30);
    cout << contact.pobierz(0);
    cout << "duppa";
}
*/
    }
}
