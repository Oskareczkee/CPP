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
	void init(const string const* map, const unsigned int& mapSize)
	{
		for (int x = 0; x < mapSize; x++)
		{
			for (int y = 0; y < map[x].size(); y++)
			{
				if (map[x][y] == (char)GameSymbols::Player)
					player = Coords{ x,y };
				else if (map[x][y] == (char)GameSymbols::Box)
					boxCount++;
			}
		}

		if (player.x == -1)
			throw exception("Player could not be found on the map!");
	}
public:
	Map(string* data, unsigned int size) : map(data), size(size) { init(map, size); }
	~Map() 
	{
		delete[] map;
	}

	string* map=nullptr;
	unsigned int size = 0;
	unsigned int boxCount=0;
	unsigned int maxMoves = 15;
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
		map = new string[other.size];
		size = other.size;

		for (int x = 0; x < other.size; x++)
			map[x] = other.map[x];

		boxCount = other.boxCount;
		maxMoves = other.maxMoves;
		player=other.player;
		offset=other.offset;

		return *this;
	}

	friend ostream& operator<<(ostream& os, const Map& map)
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
