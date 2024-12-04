#include "HexMinimax.h"

bool HexMinimax::is_player_move()
{
	if (_is_blue_computer) return _red_pawns == _blue_pawns; //player is red
	else				    return _red_pawns != _blue_pawns;
}

bool HexMinimax::is_blue_move()
{
	return _red_pawns != _blue_pawns;
}

HexMinimax::HexMinimax(HexTile** board, const int& red_pawns, const int& blue_pawns, const int& size)
	: _board(board), _size(size), _red_pawns(red_pawns), _blue_pawns(blue_pawns)
{

	for (int x = 0; x < _size; x++) {
		for (int y = 0; y < _size; y++) {
			if (_board[x][y].pawn_type == PawnType::NONE)
				available_tiles.push_back({ x,y });
		}
	}

}

void HexMinimax::rewind_last_move()
{
	if (rewind_table.get_size() <= 0)return; //no move to rewind

	Coordinates coord = rewind_table[rewind_table.get_size() - 1]; //get last move
	_board[coord.x][coord.y].pawn_type = PawnType::NONE;
	rewind_table.pop_back();
}

bool HexMinimax::can_win_with_naive_opponent(const int& moves, bool is_blue_computer)
{
	if (!is_worth_checking(moves))
		return false;

	//pre prepare for recursive call
	_is_blue_computer = is_blue_computer;
	bool player_move = is_player_move();
	bool blue_move = is_blue_move();
	rewind_table.clear();

	//_is_blue_computer ? std::cout << "Blue is computer\n" : std::cout << "Red is computer\n";

	int player_moves = player_move ? 1 : 0;
	bool out = can_win_with_naive_opponent_rec(moves, player_moves, player_move, blue_move);

	while (rewind_table.get_size() > 0)
		rewind_last_move();

	return out;
}

bool HexMinimax::can_win_with_naive_opponent_rec(const int& moves, const int& player_moves, const bool& player_move, const bool& blue_move)
{
	//blue_move ? std::cout << "Blue move\n" : std::cout << "Red move\n";
	//player_move ? std::cout << "Player move\n" : std::cout << "Computer move\n";
	//std::cout << "Player moves: " << player_moves << "\n";

	if (player_moves > moves)
		return false;

	for (int x = 0; x < available_tiles.get_size(); x++)
	{
		Coordinates coord = available_tiles[x];

		//this is much faster, than caring about removing value from the table for recursive call, and then rewinding it (to the proper index)
		if (_board[coord.x][coord.y].pawn_type != PawnType::NONE) continue;

		_board[coord.x][coord.y].pawn_type = blue_move ? PawnType::BLUE : PawnType::RED;
		rewind_table.push_back(coord);

		if (!can_connect(coord.x, coord.y, 1, blue_move ? PawnType::BLUE : PawnType::RED))
		{
			rewind_last_move();
			continue;
		}

		//We assume that the player always plays optimally to win in the move we are asking about (first or second)
		//player turn
		if (player_move)
		{
			bool wins = HexPathFinder(_board, _size).path_exists(blue_move);
			if (wins && player_moves == moves)	return true;
			else if (wins) rewind_last_move();

			//minimax next move here
			else if (player_moves != moves)
			{
				if (can_win_with_naive_opponent_rec(moves, player_moves, !player_move, !blue_move)) //computer move
					return true;
				rewind_last_move();
			}

			//search for next move
			else
				rewind_last_move();
		}

		//computer turn
		//naive opponent does not want to win, if he wins, search for next move
		else {
			if (HexPathFinder(_board, _size).path_exists(blue_move)) {
				rewind_last_move();
				continue;
			}

			//minimax next move here
			else
			{
				if (can_win_with_naive_opponent_rec(moves, player_moves + 1, !player_move, !blue_move)) //player move
					return true;
				rewind_last_move();
			}
		}

	}

	return false; //such move has not been found
}

bool HexMinimax::can_win_with_perfect_opponent(const int& moves, bool is_computer_blue)
{
	if (!is_worth_checking(moves))
		return false;

	//pre prepare for recursive call
	_is_blue_computer = is_computer_blue;
	_opponent_won = false;
	_player_can_win = false;
	bool player_move = is_player_move();
	bool blue_move = is_blue_move();
	rewind_table.clear();
	//_is_blue_computer ? std::cout << "Blue is computer\n" : std::cout << "Red is computer\n";


	int player_moves = player_move ? 1 : 0;
	bool out = can_win_with_perfect_opponent_rec(moves, player_moves, player_move, blue_move);

	while (rewind_table.get_size() > 0)
		rewind_last_move();

	return out;
}

bool HexMinimax::can_win_with_perfect_opponent_rec(const int& moves, const int& player_moves, const bool& player_move, const bool& blue_move)
{
	if (player_moves > moves) return _opponent_won ? false : _player_can_win;

	//check all moves for player and computer

	if (!player_move) {
		for (int x = 0; x < available_tiles.get_size(); x++)
		{
			Coordinates coord = available_tiles[x];

			//this is much faster, than caring about removing value from the table for recursive call, and then rewinding it (to the proper index)
			if (_board[coord.x][coord.y].pawn_type != PawnType::NONE) continue;

			_board[coord.x][coord.y].pawn_type = blue_move ? PawnType::BLUE : PawnType::RED;
			rewind_table.push_back(coord);

			
			if (!can_connect(coord.x, coord.y, 1, blue_move ? PawnType::BLUE : PawnType::RED))
			{
				rewind_last_move();
				continue;
			}

			//computer turn
			//naive opponent does not want to win, if he wins, search for next move
			if (HexPathFinder(_board, _size).path_exists(blue_move)) {
				_opponent_won = true;
				return false;
			}
			else rewind_last_move();
		}
	}

	//if winning strategy has not been found for player nor computer, explore further nodes
	for (int x = 0; x < available_tiles.get_size(); x++)
	{
		Coordinates coord = available_tiles[x];

		//this is much faster, than caring about removing value from the table for recursive call, and then rewinding it (to the proper index)
		if (_board[coord.x][coord.y].pawn_type != PawnType::NONE) continue;

		_board[coord.x][coord.y].pawn_type = blue_move ? PawnType::BLUE : PawnType::RED;
		rewind_table.push_back(coord);

		if (!can_connect(coord.x, coord.y, 1, blue_move ? PawnType::BLUE : PawnType::RED))
		{
			rewind_last_move();
			continue;
		}

		if (player_move) {

			bool path_exists = HexPathFinder(_board, _size).path_exists(blue_move);
			if (path_exists && player_moves == moves) {
				_player_can_win = true;
				rewind_last_move();
				return true;
			}
			else if (path_exists) { rewind_last_move(); continue; }
			else can_win_with_perfect_opponent_rec(moves, player_moves, !player_move, !blue_move);

			if (_opponent_won) return false;
			rewind_last_move();
		}
		else {
			can_win_with_perfect_opponent_rec(moves, player_moves + 1, !player_move, !blue_move);

			if (_opponent_won) return false;
			rewind_last_move();
		}
	}

	return _opponent_won ? false :_player_can_win; //such move has not been found
}
