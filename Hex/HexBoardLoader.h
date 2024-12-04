#pragma once
#include <iostream>
#include "HexTile.h"
#include "HexBoard.h"
#include <sstream>
#include <string>
#include <algorithm>

enum class HexBoardTiles {
	TILE_BEGIN='<',
	TILE_END='>',
	TILE_WALL='-'
};

class HexBoardLoader
{
private:
	std::istream& stream;
public:
	HexBoardLoader(std::istream& istream): stream(istream){}
	int get_size();
	HexBoard* load_board();
};