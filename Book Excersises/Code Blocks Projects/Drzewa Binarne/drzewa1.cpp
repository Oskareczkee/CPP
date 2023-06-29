#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

struct wezel
{
    int klucz;
    wezel *prawy;
    wezel *lewy;
    wezel *rodzic;
};

int random()
{
    return rand()%(10000-(-10000)+1)+(-10000);
}

wezel *wstaw(wezel *drzewo, int klucz);//wstawia wezel
wezel *szukaj(wezel *drzewo, int klucz);//szuka wezla o okreslonej wartosci
wezel * zniszcz_drzewo(wezel *drzewo);//usuwa cale drzewo
wezel* usun(wezel *drzewo, int klucz);//usuwa wezel
wezel *znajdz_max(wezel *drzewo);//funkcja pomocnicza do usuwania wezla, nie uzywac !
wezel *usun_max(wezel *drzewo, wezel* max_wezel);//funkcja pomocnicza do usuwania wezla, nie uzywac !
void wyswietl_zawartosc(wezel *drzewo);//wyswietla zawartosc drzewa
int liczba_wezlow(wezel *drzewo);//pokazuje ilosc wezlow w drzewie
bool rownowaga_drzewa(wezel *tree);//sprawdza, czy drzewo jest zrownowazone
bool czy_drzewo_jest_posortowane(wezel *drzewo);//sprawdza, czy wartosci w drzewie sa odpowiednio posortowane(zgodonie z zasada budowania drzewa binarnego)


int main()
{
    //przyklad uzycia funkcji
    int chuuuj;
    wezel *drzewo=wstaw(NULL, 0); //poczatek drzewa, bede przechowywal liczby od -10000 do 10000
    for(int x=0;x<255;x++)
    {
        wstaw(drzewo, random());

        //aby recznie wstawiac wartosci zakomentuj linijke wyzej i usun komentarz z 2 linijek nizej

        //cin>>chuuuj;
        //wstaw(drzewo, chuuuj);
    }
    wyswietl_zawartosc(drzewo);
    cout<<"\nLiczba wezlow w tym drzewie to: "<<liczba_wezlow(drzewo);
    cout<<"\n"<<rownowaga_drzewa(drzewo)<<"\n"<<czy_drzewo_jest_posortowane(drzewo);
    drzewo=zniszcz_drzewo(drzewo);
    wyswietl_zawartosc(drzewo);
}


bool czy_drzewo_jest_posortowane(wezel *drzewo)
{
    static int posortowane=0;
    if(drzewo->prawy==NULL&&drzewo->lewy==NULL)
    {
      //nic nie rob, totalnie nie wiem co tu napisac xDDDDD, jest se instrukcja warunkowa, bez niej na koncu drzewa, gdzie sie spodziewamy, ze wezel nie ma rodzenstwa, funkcja zwroci nam falsz :(
    }
    else if(drzewo->prawy!=NULL||drzewo->lewy!=NULL)
    {
        if(drzewo->prawy==NULL)
        {
           //nic nie rob
        }
        else if(drzewo->prawy->klucz>drzewo->klucz)
        {
        czy_drzewo_jest_posortowane(drzewo->prawy);
        }
        else
            posortowane++;
            if(drzewo->lewy==NULL)
            {
                //nic nie rob
            }
        else if(drzewo->lewy->klucz<drzewo->klucz)
        {
        czy_drzewo_jest_posortowane(drzewo->lewy);
        }
        else
            posortowane++;
    }
    if(posortowane!=0)
        return false;
    else
        return true;
}

bool rownowaga_drzewa(wezel *tree)
{
    static int rownowaga=0;
    if(tree->prawy==NULL&&tree->lewy==NULL)
    {
      //nic nie rob, totalnie nie wiem co tu napisac xDDDDD, jest se instrukcja warunkowa, bez niej na koncu drzewa, gdzie sie spodziewamy, ze wezel nie ma rodzenstwa, funkcja zwroci nam falsz :(
    }
    else if(tree->prawy!=NULL&&tree->lewy!=NULL)
    {
        rownowaga_drzewa(tree->lewy);
        rownowaga_drzewa(tree->prawy);
    }
    else
    {
        rownowaga++;
    }
    if(rownowaga!=0)
        return false;
    else
        return true;
}

int liczba_wezlow(wezel *drzewo)
{
    static int wezly;
    if(drzewo!=NULL)
    {
        liczba_wezlow(drzewo->lewy);
        liczba_wezlow(drzewo->prawy);
        wezly++;
    }
    return wezly;
}

void wyswietl_zawartosc(wezel *drzewo)
{
    if(drzewo!=NULL)
    {
        wyswietl_zawartosc(drzewo->lewy);
        wyswietl_zawartosc(drzewo->prawy);
        cout<<drzewo->klucz<<"\n";
    }


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
wezel *wstaw(wezel *drzewo, int klucz)
{
    static wezel *rodzic=NULL;
    if(drzewo==NULL)
    {
        wezel *nowe_drzewo=new wezel;
        nowe_drzewo->lewy=NULL;
        nowe_drzewo->prawy=NULL;
        nowe_drzewo->rodzic=rodzic;
        nowe_drzewo->klucz=klucz;
        return nowe_drzewo;
    }
    if(klucz<drzewo->klucz)
    {
        rodzic=drzewo;
        drzewo->lewy=wstaw(drzewo->lewy, klucz);
    }
    else
    {
        rodzic=drzewo;
        drzewo->prawy=wstaw(drzewo->prawy, klucz);
    }
    return drzewo;
}

wezel *szukaj(wezel *drzewo, int klucz)
{
    if(drzewo==NULL)
    {
        return NULL;
    }
    else if(klucz==drzewo->klucz)
    {
        return drzewo;
    }
    else if(klucz<drzewo->klucz)
        return szukaj(drzewo->lewy, klucz);
    else if(klucz>drzewo->klucz)
        return szukaj(drzewo->prawy, klucz);

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

wezel* usun(wezel *drzewo, int klucz)
{
    if(drzewo==NULL)
    {
        return NULL;
    }
    if(drzewo->klucz==klucz)
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
    else if(klucz<drzewo->klucz)
    {
        drzewo->lewy=usun(drzewo->lewy, klucz);
    }
    else
    {
        drzewo->prawy=usun(drzewo->prawy, klucz);
    }
    return drzewo;
}
