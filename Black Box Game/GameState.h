#pragma once
#include <algorithm>


struct GameState
{
    wchar_t** _board; //board with atoms on it
    wchar_t** _atom_checks; //board with atoms checks on it
    int    _board_width;
    int    _board_height;
    //board side size should be board width * 4
    //first row: up, right, down, left
    wchar_t* _board_side;
    //where interactions are ATOM_HIT, REFLECTION, size same as board side
    wchar_t* _board_side_interactions;
    int shot_num = 0;

    GameState() :_board(nullptr), _board_width(0), _board_height(0),
        _board_side(nullptr), _board_side_interactions(nullptr),
        _atom_checks(nullptr)
    {}

    GameState(const int& width, const int& height) { Init(width, height); }
    ~GameState() { Clear(); }

    //copy operator, for safe copying
    GameState& operator=(const GameState& other);
    //copy constructor
    GameState(const GameState& other);

    void Clear(); //clears memory and all pointers, sets to null
    void Init(const int& width, const int& height);
};

