#pragma once
#include "HexCoord.h"
enum class PawnType {
	NONE = ' ',
	RED='r',
	BLUE='b'
};

struct HexTile
{
	HexCoord cube_coord;
	PawnType pawn_type;
};
