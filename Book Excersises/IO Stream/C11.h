#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstddef>

using namespace std;

void tolower(string fileName, string outputFileName)
{
	ifstream ifs{ fileName };

	if (!ifs) throw exception("Input file not found !");
	ifs.exceptions(ifs.exceptions() | ios::badbit);

	ofstream ofs{ outputFileName };
	if (!ofs) throw exception("Couldn't open/create output File !");
	ofs.exceptions(ofs.exceptions() | ios::badbit);


	string temp;

	//getline seems to be better in this case, it lets us keep text in original form
	while (getline(ifs, temp))
	{
		if (ifs.fail())
			ifs.clear();

		for (char& c : temp)
			if (isupper(c))
				c = tolower(c);

		//new line char is eaten by getline, so we add it
		ofs << temp<<"\n";
	}
}


vector<int> FindWord(const string& fileName, string word)
{
	ifstream ifs{ fileName };

	if (!ifs) throw exception("File was not found !");

	ifs.exceptions(ifs.exceptions() | ios::badbit);

	string temp;
	vector<int> FoundLines;

	for (int x = 1; getline(ifs, temp); x++)
	{
		istringstream iss{ temp };

		string tempWord;
		while (iss >> tempWord)
			if (tempWord == word)
				FoundLines.push_back(x);
	}

	return FoundLines;
}

void multi_input()
{
	cin.unsetf(ios::dec);
	cin.unsetf(ios::hex);
	cin.unsetf(ios::oct);

	int firstNum, secondNum, thirdNum;

	cout << "Please input 3 numbers in any format: \n";
	cin >> firstNum >> secondNum >> thirdNum;

	cout << firstNum << " " << secondNum << " " << thirdNum << "\n";
}

template<class T>
char* as_bytes(T& i)// t is a sequence of bytes
{
	void* addr = &i;// first byte address

	return static_cast<char*>(addr);
}

void TextToBinary(const string& textFile, const string& binFile)
{
	ifstream ifs{ textFile };
	if (!ifs) throw exception("text file has not been found");
	ifs.exceptions(ifs.exceptions() | ios::badbit);

	ofstream ofs{ binFile, ios::binary };
	if (!ofs) throw exception("couldn't open/create output file");
	ofs.exceptions(ofs.exceptions() | ios::badbit);

	string temp;

	while (getline(ifs, temp))
	{
		ofs.write(as_bytes(temp), sizeof(temp));
	}

}

vector<string> split(const string& s)
{
	istringstream ist{ s };

	string temp;
	vector<string> output;
	while (ist >> temp)
		output.push_back(temp);

	return output;
}

vector<string> split(const string& s, const string& whitechars)
{

	string copy = s;
	string temp;
	vector<string> output;

	//find and replace all whitechars with space
	for (char& c : copy)
	{
		//any find functions didn't work well
		for (const char& cc : whitechars)
			if (cc == c)
				c = ' ';
	}
	istringstream ist{ copy };

	while (ist >> temp)
		output.push_back(temp);

	return output;
}


//Text to Binary conversion is irreversible, that means i can convert text to bytes,
//but i cannot convert these bytes to text
//The solution could be saving binary file in hexadecimal format, then propably it would be possible

//But writing program to convert binary file into text is pretty much useless, because in many cases programmists propably won't
//worry about converting data to binary hexadecimal format

/*
void BinaryToText(const string& binFile, const string& textFile)
{
	ifstream ifs{ binFile, ios::binary };
	if (!ifs) throw exception("bin file has not been found");
	ifs.exceptions(ifs.exceptions() | ios::badbit);

	ofstream ofs{ textFile };
	if (!ofs) throw exception("couldn't open/create output file");
	ofs.exceptions(ofs.exceptions() | ios::badbit);

	char temp;

	while (ifs.read(as_bytes(temp), sizeof(temp)))
	{
		ofs <<temp;
	}
}
*/

