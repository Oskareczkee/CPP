#include <iostream>
#include <string>

using namespace std;
int main ()
{
    int beer=99;
    while (0<beer)
    {
        cout<<beer<< "bottles of beer on the wall,"<<beer<< "bottles of beer.\n";
        beer--;
        cout<<"Take one down and pass it around,"<< beer<< "bottles of beer on the wall.\n";
        if (beer==1)
        {
            cout<<beer<< "bottle of beer on the wall,"<< beer <<"bottle of beer.\n""Take one down and pass it around, no more bottles of beer on the wall.\n";
            break;
        }

    }
    cout<<"No more bottles of beer on the wall, no more bottles of beer."<<endl<<"Go to the store and buy some more, 99 bottles of beer on the wall.";


}

