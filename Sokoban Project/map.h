#pragma once
#include "Enumerators.h"

using namespace std;

struct Coords
{
	int x, y;
};

#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25

class Map
{
private:
	void init(const wstring* map, const int& mapSize)
	{
		bool playerFound = false;
		for (int x = 0; x < mapSize; x++)
		{
			for (int y = 0; y < map[x].size(); y++)
			{
				if (map[x][y] == (wchar_t)GameSymbols::Player && playerFound==false)
				{
					player = Coords{ x,y };
					playerFound = true;
				}
				else if (map[x][y] == (wchar_t)GameSymbols::Box)
					boxCount++;
			}
		}

		if (player.x == -1)
			throw exception("Player could not be found on the map!");
	}
public:
	Map(wstring* data, unsigned int size, const wstring& name, const int& max_moves) : map(data), size(size), levelName(name), maxMoves(max_moves) { init(map, size); }
	Map(){}

	//otherwise it wont work with our stack
	Map(const Map& other)
	{
		*this = other;
	}
	~Map() 
	{
		delete[] map;
	}

	wstring* map=nullptr;
	int size = 0;;
	int boxCount=0;
	int maxMoves = 100;
	int moveCount = 0;
	wstring levelName=L"";
	Coords player{-1,-1};
	Coords offset{ 0,0 };

	void changeOffset(const Coords& value)
	{
		if(offset.x+value.x<size && offset.x + value.x >= 0)
			offset.x += value.x;
		if (offset.y + value.y < SCREEN_WIDTH && offset.y + value.y >= 0)
			offset.y += value.y;
	}

	Map& operator=(const Map& other)
	{
		delete[] map;
		map = new wstring[other.size];
		size = other.size;

		for (int x = 0; x < other.size; x++)
			map[x] = other.map[x];

		boxCount = other.boxCount;
		maxMoves = other.maxMoves;
		player = other.player;
		offset = other.offset;
		moveCount = other.moveCount;

		return *this;
	}

	friend wostream& operator<<(wostream& os, const Map& map)
	{
		if (!os)
			return os;

		for (int x = 0 + map.offset.x; x < map.size && x < SCREEN_HEIGHT; x++)
		{
			for (int y = 0 + map.offset.y; y < map.map[x].size() && y < SCREEN_WIDTH; y++)
				os << map.map[x][y];
			os << "\n";
		}

		return os;
	}
};
