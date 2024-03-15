#include "GameState.h"

void GameState::Clear()
{
    if (_board == nullptr)
        return;

    //delete board
    for (int x = 0; x < _board_height; x++)
    {
        delete[] _atom_checks[x];
        delete[] _board[x];
    }
    delete[] _board;
    delete[] _atom_checks;

    //delete its sides
    delete[] _board_side;
    delete[] _board_side_interactions;

    _board_side = nullptr;
    _board_side_interactions = nullptr;
    _board = nullptr;
}

void GameState::Init(const int& width, const int& height)
{
    //clear memory if board is initialized
    if (_board != nullptr)
        Clear();

    //init new board
    _board = new wchar_t* [height];
    _atom_checks = new wchar_t* [height];
    for (int x = 0; x < height; x++)
    {
        _board[x] = new wchar_t[width];
        _atom_checks[x] = new wchar_t[width];
        std::fill(_board[x], _board[x] + width, L' ');//fill with spaces, otherwise will be filled with 0s (nulls)
        std::fill(_atom_checks[x], _atom_checks[x] + width,0);//fill with zeroes
    }

    //init its sides
    _board_side = new wchar_t[width * 4];
    std::fill(_board_side, _board_side + (width * 4), 0);//fill zeroes

    _board_side_interactions = new wchar_t[width * 4];
    std::fill(_board_side_interactions, _board_side_interactions + (width * 4), 0); //fill with zeroes

    _board_width = width;
    _board_height = height;
}

//operators 

//copy operator
GameState& GameState::operator=(const GameState& other)
{
    if (this == &other)
        return *this;

    Clear();

    //copy board
    _board_width = other._board_width;
    _board_height = other._board_height;
    
    _board = new wchar_t* [_board_height];
    _atom_checks = new wchar_t* [_board_height];
    for (int x = 0; x < _board_height; x++)
    {
        _board[x] = new wchar_t[_board_width];
        _atom_checks[x] = new wchar_t[_board_width];
        for (int y = 0; y < _board_width; y++)
        {
            _board[x][y] = other._board[x][y];
            _atom_checks[x][y] = other._atom_checks[x][y];
        }
    }

    //copy sides
    _board_side = new wchar_t[_board_width * 4];
    for (int x = 0; x < _board_width * 4;x++)
        _board_side[x] = other._board_side[x];

    _board_side_interactions = new wchar_t[_board_width * 4];
    for (int x = 0; x < _board_width * 4; x++)
        _board_side_interactions[x] = other._board_side_interactions[x];

    shot_num = other.shot_num;

    return *this;
}

//copy constructor, does all things like normal operator=, but does not clear memory
//memory is not set when object is created, it is foribidden to clear it
GameState::GameState(const GameState& other)
{
    //copy board
    _board_width = other._board_width;
    _board_height = other._board_height;

    _board = new wchar_t* [_board_height];
    _atom_checks = new wchar_t* [_board_height];
    for (int x = 0; x < _board_height; x++)
    {
        _board[x] = new wchar_t[_board_width];
        _atom_checks[x] = new wchar_t[_board_width];
        for (int y = 0; y < _board_width; y++)
        {
            _board[x][y] = other._board[x][y];
            _atom_checks[x][y] = other._atom_checks[x][y];
        }
    }

    //copy sides
    _board_side = new wchar_t[_board_width * 4];
    for (int x = 0; x < _board_width * 4; x++)
        _board_side[x] = other._board_side[x];

    _board_side_interactions = new wchar_t[_board_width * 4];
    for (int x = 0; x < _board_width * 4; x++)
        _board_side_interactions[x] = other._board_side_interactions[x];

    shot_num = other.shot_num;
}