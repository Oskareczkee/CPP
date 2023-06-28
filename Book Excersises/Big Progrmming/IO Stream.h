#pragma once
#include <fstream>
#include <vector>
#include <string>
#define IO_STREAM

using namespace std;

void Add_Score()
{
	//creating new bin file, if one does not exist

	ofstream* createFile=new ofstream("score.bin");
	createFile->close();
	delete createFile;

	fstream file("score.bin", ios::in | ios::out | ios::binary);
	if (!file.is_open())
	{
		cout << "Couldn't open the file !\n";
		return;
	}
	int newScore;
	cout << "Enter new score: ";
	cin >> newScore;
	
	streampos prevPos = file.tellg();
	int fileScore;

	while (file.read(reinterpret_cast<char*>(&fileScore), sizeof(fileScore)))
	{
		if (fileScore < newScore)
		{
			break;
		}
		prevPos = file.tellg();
	}

	if (file.fail() && !file.eof())
	{
		cout << "Reading Score from file went wrong.";
		return;
	}
	file.clear();

	file.seekg(prevPos);

	vector<int> Score;

	while (file.read(reinterpret_cast<char*>(&fileScore), sizeof(fileScore)))
	{
		Score.push_back(fileScore);
	}

	if (!file.eof())
	{
		cout << "Saving Score from file to vector went wrong.";
		return;
	}

	file.clear();

	file.seekp(prevPos);

	file.write(reinterpret_cast<char*>(&newScore), sizeof(newScore));

	for (vector<int>::iterator itr = Score.begin(); itr != Score.end(); ++itr)
		file.write(reinterpret_cast<char*>(*itr), sizeof(*itr));

}

void Read_Score()
{
     ifstream file("score.bin", ios::binary);

	 if (!file.is_open())
	 {
		 cout << "couldn't open the file !";
	     return;
	 }

	 int fileScore;

	 vector<int> Scores;

	 while (file.read(reinterpret_cast<char*>(&fileScore), sizeof(fileScore)))
	 {
		 Scores.push_back(fileScore);
	 }

	 cout << "Scores:\n\n";

	 for (vector<int>::iterator itr = Scores.begin(); itr != Scores.end(); ++itr)
	 {
		 cout << *itr << endl;
	 }
	
}

string wykryj_znak(string tekst)//poczatek oznacza jakies miejsce w tekscie, od ktorego trzeba zaczac//bede zwracal tablice znakow, czyli stringa
{
    string wykryte_znaki;
    for (int x = 0; x < tekst.length(); x++)
    {
        if (tekst[x] == 32 || (tekst[x] >= 48 && tekst[x] <= 57) || (tekst[x] >= 65 && tekst[x] <= 90) || (tekst[x] >= 97 && tekst[x] <= 122))
        {
            continue;
        }
        else
        {
            if (wykryte_znaki.find(tekst[x]) == string::npos)
            {
                wykryte_znaki += tekst[x];
            }
        }
    }
    return wykryte_znaki;
}

vector<string> znaczniki = { "<html>","</html>","<head>","</head>","<body>","</body>","<b>","</b>","<i>","</i>","<a>","</a>" };
enum index_enum { html, endhtml, head, endhead, body, endbody, b, endb, i, endi, a, enda };//end==</"znacznik">

int zwroc_index_znacznika(string znacznik)
{
    bool znaleziono = false;
    int index_znacznika = 0;
    if (znacznik[0] == '<' && znacznik[1] == 'a')//zwraca wartosc 10, gdy napotka znacznik linku
    {
        return 10;
    }
    for (vector<string>::iterator itr = znaczniki.begin(); itr != znaczniki.end(); ++itr)
    {
        if (*itr == znacznik)
        {
            znaleziono = true;
            return index_znacznika;
        }
        index_znacznika++;
    }

    if (znaleziono == false)
    {
        cout << "Znacznik nie istnieje, lub nie jest zawarty w bazie znacznikow\n";
        return -1;
    }
}

int oblicz_dlugosc_head(int miejsce_w_tekscie, const string& kod_sformatowany)
{
    string znacznik;
    for (int x = 0; x < kod_sformatowany.length(); x++)
    {
        if (kod_sformatowany[miejsce_w_tekscie + x] == '<')
        {
            for (; x < kod_sformatowany.length(); x++)
            {
                if (kod_sformatowany[miejsce_w_tekscie + x] != '>')
                {
                    znacznik += kod_sformatowany[miejsce_w_tekscie + x];
                }
                else
                {
                    znacznik += '>';
                    cout << "\n" << znacznik << "\n";
                    if (zwroc_index_znacznika(znacznik) == 3)
                    {
                        return x + 2;
                    }
                    else
                    {
                        znacznik.erase();
                        continue;
                    }
                }
            }
        }
    }
    return 0;

}

int oblicz_dlugosc_linku(int miejsce_w_tekscie, const string& kod_sformatowany)
{
    string znacznik;
    for (int x = 0; x < kod_sformatowany.length(); x++)
    {
        if (kod_sformatowany[miejsce_w_tekscie + 1] == 'a')
        {
            for (; x < kod_sformatowany.length(); x++)
            {
                if (kod_sformatowany[miejsce_w_tekscie + x] != '>')
                {
                    znacznik += kod_sformatowany[miejsce_w_tekscie + x];
                }
                else
                {
                    znacznik += '>';
                    cout << "\n" << znacznik << "\n";
                    return znacznik.length();
                }
            }
        }
    }
    return 0;
}

bool formatuj_tekst(string znacznik, string& kod_sformatowany, int miejsce_w_tekscie)
{
    int index_znacznika = zwroc_index_znacznika(znacznik);
    if (index_znacznika != -1)
    {
        switch (index_znacznika)
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
            int dlugosc_head = oblicz_dlugosc_head(miejsce_w_tekscie + 1, kod_sformatowany);
            kod_sformatowany.erase(miejsce_w_tekscie, dlugosc_head);
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
        case b:
        {
            kod_sformatowany.erase(miejsce_w_tekscie, znaczniki[index_znacznika].length());
            kod_sformatowany.insert(miejsce_w_tekscie, "*");
            return 1;
            break;
        }
        case endb:
        {
            kod_sformatowany.erase(miejsce_w_tekscie, znaczniki[index_znacznika].length());
            kod_sformatowany.insert(miejsce_w_tekscie, "*");
            return 1;
            break;
        }
        case i:
        {
            kod_sformatowany.erase(miejsce_w_tekscie, znaczniki[index_znacznika].length());
            kod_sformatowany.insert(miejsce_w_tekscie, "_");
            return 1;
            break;
        }
        case endi:
        {
            kod_sformatowany.erase(miejsce_w_tekscie, znaczniki[index_znacznika].length());
            kod_sformatowany.insert(miejsce_w_tekscie, "_");
            return 1;
            break;
        }
        case a:
        {
            int dlugosc_linku = oblicz_dlugosc_linku(miejsce_w_tekscie, kod_sformatowany);
            kod_sformatowany.erase(miejsce_w_tekscie, dlugosc_linku);
            kod_sformatowany.insert(miejsce_w_tekscie, "(linkurl)");
            return 1;
            break;
        }
        case enda:
        {
            kod_sformatowany.erase(miejsce_w_tekscie, znaczniki[index_znacznika].length());
            kod_sformatowany.insert(miejsce_w_tekscie, "(linkurl)");
            return 1;
            break;
        }
        }
    }
    else
    {
        return 0;
    }
}

void HTML_Analyzer()
{
	string kod;
	string kod_sformatowany;
	string znacznik;
	int miejsce_w_tekscie = 0;
	int tak = 0;
	cout << "Podaj nazwe pliku z kodem HTML\n";
	getline(cin, kod, '\n');
    ifstream code(kod, ios::beg);
    if (!code.is_open())
    {
        cout << "Couldn't open the file !\n";
        return;
    }
    while (!code.eof()) { string temp; code >> temp; kod_sformatowany+=temp+" "; }
    cout << kod_sformatowany << "\n";
	for (int x = 0; x < kod_sformatowany.length(); x++, x -= tak)
	{
		tak = 0;
		znacznik.erase();
		znacznik.shrink_to_fit();
		kod_sformatowany.shrink_to_fit();
		if (kod_sformatowany[x] == '<')
		{
			miejsce_w_tekscie = x;
			for (; x < kod_sformatowany.length(); x++)
			{
				if (kod_sformatowany[x] != '>')
				{
					znacznik += kod_sformatowany[x];
				}
				else
				{
					znacznik += '>';
					if (formatuj_tekst(znacznik, kod_sformatowany, miejsce_w_tekscie) != false)
					{
						int dlugosc_znacznika = znacznik.length();
						tak = dlugosc_znacznika;
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
	cout << kod_sformatowany;
	//<<znaczniki[1]<<znaczniki[1].length();
}

