#pragma once
#include <fstream>
#include "mapLoader.h"

using namespace std;

class imageLoader
{
public:
	static void printImage(const wstring& fileName)
	{
		wifstream ifs{ fileName };
		if (!ifs)
		{
			wcout << "Image "<<fileName<<" could not be loaded!\n";
			return;
		}

		wstring line;
		while (mapLoader::getline(ifs, line))
			wcout << line << "\n";
	}
};