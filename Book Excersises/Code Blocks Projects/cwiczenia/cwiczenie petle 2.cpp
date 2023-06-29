#include <iostream>

using namespace std;
int main()
{
    int opcja;

    cout<<"Jaka opcje chcesz wybrac (1-4) ? ";
    cin>>opcja;
    bool opcjax= (opcja==1)||(opcja==2)||(opcja==3)||(opcja==4);
    if (opcjax)
    {
        cout<<"Brawo wybrales prawidlowa opcje";
    }
    else
    {
        while (opcjax==0)
        {
                cout<<"Jaka opcje chcesz wybrac (1-4) ? ";
                cin>>opcja;
                bool opcjax= (opcja==1)||(opcja==2)||(opcja==3)||(opcja==4);
                if (opcjax)
                   {
                        cout<<"Brawo wybrales prawidlowa opcje";
                        break;
                   }

        }

    }
}
