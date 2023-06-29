#pragma once

#include <fstream>
#include "map.h"
#include "mapLoader.h"
using namespace std;

struct Model
{
	//position at which model is, must be set manually
	Coords* modelOffsets=nullptr;
	wchar_t* model = nullptr;
	int offsetsCount=0;
	//wchar_t* buffer //to keep whatever is behind that model
	wchar_t* buffer = nullptr;

	Model(Coords* offsets, wchar_t* ObjectModel, int count) :modelOffsets(offsets), offsetsCount(count),model(ObjectModel)/*buffer(new wchar_t[count])*/ {};

	~Model()
	{
		delete[] modelOffsets;
		//delete[] buffer;
		delete[] model;
	}
};

class modelLoader {
public:
	static int getNumberOfOutputCoords(const wstring* output, const int& lineCount)
	{
		int outputCoordsNumber = 0;

		for (int x = 0; x < lineCount; x++)
			for (int y = 0; y < output[x].size(); y++)
			{
				if (output[x][y] != ' ')
					outputCoordsNumber++;
			}

		return outputCoordsNumber;
	}

	static Model loadFromFile(const string& fileName)
	{
		wifstream ifs{ fileName };

		if (!ifs)
			throw exception("Model File not found!");


		int lineCount = mapLoader::getFileLineCount(ifs);

		//clear eof flag and go to the beginning
		ifs.clear();
		ifs.seekg(0, ios::beg);

		wstring* output = new wstring[lineCount];

		wstring line;

		for (int x = 0; mapLoader::getline(ifs, line) && x < lineCount; x++)
			output[x] = line;

		//get number of output coords
		int outputCoordsNumber = getNumberOfOutputCoords(output, lineCount);

		Coords* outputCoords = new Coords[outputCoordsNumber];
		wchar_t* model = new wchar_t[outputCoordsNumber];
		int outputCoordsCounter = 0;
		for (int x = 0; x < lineCount; x++)
		{
			for (int y = 0; y < output[x].size(); y++)
			{
				if (output[x][y] != ' ')
				{
					//get offset and save whatever should be at this offset
					outputCoords[outputCoordsCounter] = Coords{ x,y };
					model[outputCoordsCounter] = output[x][y];
					outputCoordsCounter++;
				}
			}
		}

		return Model(outputCoords, model, outputCoordsNumber);
	}
};