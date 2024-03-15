#pragma once
#include <iostream>
#include <iomanip>
#include <random>
#include <algorithm>
#include <numeric>
#include <conio.h>
#include <math.h>
#include <chrono>
#include <thread>
#include "GameState.h"
#include "UndoRedoStack.h"

using namespace std;

class BlackBoxGame
{
    private:
        enum class Directions
        {
            NONE=-1,
            NORTH,
            EAST,
            SOUTH,
            WEST,
        };

        GameState _game;
        UndoRedoStack<GameState,10> _undo_stack;
        UndoRedoStack<GameState, 10> _redo_stack;
        
        //here add stack with previous game states for undo/redo


        bool _showAtoms = false;

        const int CELL_WIDTH=3; //cell width must be fixed 
                                //so numbers up to 999 can be shown
        const int LOOP_MAX_ITERATIONS = 100; //prevents from looping program
                                             //sometimes beam might loop between atoms, we have to detect it
        const int MAX_HELPS = 2;
        const wchar_t ATOM = L'A';
        const wchar_t ATOM_HIT = L'H';
        const wchar_t ATOM_CHECK = L'o';
        const wchar_t ATOM_GUESSED = L'O';
        const wchar_t REFLECTION = 'R';
        const wchar_t CURSOR = L'×';
        const wchar_t CURSOR_UP = L'^';
        const wchar_t CURSOR_DOWN = L'ˇ';
        const wchar_t CURSOR_RIGHT = L'>';
        const wchar_t CURSOR_LEFT = L'<';
        const wchar_t EMPTY_CELL = L' ';

        int cursorX = 0, cursorY = 0;
        int atom_count = 3;
        int atom_mark_count = 0;
        int settings_board_width = 5;
        int settings_board_height = 5;
        int helps_used = 0;

    private:
        /*Basic console and menu*/
        void WaitForInput();
        wchar_t GetInput();
        //returns true if input was successfully processed
        bool ProcessInput(const wchar_t& input);
        //moves cursor in given direction and changes its coordinate and direction
        void MoveCursor(const Directions& direction);

        bool IsInBound(const int& xCoord, const int& yCoord);
        //returns true if coordinates are in bound of cursor bounds (board + sides)
        bool IsInCursorBound(const int& xCoord, const int& yCoord);
        //checks if cursor is in side bound (side bounds are smaller by 1)
        //if cursosr is not on the side panel, returns true always
        bool IsInCursorSideBound(const int& xCoord, const int& yCoord);
        //returns on which side of board cursor is, if is not returns NONE

        /*Tools to render board*/
        void PrintBoardSideInteractions(const Directions& direction, const int& coord);
        void PrintBoardSide(const Directions& direction, const int& coord);
        void PrintBorder(const Directions& directions, const int& coord);
        void PrintPadding();

        void ShowMainMenu();
        void ShowGenerateLevel();
        void ClearScreen();
        void ShowAuthor();

        /*Game logic*/
        //shoots beam, from north, east, south or west
        void ShootBeam(const int& coordinate, const Directions& direction);
        //sets dx dy, depending on direction for proper movement
        void SetDeltas(int& dx, int& dy, const Directions& direction);
        //returns true if atom is present at given coordinates
        bool CheckAtom(const int& xCoord, const int& yCoord);
        //returns true if coordinates are in bound of board
        Directions ReturnCursorDirection();
        Directions ReturnBeamDirection(const int& dx, const int& dy);
        //checks for deflections, changes deltas to proper direction, returns true if deflection occured
        bool CheckDeflection(const int& xCoord, const int& yCoord,
                                   int& dx, int& dy);
        bool CheckInstantReflection(const int& xCoord, const int& yCoord, const Directions& beam_direction);
        //returns opposite direction to given one
        Directions GetOppositeDirection(const Directions& direction);

        void ShowAtoms(const int& msDuration=1000);
        void MarkAtom(const int& xCoord, const int& yCoord);

        void EndGame();

        void Undo();
        void Redo();

        //resets all settings to 0
        void Reset();

        /*Rendering*/
        void DrawBoard();
        void GenerateBoard(const int& width,
            const int& height,
            const int& atom_amount);

        void GameLoop();
    public:
        BlackBoxGame();
        void Start();
};