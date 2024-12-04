#include <iostream>
#include <sstream>
#include <fstream>
#include <string.h> //C string functions
#include "HexBoardLoader.h"
#define BOARD_STRING_LENGTH 10000
#define STRING_LINE_LENGTH 200

using namespace std;

//GLOBAL VARIABLES

	//load the board into stringstream
	//string stream has an ability to seek its position, which will be usefull for us
	//in std::cin everything is flushed after reading so seeking position is impossible
	istringstream iss;
	HexBoardLoader hbl(iss);
	ifstream ifs{ R"(.\Tests\11.in.txt)" };
	istream& input_stream = ifs;
	bool red_wins = false;

//END GLOBAL VARIABLES

char* load_board_from_stream(istream& stream)
{
	char out[BOARD_STRING_LENGTH] = { 0 };
	char line[STRING_LINE_LENGTH] = { 0 };

	//load first line
	stream.getline(line, STRING_LINE_LENGTH, '\n');
	strcat_s(out, line);//append line to the output
	strcat_s(out, "\n");//append newline character, cause it was lost during getline

	//this loop ends, when it encounters --- at the end of the board input
	while (true) {
		stream.getline(line, STRING_LINE_LENGTH, '\n');
		int len = strlen(line);
		if (strcmp(line + len - 3, "---") == 0)//if at the end of the line is --- combination, ignore this line, and end loading
			return out;

		strcat_s(out, line);//append line to the output
		strcat_s(out, "\n");//append newline character, cause it was lost during getline
	}
}

//parses query and prints to the stdout (cout)
void parse_query(const char* q, HexBoard& board)
{
	if (strcmp(q, "BOARD_SIZE") == 0)
		cout << board.get_size() << "\n";
	else if (strcmp(q, "PAWNS_NUMBER") == 0)
		cout << board.get_blue_pawns_count() + board.get_red_pawns_count() << "\n";
	else if (strcmp(q, "IS_BOARD_CORRECT") == 0)
		board.is_board_correct() ? cout << "YES\n" : cout << "NO\n";
	else if (strcmp(q, "IS_GAME_OVER") == 0)
	{
		if (!board.is_board_correct()) cout << "NO\n";
		else if (board.has_blue_won()) cout << "YES BLUE\n";
		else if (board.has_red_won())  cout << "YES RED\n";
		else						   cout << "NO\n";
	}
	else if (strcmp(q, "IS_BOARD_POSSIBLE") == 0)
		board.is_board_possible() ? cout << "YES\n" : cout << "NO\n";

	//NAIVE OPPONENT QUERIES
	else if (strcmp(q, "CAN_RED_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT") == 0)
		board.can_win_with_naive_opponent(1, true) ? cout << "YES\n" : cout << "NO\n";

	else if (strcmp(q, "CAN_BLUE_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT") == 0)
		board.can_win_with_naive_opponent(1, false) ? cout << "YES\n" : cout << "NO\n";

	else if (strcmp(q, "CAN_RED_WIN_IN_2_MOVES_WITH_NAIVE_OPPONENT") == 0)
		board.can_win_with_naive_opponent(2, true) ? cout << "YES\n" : cout << "NO\n";

	else if (strcmp(q, "CAN_BLUE_WIN_IN_2_MOVES_WITH_NAIVE_OPPONENT") == 0)
		board.can_win_with_naive_opponent(2, false) ? cout << "YES\n" : cout << "NO\n";
	//END NAIVE OPPONENT QUERIES

	//PERFECT OPPONENT QUERIES
	else if (strcmp(q, "CAN_RED_WIN_IN_1_MOVE_WITH_PERFECT_OPPONENT") == 0)
		board.can_win_with_perfect_opponent(1, true) ? cout << "YES\n" : cout << "NO\n";

	else if (strcmp(q, "CAN_BLUE_WIN_IN_1_MOVE_WITH_PERFECT_OPPONENT") == 0)
		board.can_win_with_perfect_opponent(1, false) ? cout << "YES\n" : cout << "NO\n";

	else if (strcmp(q, "CAN_RED_WIN_IN_2_MOVES_WITH_PERFECT_OPPONENT") == 0)
		board.can_win_with_perfect_opponent(2, true) ? cout << "YES\n" : cout << "NO\n";

	else if (strcmp(q, "CAN_BLUE_WIN_IN_2_MOVES_WITH_PERFECT_OPPONENT") == 0)
		board.can_win_with_perfect_opponent(2, false) ? cout << "YES\n" : cout << "NO\n";
	//END PERFECT OPPONENT QUERIES

}


int main()
{
	char query[STRING_LINE_LENGTH];
	int test = 0;

	while (input_stream)
	{
		iss.str(load_board_from_stream(input_stream));
		HexBoard* board = hbl.load_board();
	
		
		/*
		test++;
		//test 518 print board
		if (test == 488) {
			cout<<"\n\n"<<iss.str()<<"\n\n";
			cin.get();
		}
		*/

		char c;
		//parse all queries till we get to the newline character
		while (input_stream ) {
			input_stream.get(c);
			if (c == '\n' || c == ' ')
				break;

			input_stream.putback(c);
			input_stream >> query;
			parse_query(query, *board);
			input_stream.get();
		}

		std::cout << iss.str()<<"\n";
		cin.get();

		std::cout << "\n";

		input_stream.get();//skip newline, for some reason it does not skip
		//eof check
		c = input_stream.get();
		if (!input_stream)
			break;
		input_stream.putback(c);

		delete board;
	}
}
