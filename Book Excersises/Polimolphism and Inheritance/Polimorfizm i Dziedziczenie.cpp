#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

class Porownywalne
{
public:
	Porownywalne(): nazwa("huj"), wynik(rand()%65000+1){}
	virtual bool porownaj(Porownywalne&inny) = 0;
	string nazwa;
    int wynik;
};
class TabelaWynikow : public Porownywalne
{
public:
	virtual bool porownaj(Porownywalne &inny);
};

bool TabelaWynikow::porownaj(Porownywalne& inny)
{
	if ((this->wynik == inny.wynik) && (this->nazwa == inny.nazwa))
		return 0;
	else if (inny.wynik > this->wynik)
		return 1;
	else if (inny.nazwa > this->nazwa)
		return 1;
}
//aaaa sortownia nie chce mi sie pisac
void sortuj(vector<Porownywalne*>& wektor)
{
	
}


int main()
{
	srand(time(NULL));
	vector<Porownywalne*>rysowalne;
	rysowalne.push_back(new TabelaWynikow());
	TabelaWynikow tabela;
	//statek.rysuj();
	for (vector<Porownywalne*>::iterator itr = rysowalne.begin(), koniec = rysowalne.end(); itr != koniec; ++itr)
	{
		cout<<(*itr)->porownaj(tabela);
		cout << "\n";
	}
}

