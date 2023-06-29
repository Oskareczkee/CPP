#include <iostream>
#include <vector>
#include <string>
using namespace std;

///////////
void z_1();
void z_2();
void z_3();
///////////

string wykryj_znak(string tekst)//poczatek oznacza jakies miejsce w tekscie, od ktorego trzeba zaczac//bede zwracal tablice znakow, czyli stringa
{
    string wykryte_znaki;
    for(int x=0;x<tekst.length();x++)
    {
        if(tekst[x]==32||(tekst[x]>=48&&tekst[x]<=57)||(tekst[x]>=65&&tekst[x]<=90)||(tekst[x]>=97&&tekst[x]<=122))
        {
            continue;
        }
        else
        {
            if(wykryte_znaki.find(tekst[x])==string::npos)
            {
                wykryte_znaki+=tekst[x];
            }
        }
    }
    return wykryte_znaki;
}

vector<string> znaczniki={"<html>","</html>","<head>","</head>","<body>","</body>","<b>","</b>","<i>","</i>","<a>","</a>"};
enum index_enum{html,endhtml,head,endhead,body,endbody,b,endb,i,endi,a,enda};//end==</"znacznik">

int zwroc_index_znacznika(string znacznik)
{
    bool znaleziono=false;
    int index_znacznika=0;
    for(vector<string>::iterator itr=znaczniki.begin();itr!=znaczniki.end();++itr)
    {
        if(*itr==znacznik)
        {
           znaleziono=true;
           return index_znacznika;
        }
        index_znacznika++;
    }

    if(znaleziono==false)
    {
      cout<<"Znacznik nie istnieje, lub nie jest zawarty w bazie znacznikow\n";
      return -1;
    }
}

int oblicz_dlugosc_head(int miejsce_w_tekscie, const string &kod_sformatowany)
{
    string znacznik;
   for(int x=0;x<kod_sformatowany.length();x++)
   {
     if(kod_sformatowany[miejsce_w_tekscie+x]=='<')
       {
           if(kod_sformatowany[miejsce_w_tekscie+x]!='>')
           {
             znacznik+=kod_sformatowany[miejsce_w_tekscie+x];
           }
           else
           {
               znacznik+='>';
               cout<<"\n"<<znacznik<<"\n";
             if(zwroc_index_znacznika(znacznik)==2)
             {
                 return x+1;
             }
             else
             {
           znacznik.erase();
           continue;
             }
           }
       }
   }
   return 0;

}

bool formatuj_tekst(string znacznik, string &kod_sformatowany, int miejsce_w_tekscie)
{
   int index_znacznika=zwroc_index_znacznika(znacznik);
   if(index_znacznika!=-1)
   {
      switch(index_znacznika)
      {
      case html:
        {
            kod_sformatowany.erase(miejsce_w_tekscie, znaczniki[index_znacznika].length());
            return 1;
            break;
        }
      case endhtml:
        {
            kod_sformatowany.erase(miejsce_w_tekscie, znaczniki[index_znacznika].length());
            return 1;
            break;
        }
        case head:
        {
            int dlugosc_head=oblicz_dlugosc_head(miejsce_w_tekscie, kod_sformatowany);
            kod_sformatowany.erase(miejsce_w_tekscie, oblicz_dlugosc_head(miejsce_w_tekscie, kod_sformatowany));
            return 1;
        }
        case body:
        {
            kod_sformatowany.erase(miejsce_w_tekscie, znaczniki[index_znacznika].length());
            return 1;
            break;
        }
        case endbody:
        {
            kod_sformatowany.erase(miejsce_w_tekscie, znaczniki[index_znacznika].length());
            return 1;
            break;
        }
        //case b:
            //kod_sformatowany
      }
   }
   else
   {
       return 0;
   }
}

int main()
{
  z_3();
}


void z_1()
{
    string igla="igla";
    string stog_siana="stog siana";
    int igla_w_stogu=0;
    for(int x=stog_siana.find(igla, 0); x!=string::npos;x=stog_siana.find(igla,x))
    {
        igla_w_stogu++;
        x++;
    }
    cout<<"Igla w stogu siana wystepuje: "<<igla_w_stogu<<" razy !\n";
}


void z_2()
{

    char znak;
    string znaki;
    string dane;
    cout<<"Wpisz dane: ";
    getline(cin, dane,'\n');
    znaki=wykryj_znak(dane);
    if(!znaki.empty())
    {
        cout<<"Uzyte przez ciebie znaki: \n";
        for(int x=0;x<znaki.length();x++)
        {
            cout<<znaki[x]<<" ";
        }
        do
        {
        cout<<"\n\nWpisz znak, ktory jest separatorem: ";
        cin>>znak;
        if(znaki.find(znak)!=string::npos)
        {
           for(int x=0;x<dane.length();x++)
           {
               if(dane[x]==znak)
               {
                   cout<<"\n";
                   x++;
               }
               else
               {
                   cout<<dane[x];
               }
           }
           break;
        }
        else
        {
            cout<<"Podany przez ciebie znak nie zostal odnaleziony !\n";
        }
        }while(1);

    }
}

void z_3()
{
   //const vector<string> znaczniki={"<html>","</html>","<body>","</body>","<b>","</b>","<i>","</i>","<a>","</a>"};
   //const vector<string> znaczniki={"<html>","<body>","<b>","<i>","<a>"};
   string kod;
   string kod_sformatowany;
   string znacznik;
   int miejsce_w_tekscie=0;
   cout<<"Podaj kod HTML: ";
   getline(cin, kod, '\n');
   kod_sformatowany=kod;
   for(int x=0;x<kod_sformatowany.length();x++)
   {
       if(kod[x]=='<')
       {
           miejsce_w_tekscie=x;
           cout<<miejsce_w_tekscie;
           for(;x<kod_sformatowany.length();x++)
           {

             if(kod[x]!='>')
             {
                znacznik+=kod_sformatowany[x];
             }
             else
             {
               znacznik+='>';
               cout<<"\n"<<znacznik<<"\n";
               if(formatuj_tekst(znacznik, kod_sformatowany, miejsce_w_tekscie)!=false)
               {
                   int dlugosc_znacznika=znacznik.length();
                   cout<<dlugosc_znacznika;
                   x-=dlugosc_znacznika-1;
                   znacznik="";
                   break;
               }
              else
              {
                 znacznik.erase();
                 break;
              }
             }
           }
       }
   }
   cout<<kod_sformatowany<<znacznik.length()<<znacznik[0];
   //<<znaczniki[1]<<znaczniki[1].length();
}

//jak sie nie uda dokonczyc kodu, to napisac kod uzywajacy metody find w stringu, ktory szuka znacznikow, az do momentu kiedy sie wyczerpia
