#pragma once
#include "HexTile.h"
#include "HexPathFinder.h"
#include "HexMinimax.h"
#include <iostream>

class HexBoard
{
private:
	int _size;
	HexTile** _board = nullptr;
	int red_pawns = 0;
	int blue_pawns = 0;

	friend class HexBoardLoader;
public:
	int get_size() { return _size; }
	int get_red_pawns_count(){return red_pawns;}
	int get_blue_pawns_count(){return blue_pawns;}

	bool is_board_correct();

	bool has_blue_won();
	bool has_red_won();
	bool is_board_possible();
	bool can_win_with_naive_opponent(const int& moves, bool is_computer_blue = false);
	bool can_win_with_perfect_opponent(const int& moves, bool is_computer_blue = false);

	//destructor
	~HexBoard();

	void print_array()
	{
		for (int x = 0; x < _size; x++)
		{
			for (int y = 0; y < _size; y++) {
				std::cout << "[" << x << "," << y << "(" << (char)_board[x][y].pawn_type << ")] ";
			}
			std::cout << "\n";
		}
	}
};
