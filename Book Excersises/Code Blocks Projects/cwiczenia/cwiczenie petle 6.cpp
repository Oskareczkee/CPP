#include <iostream>
using namespace std;

int main()
{
    int kolor;
    int czer=0;
    int nieb=0;
    int ziel=0;
    int powtorzenie;

    cout<<"Witaj w podrecznym systemie ankietowania. Zostanie ci przedstawiona ankieta. Wybierz sposrod 3 odpowiedzi. Wyniki ankiety beda pokazane na koncu.\n";
    do
    {
    cout<<"Jaki kolor z przedstawionych lubisz najbardziej ?\n1-czerwony\n2-niebieski\n3-zielony\n";
    cin>>kolor;
    while((kolor<0||kolor>3))
    {
        cout<<"Musisz wybrac poprawna odpowiedz\n";
        cin>>kolor;
    }
        if(kolor==1)
        {
            czer++;
        }
        if(kolor==2)
        {
            nieb++;
        }
        if(kolor==3)
        {
            ziel++;
        }
        cout<<"Czy chcesz powtorzyc ankiete ?\n1-tak\n0-nie\n";
        cin>>powtorzenie;
        while((0>powtorzenie||powtorzenie>2))
        {
            cout<<"Musisz wybrac poprawna opcje\n";
            cin>>powtorzenie;
            if(powtorzenie==0)
            {
                break;
            }
        }
    }while(powtorzenie==1);
    cout<<"Dziekuje za wziecie udzialu w ankiecie.\n\n\nWyniki:";
    cout<<"                              czerwony   niebieski   zielony\n";
    cout<<"                                        "<<czer<<"           "<<nieb<<"          "<<ziel<<"\n\n\n\n\n\n\n\n";
}
