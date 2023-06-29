#include <iostream>
using namespace std;

int main()
{
    int rozpoczecie;
    int pierwszaliczba=0;
    int hee=0;
    do
    {
        if(hee==0)
        {
    cout<<"To jest program wyswietlajacy kwadraty pierwszych 20 liczb.\nAby zaczac wpisz 1\n";
    cin>>rozpoczecie;
    hee++;
        }
        else
        {
           cout<<"Aby rozpoczac dzialanie programu musisz wpisac 1 !\n";
           cin>>rozpoczecie;
        }
    }while ((rozpoczecie>1)||(0>rozpoczecie));
    for(1;(pierwszaliczba<0)||(21>pierwszaliczba);pierwszaliczba++)
    {
        cout<<"Kwadrat liczby "<<pierwszaliczba<<" wynosi: "<<pierwszaliczba*pierwszaliczba<<"\n";
    }



}
