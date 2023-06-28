#include <iostream>
#include "vectorinho.h"

using namespace std;


//byczq, operator "=" narazie nie dziala, chuj wie, pewnie kiedys to naprawie, ale nie teraz, bo jestem zmeczony, aha i ta metoda pod kopiowaniem to nawet nie wiem co robi xDDDD

int main()
{
    //przyklad uzycia
    vector contact(5);
    vector siema(contact);
    siema = contact;
    contact.ustaw(2, 5);
    contact.dodaj(15);
    contact.wstaw(30);
    cout << contact.pobierz(0);
    cout << "duppa";
}
