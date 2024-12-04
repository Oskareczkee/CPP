#include "HexBoard.h"

bool HexBoard::is_board_correct()
{
	//the starting player is red, so if there is more blue than red, then board is incorrect
	return blue_pawns <= red_pawns //there is less or equal blue pawns
		&& abs(blue_pawns - red_pawns) <= 1; //and difference in number of pawns is no bigger than 1
}

bool HexBoard::has_blue_won()
{
	HexPathFinder hpf(_board, _size);
	return hpf.path_exists();
}

bool HexBoard::has_red_won()
{
	HexPathFinder hpf(_board, _size);
	return hpf.path_exists(false); // false -> check if path exists for red
}

bool HexBoard::is_board_possible()
{
	HexPathFinder hpf(_board, _size);

	if (!is_board_correct())				return false;
	if (hpf.path_count() > 1)				return false;
	if (hpf.path_count(false) > 1)			return false;
	//if (has_blue_won() && has_red_won())    return false; //in hex it is impossible for 2 players to win at once, no need to waste resources

	return true;
}

bool HexBoard::can_win_with_naive_opponent(const int& moves, bool is_computer_blue)
{
	if (!is_board_correct())
		return false;

	return HexMinimax(_board, red_pawns, blue_pawns, _size).can_win_with_naive_opponent(moves, is_computer_blue);
}

bool HexBoard::can_win_with_perfect_opponent(const int& moves, bool is_computer_blue)
{
	if (!is_board_correct()) return false;
	return HexMinimax(_board, red_pawns, blue_pawns, _size).can_win_with_perfect_opponent(moves, is_computer_blue);
}

HexBoard::~HexBoard()
{
	for (int x = 0; x < _size; x++)
		delete[] _board[x];
	delete[] _board;
}
