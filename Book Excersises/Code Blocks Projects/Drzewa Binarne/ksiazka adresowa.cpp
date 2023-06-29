#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

struct wezel
{
    string nazwisko; // nazwisko jest kluczem
    string email;
    wezel *prawy;
    wezel *lewy;
    wezel *rodzic;
};


void wybierz_opcje()
{
    cout<<"Wybierz opcje: \n\n1.dodaj nowy adres\n2.usun istniejacy adres\n3.aktualizuj adres email\n4.szukaj uzytkownika\n0.zakoncz dzialanie programu\n";
}

void cls()
{

       cin.get();
       system("cls");
}

wezel *wstaw(wezel *drzewo, string nazwisko, string email);//wstawia wezel
wezel *szukaj(wezel *drzewo, string nazwisko);//szuka wezla o okreslonej wartosci
wezel * zniszcz_drzewo(wezel *drzewo);//usuwa cale drzewo
wezel* usun(wezel *drzewo, string nazwisko);//usuwa wezel
wezel *znajdz_max(wezel *drzewo);//funkcja pomocnicza do usuwania wezla, nie uzywac !
wezel *usun_max(wezel *drzewo, wezel* max_wezel);//funkcja pomocnicza do usuwania wezla, nie uzywac !


int main()
{
    /*
                    boze=drzewo;
                drzewo=jezus;
                delete drzewo;
                drzewo=NULL;
                drzewo=boze;
    */
     int opcja;
     string nazwisko;
     string email;
     wezel *jezus=NULL;
     wezel *boze=NULL;
     wezel *drzewo=wstaw(NULL, "lllllllll", ""); //pierwszy wezel, bedzie rozdzialal litery w alfabecie
     do
     {
         wybierz_opcje();
         cin>>opcja;
         switch(opcja)
         {
         case 1:
             {
                 cout<<"\nPodaj nazwisko: ";
                 cin.ignore();
                 getline(cin,nazwisko,'\n');
                 cout<<"Podaj email: ";
                 getline(cin,email,'\n');
                 drzewo=wstaw(drzewo, nazwisko, email);
                 cout<<"\nPomyslnie dodano profil !\n";
                 cls();
                 break;
             }
         case 2:
             {
                cout<<"\nPodaj nazwisko, aby usunac profil: ";
                cin.ignore();
                getline(cin,nazwisko,'\n');
                jezus=szukaj(drzewo, nazwisko);
                if(jezus==NULL)
                {
                   cout<<"\nPodane przez ciebie nazwisko, nie zostalo odnalezione\n";
                   cls();
                   break;
                }
                drzewo=usun(drzewo, nazwisko);
                cout<<"\nPomyslnie usunieto profil !";
                cls();
                break;
             }
         case 3:
            {
                cout<<"Podaj nazwisko, aby zaktualizowac email: ";
                cin.ignore();
                getline(cin, nazwisko, '\n');
                jezus=szukaj(drzewo, nazwisko);
                if(jezus==NULL)
                {
                   cout<<"\nPodane przez ciebie nazwisko, nie zostalo odnalezione\n";
                   cls();
                   break;
                }
                cout<<"\nPodaj nowy email: ";
                getline(cin, email,'\n');
                jezus->email=email;
                cout<<"\nPomyslnie zaktualizowano email !\n";
                cls();
                break;
            }
         case 4:
            {
                cout<<"Podaj nazwisko, aby znalezc uzytkownika: ";
                cin.ignore();
                getline(cin, nazwisko, '\n');
                jezus=szukaj(drzewo, nazwisko);
                if(jezus==NULL)
                {
                   cout<<"\nPodane przez ciebie nazwisko, nie zostalo odnalezione\n";
                   cls();
                   break;
                }
                cout<<"Nazwisko: "<<jezus->nazwisko<<"\nemail: "<<jezus->email<<"\n\n";
                cls();
                break;
            }
         case 0:
             {
                drzewo=zniszcz_drzewo(drzewo);
                break;
             }
         default:
             {
                cout<<"Podales nieodpowiednia wartosc !\n";
                break;
             }
         }
     }while(opcja!=0);
}

//////////////////////////////////////////////////////////////////////////
wezel *znajdz_max(wezel* drzewo)
{
    if(drzewo==NULL)
    {
        return NULL;
    }
    if(drzewo->prawy==NULL)
    {
        return drzewo;
    }
    return znajdz_max(drzewo->prawy);
}

wezel *usun_max(wezel *drzewo, wezel* max_wezel)
{
    if(drzewo=NULL)
    {
        return NULL;
    }
    if(drzewo==max_wezel)
    {
        return max_wezel->lewy;
    }
    drzewo->prawy=usun_max(drzewo->prawy, max_wezel);
    return drzewo;
}

////////////////////////////////////////////////////////////////////////
wezel *wstaw(wezel *drzewo, string nazwisko, string email)
{
    static wezel *rodzic=NULL;
    if(drzewo==NULL)
    {
        wezel *nowe_drzewo=new wezel;
        nowe_drzewo->lewy=NULL;
        nowe_drzewo->prawy=NULL;
        nowe_drzewo->rodzic=rodzic;
        nowe_drzewo->nazwisko=nazwisko;
        nowe_drzewo->email=email;
        return nowe_drzewo;
    }
    if(nazwisko<drzewo->nazwisko)
    {
        rodzic=drzewo;
        drzewo->lewy=wstaw(drzewo->lewy, nazwisko, email);
    }
    else
    {
        rodzic=drzewo;
        drzewo->prawy=wstaw(drzewo->prawy, nazwisko, email);
    }
    return drzewo;
}

wezel *szukaj(wezel *drzewo, string nazwisko)
{
    if(drzewo==NULL)
    {
        return NULL;
    }
    else if(nazwisko==drzewo->nazwisko)
    {
        return drzewo;
    }
    else if(nazwisko<drzewo->nazwisko)
        return szukaj(drzewo->lewy, nazwisko);
    else if(nazwisko>drzewo->nazwisko)
        return szukaj(drzewo->prawy, nazwisko);

}

wezel * zniszcz_drzewo(wezel *drzewo)
{
    if(drzewo!=NULL)
    {
        zniszcz_drzewo(drzewo->lewy);
        zniszcz_drzewo(drzewo->prawy);
        drzewo=NULL;
        delete drzewo;
    }
}

wezel* usun(wezel *drzewo, string nazwisko)
{
    if(drzewo==NULL)
    {
        return NULL;
    }
    if(drzewo->nazwisko==nazwisko)
    {
        if(drzewo->lewy==NULL)
        {
            wezel *prawe_poddrzewo=drzewo->prawy;
            delete drzewo;
            return prawe_poddrzewo;
        }
        if(drzewo->prawy==NULL)
        {
            wezel *lewe_poddrzewo=drzewo->lewy;
            delete drzewo;
            return lewe_poddrzewo;
        }
        wezel *max_wezel=znajdz_max(drzewo->lewy);
        max_wezel->lewy=usun_max(drzewo->lewy, max_wezel);
        max_wezel->prawy=drzewo->prawy;
        delete drzewo;
        return max_wezel;
    }
    else if(nazwisko<drzewo->nazwisko)
    {
        drzewo->lewy=usun(drzewo->lewy, nazwisko);
    }
    else
    {
        drzewo->prawy=usun(drzewo->prawy, nazwisko);
    }
    return drzewo;
}
