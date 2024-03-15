#include "Game.h"

void BlackBoxGame::WaitForInput()
{
    wcin.ignore(INT_MAX, '\n'); //ignore all characters till new line character
    wcin.get();
}

wchar_t BlackBoxGame::GetInput()
{
    return _getch();
}

void BlackBoxGame::ClearScreen()
{
    system("cls");
}

void BlackBoxGame::ShowAuthor()
{
    wcout<<L"Tutaj wyswietlic autora w ascci art\n";
    WaitForInput();
    ClearScreen();
}

void BlackBoxGame::ShowGenerateLevel()
{
    int input = -1;
    ClearScreen();
    while (true)
    {
        wcout << "Choose level to generate: \n"
            << "1. 5x5 Board with 3 atoms\n"
            << "2. 8x8 Board with 5 atoms\n"
            << "3. 10x10 Board with 10 atoms\n";

        wcin >> input;
        if (!wcin)
        {
            wcout << "Incorrect input!\n";
            wcin.clear();
            WaitForInput();
            ClearScreen();
            continue;
        }

        switch (input)
        {
        case 1:
            settings_board_width = 5;
            settings_board_height = 5;
            atom_count = 3;
            return;
        case 2:
            settings_board_width = 8;
            settings_board_height = 8;
            atom_count = 5;
            return;
        case 3:
            settings_board_width = 10;
            settings_board_height = 10;
            atom_count = 8;
            return;
        default:
            wcout << "Incorrect input!\n";
            WaitForInput();
            ClearScreen();
            break;
        }
    }
}

void BlackBoxGame::ShowMainMenu()
{
    int option = -1;
    ClearScreen();
    wcout << L"Welcome to the \"Black Box Game\"\n";

    while (true)
    {
        wcout << L"Choose an option\n\n"
            << L"1. Play/Resume\n"
            <<L"2. Generate Level\n"
            << L"3. Author\n"
            << L"0. Exit\n";

        wcin >> option;
        if (!wcin)
        {
            wcout << L"Incorrect Input!\n";
            wcin.clear();
            WaitForInput();
            ClearScreen();
            continue;
        }

        switch (option)
        {
        case 1:
            ClearScreen();
            return;
        case 2:
            ShowGenerateLevel();
            Reset();
            GenerateBoard(settings_board_width, settings_board_height, atom_count);
            ClearScreen();
            break;
        case 3:
            ShowAuthor();
            break;
        case 0:
            exit(0);

        default:
            wcout << L"Incorrect option!\n";
            WaitForInput();
            ClearScreen();
            break;
        }
    }
}

void BlackBoxGame::GenerateBoard(const int& width,const int& height,
                                 const int& atom_amount)
{
    
    _game.Init(width, height);

    static random_device rd;
    static mt19937 rand(rd());

    int arr_size = width * height;

    //generate numbers from 0 to last index
    int* indexes = new int[arr_size];
    iota(indexes, indexes + arr_size, 0);

    //sort them randomly, we'll get only first atom_amount
    shuffle(indexes, indexes + arr_size, rand);

    for (int x = 0; x < atom_amount; x++)
    {
        //calculate 2d array indexes
        int by = indexes[x] / width;
        int bx = indexes[x] % width;
        _game._board[bx][by] = ATOM;
    }

    delete[] indexes;
}

void BlackBoxGame::PrintBoardSideInteractions(const Directions& direction, const int& coord)
{
    wcout << setw(CELL_WIDTH);
    if (_game._board_side_interactions[((int)direction * _game._board_width) + coord] != 0)
        wcout << _game._board_side_interactions[((int)direction * _game._board_width) + coord];
    else wcout << EMPTY_CELL;
}

void BlackBoxGame::PrintBoardSide(const Directions& direction, const int& coord)
{
    wcout << setw(CELL_WIDTH);
    wcout << (int)_game._board_side[((int)direction * _game._board_width) + coord];
}

void BlackBoxGame::PrintPadding()
{
    for (int x = 0; x < (2 * CELL_WIDTH) +2; x++)
        wcout << L" ";
}

void BlackBoxGame::PrintBorder(const Directions& direction, const int& coord)
{
    Directions cursorSide = ReturnCursorDirection();



    if (direction == Directions::NORTH || direction == Directions::SOUTH)
    {

        if (cursorSide == direction && (cursorX * CELL_WIDTH) + ceil(CELL_WIDTH / 2.0) == coord)
        {
           if (direction == Directions::NORTH)
               wcout << CURSOR_DOWN;
           else if (direction == Directions::SOUTH)
               wcout << CURSOR_UP;
        }
        else 
            wcout << L"─";
    }


    else
    {
        if(cursorSide == direction && cursorY == coord)
        {
            if (direction == Directions::WEST)
                wcout << CURSOR_RIGHT;
            else if (direction == Directions::EAST)
                wcout << CURSOR_LEFT;
            else
                wcout << EMPTY_CELL;
        }
        else wcout << L"│";
    }
}

void BlackBoxGame::DrawBoard()
{
    //draw interactions top side
    PrintPadding();
    wcout << " ";//fix padding on the top and bottom
    for (int x = 0; x < _game._board_width; x++)
        PrintBoardSideInteractions(Directions::NORTH, x);

    //draw top side
    wcout << "\n";
    PrintPadding();
    wcout << " ";
    for (int x = 0; x < _game._board_width; x++)
        PrintBoardSide(Directions::NORTH, x);

    wcout << "\n";
    PrintPadding();
    wcout << L"┌";
    for (int x = 0; x < ((_game._board_width + 1) * CELL_WIDTH) - 1; x++)
        PrintBorder(Directions::NORTH, x);
    wcout << L"┐\n";

    //draw center
    for(int x=0;x<_game._board_height;x++)
    {
        PrintBoardSideInteractions(Directions::WEST, x);
        PrintBoardSide(Directions::WEST, x);

        wcout << setw(CELL_WIDTH);
        PrintBorder(Directions::WEST, x);

        for(int y=0;y<_game._board_width;y++)
        {
            wcout<<setw(CELL_WIDTH);
            if (cursorX == y && cursorY == x)
                wcout << CURSOR;
            else if (_game._atom_checks[x][y] == ATOM_CHECK)
                wcout << ATOM_CHECK;
            else if (_game._atom_checks[x][y] == ATOM_GUESSED)
                wcout << ATOM_GUESSED;
            else if(_game._board[x][y]==ATOM && _showAtoms)
                wcout<<ATOM;            
            else
                wcout<<EMPTY_CELL;
        }
        wcout << setw(CELL_WIDTH);
        PrintBorder(Directions::EAST, x);
        PrintBoardSide(Directions::EAST, x);
        PrintBoardSideInteractions(Directions::EAST, x);

        wcout << "\n";
    }

    PrintPadding();
    wcout << L"└";
    for (int x = 0; x < ((_game._board_width + 1) * CELL_WIDTH) - 1; x++)
        PrintBorder(Directions::SOUTH, x);
    wcout << L"┘";

    wcout << "\n";
    PrintPadding();
    wcout << " ";

    //draw down side
    for (int x = 0; x < _game._board_width; x++)
        PrintBoardSide(Directions::SOUTH, x);

    wcout << "\n";
    PrintPadding();
    wcout << " ";

    for (int x = 0; x < _game._board_width; x++)
        PrintBoardSideInteractions(Directions::SOUTH, x);

    wcout << "\n";
}

void BlackBoxGame::MoveCursor(const Directions& direction)
{
    if (direction == Directions::NORTH)
    {
        if (IsInCursorBound(cursorX, cursorY - 1) && IsInCursorSideBound(cursorX, cursorY - 1))
            cursorY--;
    }
    else if (direction == Directions::SOUTH)
    {
        if (IsInCursorBound(cursorX, cursorY + 1) && IsInCursorSideBound(cursorX, cursorY + 1))
            cursorY++;
    }
    else if (direction == Directions::WEST)
    {
        if (IsInCursorBound(cursorX -1, cursorY) && IsInCursorSideBound(cursorX-1, cursorY))
            cursorX--;
    }
    else if (direction == Directions::EAST)
    {
        if (IsInCursorBound(cursorX + 1, cursorY) && IsInCursorSideBound(cursorX+1, cursorY))
            cursorX++;
    }
}

bool BlackBoxGame::ProcessInput(const wchar_t& input)
{
    //make input case independent
    wchar_t input_lowercase = towlower(input);

    //return true if correct input, otherwise default case returns false
    switch (input_lowercase)
    {
    case L'w':
        MoveCursor(Directions::NORTH);
        return true;
    case L'a':
        MoveCursor(Directions::WEST);
        return true;
    case L's':
        MoveCursor(Directions::SOUTH);
        return true;
    case L'd':
        MoveCursor(Directions::EAST);
        return true;
    case L' ': //space
    {
        //beam is always shot in the opposite direction
        Directions shotDirection = GetOppositeDirection(ReturnCursorDirection());
        if (shotDirection == Directions::NONE)
            return false;
        int coordinate = 0;

        //save previous state to the undo stack
        _undo_stack.push(_game);
        _redo_stack.clear();

        if (shotDirection == Directions::WEST || shotDirection == Directions::EAST)
            coordinate = cursorY;
        else
            coordinate = cursorX;

        ShootBeam(coordinate, shotDirection);
        return true;
    }
    case L'q':
        ShowMainMenu();
        return true;
    case L'u':
        Undo();
        return true;
    case L'r':
        Redo();
        return true;
    case L'o':
        MarkAtom(cursorX, cursorY);
        return true;
    case L'k':
        EndGame();
        Reset();
        GenerateBoard(settings_board_width, settings_board_height, atom_count);
        ShowMainMenu();
        return true;
    case L'h':
    {
        if (helps_used >= MAX_HELPS)
        {
            wcout << "You have used all of your helps\n";
            WaitForInput();
            return true;
        }
        ShowAtoms();
        return true;
    }
    
    default:
        return false;
    }
}

void BlackBoxGame::GameLoop()
{
    GenerateBoard(settings_board_width, settings_board_height, atom_count);
    ShowMainMenu();
    while (true)
    {
        DrawBoard();
        wchar_t input = GetInput();
        ProcessInput(input);
        ClearScreen();
    }
}

void BlackBoxGame::SetDeltas(int& dx, int& dy, const Directions& direction)
{
    switch (direction)
    {
        case BlackBoxGame::Directions::NORTH:
            dx = 0;
            dy = -1;//moving vertically in the array is opposite to the real world
            break;
        case BlackBoxGame::Directions::EAST:
            dx = 1;
            dy = 0;
            break;
        case BlackBoxGame::Directions::SOUTH:
            dx = 0;
            dy = 1;
            break;
        case BlackBoxGame::Directions::WEST:
            dx = -1;
            dy = 0;
            break;
        default:
            break;
    }
}

void BlackBoxGame::ShowAtoms(const int& msDuration)
{
    _showAtoms = true;
    ClearScreen();
    DrawBoard();
    this_thread::sleep_for(chrono::milliseconds(msDuration));
    _showAtoms = false;
    helps_used++;
}

void BlackBoxGame::MarkAtom(const int& xCoord, const int& yCoord)
{
    if (!IsInBound(xCoord, yCoord))
        return;

    if (_game._atom_checks[yCoord][xCoord] != ATOM_CHECK && atom_mark_count < atom_count)
    {
        _game._atom_checks[yCoord][xCoord] = ATOM_CHECK;
        atom_mark_count++;
    }
    else if(_game._atom_checks[yCoord][xCoord] == ATOM_CHECK)
    {
        _game._atom_checks[yCoord][xCoord] = EMPTY_CELL;
        atom_mark_count--;
    }
}

bool BlackBoxGame::CheckDeflection(const int& xCoord, const int& yCoord,
    int& dx, int& dy)
{
    int dir = dx == 0 ? dy : dx;
    int deflectionOccured = false;

    //beam is moving horizontally
    if (dx != 0)
    {
        if (IsInBound(xCoord + dir, yCoord - dir) && CheckAtom(xCoord + dir, yCoord - dir))
        {
            swap(dx,dy);
            deflectionOccured = true;
        }
        if (IsInBound(xCoord + dir, yCoord + dir) && CheckAtom(xCoord + dir, yCoord + dir))
        {
            swap(dx, dy);
            dx = -dx;
            dy = -dy;
            deflectionOccured = true;
        }
    }
    else //vertical movement
    {
        if (IsInBound(xCoord + dir, yCoord + dir) && CheckAtom(xCoord + dir, yCoord + dir))
        {
            swap(dx, dy);
            dx = -dx;
            dy = -dy;
            deflectionOccured = true;
        }
        //south-east, north-west
        if (IsInBound(xCoord - dir, yCoord + dir) && CheckAtom(xCoord - dir, yCoord + dir))
        {
            swap(dx, dy);
            deflectionOccured = true;
        }
    }

    return deflectionOccured;
}

void BlackBoxGame::Undo()
{
    if (_undo_stack.isEmpty())
        return;
    _redo_stack.push(_undo_stack.pop());
    _game = _redo_stack.getTop();
}

void BlackBoxGame::Redo()
{
    if (_redo_stack.isEmpty())
        return;

    _undo_stack.push(_redo_stack.pop());
    _game = _undo_stack.getTop();
}

bool BlackBoxGame::CheckAtom(const int& xCoord, const int& yCoord)
{
    //if cooridinates are out of bounds
    if (!IsInBound(xCoord, yCoord))
        return false;
    return _game._board[yCoord][xCoord] == ATOM;
}

bool BlackBoxGame::IsInBound(const int& xCoord, const int& yCoord)
{
    return xCoord >= 0 && xCoord < _game._board_width
           && yCoord >= 0 && yCoord < _game._board_height;
}

bool BlackBoxGame::IsInCursorBound(const int& xCoord, const int& yCoord)
{ 
    return xCoord >=-1 && xCoord <= _game._board_width
           && yCoord >= -1 && yCoord <= _game._board_height;
}

bool BlackBoxGame::IsInCursorSideBound(const int& xCoord, const int& yCoord)
{
    if (xCoord == -1 || xCoord == _game._board_width)
    {
        if (yCoord >= 0 && yCoord < _game._board_height)
            return true;
        return false;
    }
    else if (yCoord == -1 || yCoord == _game._board_height)
    {
        if (xCoord >= 0 && xCoord < _game._board_width)
            return true;
        return false;
    }
    else //cursor is on the board
        return true;
}

BlackBoxGame::Directions BlackBoxGame::ReturnCursorDirection()
{
    if (cursorX == -1)
        return Directions::WEST;
    if (cursorX == _game._board_width)
        return Directions::EAST;
    if (cursorY == -1)
        return Directions::NORTH;
    if (cursorY == _game._board_height)
        return Directions::SOUTH;

    return Directions::NONE;
}

BlackBoxGame::Directions BlackBoxGame::GetOppositeDirection(const Directions& direction)
{
    if (direction == Directions::NORTH)
        return Directions::SOUTH;
    if (direction == Directions::SOUTH)
        return Directions::NORTH;
    if (direction == Directions::WEST)
        return Directions::EAST;
    if (direction == Directions::EAST)
        return Directions::WEST;
    
    //we do not support diagonal directions, no need to
    return Directions::NONE;
}

bool BlackBoxGame::CheckInstantReflection(const int& xCoord, const int& yCoord, const Directions& beam_direction)
{
    if (CheckAtom(xCoord, yCoord))
        return false;

    if (beam_direction == Directions::WEST || beam_direction == Directions::EAST)
        if (CheckAtom(xCoord, yCoord + 1) || CheckAtom(xCoord, yCoord - 1))
            return true;

    if (beam_direction == Directions::NORTH || beam_direction == Directions::SOUTH)
        if (CheckAtom(xCoord+1, yCoord) || CheckAtom(xCoord-1, yCoord))
            return true;

    return false;
}

BlackBoxGame::Directions BlackBoxGame::ReturnBeamDirection(const int& dx, const int& dy)
{
    if (dx == -1)
        return Directions::WEST;
    else if (dx == 1)
        return Directions::EAST;
    else if (dy == -1)
        return Directions::NORTH;
    else if (dy == 1)
        return Directions::SOUTH;

    return Directions::NONE;
}

void BlackBoxGame::ShootBeam(const int& coordinate, const Directions& direction)
{
    if (direction == Directions::NONE)
        return;

    _game.shot_num++;

    int dx = 0, dy = 0;//this will be used to indicate in which direction we should
                       //move in our array, either x or y direction
    int xCoord = 0, yCoord = 0;

    //set proper coordinate to shoot
    if (direction == Directions::NORTH || direction == Directions::SOUTH)
        xCoord = coordinate;
    else
        yCoord = coordinate;

    Directions startDirection = GetOppositeDirection(direction);
    _game._board_side[((int)startDirection * _game._board_width) + coordinate] = _game.shot_num;

    //get proper x or y coordinate if direction is on south or east (ends of array)
    if (startDirection == Directions::SOUTH)
        yCoord = _game._board_height - 1;
    else if (startDirection == Directions::EAST)
        xCoord = _game._board_width - 1;

    SetDeltas(dx, dy, direction);

    if (CheckInstantReflection(xCoord, yCoord, direction))
    {
        _game._board_side_interactions[((int)startDirection * _game._board_width) + coordinate] = REFLECTION;
        return;
    }

    int anti_loop = 0;
    while(IsInBound(xCoord, yCoord))
    {
        //our beam propably looped
        if (anti_loop == LOOP_MAX_ITERATIONS)
        {
            wcout << "Anti-loop";
            return;
        }

        if (CheckAtom(xCoord, yCoord))
        {
            _game._board_side_interactions[((int)startDirection * _game._board_width) + coordinate] = ATOM_HIT;
            return;
        }

        CheckDeflection(xCoord, yCoord, dx, dy);
        anti_loop++;

        xCoord += dx;
        yCoord += dy;
    }

    Directions BeamDirection = ReturnBeamDirection(dx, dy);
    int sideCoord = 0;
    if (BeamDirection == Directions::NORTH || BeamDirection == Directions::SOUTH)
        sideCoord = xCoord;
    else
        sideCoord = yCoord;

    if(sideCoord==coordinate && startDirection == BeamDirection)//reflection occured
        _game._board_side_interactions[((int)BeamDirection * _game._board_width) + sideCoord] = REFLECTION;

    _game._board_side[((int)BeamDirection * _game._board_width) + sideCoord] = _game.shot_num;
}

void BlackBoxGame::EndGame()
{
    ClearScreen();
    _showAtoms = true;

    int atomsGuessed = 0;
    for (int x = 0; x < _game._board_height; x++)
    {
        for (int y = 0; y < _game._board_width; y++)
        {
            if (_game._board[x][y] == ATOM && _game._atom_checks[x][y] == ATOM_CHECK)
            {
                atomsGuessed++;
                _game._atom_checks[x][y] = ATOM_GUESSED;
            }
        }
    }

    DrawBoard();
    _showAtoms = false;
    wcout << "You have guessed " << atomsGuessed << "/" << atom_count << " Atoms!\n";
    WaitForInput();
}

void BlackBoxGame::Reset()
{
    cursorX = 0;
    cursorY = 0;
    _undo_stack.clear();
    _redo_stack.clear();
    _showAtoms = false;
    helps_used = 0;
    _game.shot_num = 0;
    atom_mark_count = 0;
}

BlackBoxGame::BlackBoxGame(){}

void BlackBoxGame::Start()
{
    GameLoop();
}