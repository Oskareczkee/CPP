#pragma once
#include <iostream>
#include <fstream>
#include "map.h"

using namespace std;
class mapLoader {
public:
	static int getFileLineCount(wistream& is)
	{
		int output = 0;

		wstring line;
		while (getline(is, line))
			output++;

		return output;
	}

	//cant use string library so i wrote my own implementation
	static wistream& getline(wistream& is, wstring& output, const wchar_t& delim = L'\n')
	{
		//clear string
		output.clear();

		wchar_t c;
		while (is.get(c) && c != delim)
			output.push_back(c);
		return is;
	}

	static Map loadMap(const wstring& fileName)
	{
		wifstream ifs{ fileName };

		if (!ifs)
			throw exception("Map File not found!");


		//-1 because we have max_moves at the top and we dont want to count it
		int lineCount = getFileLineCount(ifs)-1;

		//clear eof flag and go to the beginning
		ifs.clear();
		ifs.seekg(0, ios::beg);

		wstring max_moves;
		int max_movesInt = 0;
		getline(ifs, max_moves);
		max_movesInt = _wtoi(max_moves.c_str());

		wstring* output = new wstring[lineCount];

		wstring line;

		for (int x = 0; getline(ifs, line) && x < lineCount; x++)
			output[x] = line;

		return Map(output, lineCount, fileName, max_movesInt);
	}
};
