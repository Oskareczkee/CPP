
#include <iostream>
#include <math.h>
#include <conio.h>

using namespace std;


float Pole(float dx,float dy) //Prostokata
{
return dx*dy;
}
float Pole(float r) //Kola
{
return 3.14159*r*r;
}

float Obwod(float dx,float dy) //Prostokata
{
return 2*(dx+dy);
}
float Obwod(float r) //Kola
{
return 2*3.14159*r;
}
float Obwod(float a, float b, float c)//prostopadloscianu
{
    return 4*(a+b+c);
}
//Obwodu walca nie ma chyba :/


float Objetosc(float dx,float dy,float dz) //Prostopadloscianu
{
return Pole(dx,dy)*dz;
}
float Objetosc(float r,float h) //Walca
{
return Pole(r)*h;
}

float Pole3d(float dx,float dy,float dz) //Prostopadloscianu
{
return
   Pole(dx,dy)*2+
   Pole(dx,dz)*2+
   Pole(dz,dy)*2;
}
float Pole3d(float r,float h) //Walca
{
return
     Pole(r)*2
   +Pole(Obwod(r),h);
}

float przekatna(float a, float b)//prostokata
{
    return sqrt(pow(a,2)+pow(b,2));
}
float przekatna(float a, float b, float h)//prostopadloscianu
{
    float c=przekatna(a,b);//zmienna liczaca przekatna, zeby return byl czytelniejszy
    return sqrt(pow(c,2)+pow(h,2));
}
float przekatna_w(float h, float r)//przekotna walca, niestety nazwana inaczej, gdyz przyjmuje 2 argumenty , kolidowalaby z prostokatem, z dodatkowym argumentem kolidowalaby z prostopadloscianem :/
{
    return sqrt(pow(h,2)+pow(2*r,2));
}

///////////////////////

void menu()
{
    cout<<"Wybierz figure/bryle:\n\n1. Prostokat\n2.Kolo\n3.Prostopadloscian\n4.Walec\n\n0.Wyjdz\n\n";
}

void Wyswietl_pole(float a, float b)//prostokat
{
    cout<<"Przekatna tego prostokata wynosi: "<<przekatna(a,b)<<"\n"
    <<"Obwod tego prostakata wynosi: "<<Obwod(a,b)<<"\n"
    <<"Pole tego prostokata wynosi: "<<Pole(a,b)<<"\n\n";
}

void Wyswietl_pole(float r)//kolo
{
    cout<<"Obwod tego kola wynosi: "<<Obwod(r)<<"\n"
    <<"Pole tego kola wynosi: "<<Pole(r)<<"\n\n";
}

void Wyswietl_pole(float a, float b, float c)//prostopadloscian
{
    cout<<"Obwod tego prostopadloscianu wynosi: "<<Obwod(a,b,c)<<"\n"
    <<"Objetosc tego prostopadloscianu wynosi: "<<Objetosc(a,b,c)<<"\n"
    <<"Pole tego prostopadloscianu wynosi: "<<Pole3d(a,b,c)<<"\n"
    <<"Przekatna tego prostopadloscianu wynosi: "<<przekatna(a,b,c)<<"\n\n";
}

void Wyswietl_pole(float r, float h, bool walec)//walec
{
    cout<<"Obwod walca nie istnieje :/\n"
    <<"Objetosc tego walca wynosi: "<<Objetosc(r,h)<<"\n"
    <<"Pole tego walca wynosi: "<<Pole3d(r,h)<<"\n"
    <<"Przekatna tego walca wynosi: "<<przekatna_w(r,h)<<"\n\n";
}

void cls()
{
    cin.ignore();
    cin.get();
    system("cls");
}

///////////////////////////////

void Wyswietl_pole()
{
    float a,b,c,h,r;
    int znak;
    do
    {
        menu();
        znak=getch();
        switch(znak)
        {
        case 49:
            cout<<"Wpisz bok a: ";
            cin>>b;
            cout<<"Wpisz bok b: ";
            cin>>a;
            Wyswietl_pole(a,b);
            cls();
            break;
        case 50:
            cout<<"Wpisz promien kola: ";
            cin>>r;
            Wyswietl_pole(r);
            cls();
            break;
        case 51:
            cout<<"Wpisz bok a: ";
            cin>>a;
            cout<<"Wpisz bok b: ";
            cin>>b;
            cout<<"Wpisz bok c: ";
            cin>>c;
            Wyswietl_pole(a,b,c);
            cls();
            break;
        case 52:
            cout<<"Wpisz promien: ";
            cin>>r;
            cout<<"Wpisz wysokosc: ";
            cin>>h;
            Wyswietl_pole(r,h, true);
            cls();
            break;
        case 48:
            break;
        default:
            cout<<"Wybrales nieodpowiednia wartosc !\n";
            cin.get();
            system("cls");
            break;
        }
    }while(znak!=48);

}

int main()
{
  Wyswietl_pole();
}

