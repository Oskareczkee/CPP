#pragma once
#include <iostream>
#include "HexTile.h"
#include "HexPathFinder.h"
#include "vector.h"

class HexMinimax {
private:
	struct Coordinates {
		int x = 0, y = 0;
	};

	HexTile** _board = nullptr; //reference to the board
	int _size = 0;				//size of the board

	int _red_pawns = 0;
	int _blue_pawns = 0;

	vector<Coordinates> available_tiles; //all available tiles for moves
	vector<Coordinates> rewind_table;    //for rewinding moves, this way we do not have to copy board each recursive call

	void rewind_last_move();
	bool is_player_move(); //returns true if now it is red move, otherwise returns false -> blue move
	bool is_blue_move();
	bool _is_blue_computer = false;
	bool _opponent_won = false;
	bool _player_can_win = false;

	bool is_worth_checking(const int& moves) {
		if (_red_pawns < (_size - moves - 1)) return false;
		if (_blue_pawns < (_size - moves - 1)) return false;

		return true;
	}

	bool is_border_tile(const int& x, const int& y)
	{
		if (x == 0 || x == _size - 1) return true;
		if (y == 0 || y == _size - 1) return true;
		return false;
	}

	bool can_connect(const int& x, const int& y,const int& radius, PawnType color)
	{
		int neighbors = 0;

		if (radius >= _size)
			return true;

		for (int r = 1; r <= radius; r++) {
			for (auto& vec : AxialVectors::Vectors)
			{
				int coordX = x + vec.p*r;
				int coordY = y + vec.q*r;

				if (is_proper_coordinate(coordX, coordY) && _board[coordX][coordY].pawn_type == color)
					neighbors++;
				else if (is_border_tile(coordX, coordY) && !is_border_tile(x,y))
					neighbors++;
			}
		}

		if (is_border_tile(x, y)) {
			if (_size >= 3)
				return neighbors >= 1;
			return true;
		}
		return neighbors >= 2;
	}

	bool is_proper_coordinate(const int& x, const int& y)
	{
		return x >= 0 && x < _size &&
			y >= 0 && y < _size;
	}



	//recursive functions
	bool can_win_with_naive_opponent_rec(const int& moves, const int& player_moves, const bool& player_move, const bool& blue_move); //returns true if red can win with naive blue opponnent (stupid)
	bool can_win_with_perfect_opponent_rec(const int& moves, const int& player_moves, const bool& player_move, const bool& blue_move); //returns true if red can win with perfec blue opponent (mastermind)
public:
	HexMinimax(HexTile** board, const int& red_pawns, const int& blue_pawns, const int& size);

	bool can_win_with_naive_opponent(const int& moves, bool is_blue_computer = false); //returns true if red can win with naive blue opponnent (stupid)
	bool can_win_with_perfect_opponent(const int& moves, bool is_blue_computer = false); //returns true if red can win with perfec blue opponent  (mastermind)


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