#pragma once
#include <iostream>
#include <fstream>
#include "map.h"

using namespace std;
class mapLoader {
private:

public:
	static void printImage(const string& fileName)
	{
		ifstream ifs{ fileName };
		if (!ifs)
			throw exception("Image file name was not found");

		string line;
		while (mapLoader::getline(ifs, line))
			cout << line<<"\n";
	}

	//cant use string library so i wrote my own implementation
	static istream& getline(istream& is, string& output, const char& delim = '\n')
	{
		//clear string
		output.clear();

		char c;
		while (is.get(c) && c != delim)
			output.push_back(c);
		return is;
	}

	static int getFileLineCount(istream& is)
	{
		int output = 0;

		string line;
		while (getline(is, line))
			output++;

		return output;
	}
	
	static Map loadMap(const string& fileName)
	{
		ifstream ifs{ fileName };

		if (!ifs)
			throw exception("Map File not found!");

		int lineCount = getFileLineCount(ifs);

		//clear eof flag and go to the beginning
		ifs.clear();
		ifs.seekg(0, ios::beg);

		string* output = new string[lineCount];

		string line;

		for (int x = 0; getline(ifs, line) && x < lineCount; x++)
			output[x] = line;

		return Map(output, lineCount);
	}
};
