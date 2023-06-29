#include <iostream>

using namespace std;

struct Wezel
{
    int wart;
    Wezel *w_nastepny;
};

int main()
{
    int wart;
    Wezel* w_glowa;
    Wezel *w_tymczas=new Wezel;
    while(1)
    {
        cout<<"Podaj wartosc; 0, aby powtorzyc: \n";
        cin>>wart;
        if(wart == 0)
        {
            break;
        }
        //w_tymczas=w_glowa;
        w_tymczas->wart=wart;
        w_tymczas->w_nastepny=NULL;
        w_glowa=w_tymczas;
    }
    Wezel *w_itr=w_glowa;
    while(w_itr!=NULL)
    {
        cout<<w_itr->wart<<"\n";
        w_itr=w_itr->w_nastepny;
    }
        delete w_itr;
}
