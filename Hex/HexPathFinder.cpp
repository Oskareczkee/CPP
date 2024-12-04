#include "HexPathFinder.h"

HexPathFinder::~HexPathFinder()
{
    //do not delete _board, this is reference to the original board
    delete_v_arr();
    delete_v_beg();
    delete_v_end();
}

bool HexPathFinder::dfs_visit(const int& x, const int& y, bool blue)
{
    int xCoord = 0, yCoord = 0;

    //for each edge in vertex[x][y]
    for (auto& vec : AxialVectors::Vectors)
    {
        xCoord = x + vec.p;
        yCoord = y + vec.q;
        if (is_proper_coordinate(xCoord, yCoord) && !v_arr[xCoord][yCoord])
        {
            //if vertex does not conatin proper pawn type, do not check it
            if (blue && _board[xCoord][yCoord].pawn_type != PawnType::BLUE)continue;
            if (!blue && _board[xCoord][yCoord].pawn_type != PawnType::RED)continue;
            v_arr[xCoord][yCoord] = true; //mark as visited

            if (blue && xCoord == _size - 1) //path from 1 end to another has been found for blue
                return true;
            if (!blue && yCoord == _size - 1) //path has been found for red
                return true;

            //for proper recursion end
            if (dfs_visit(xCoord, yCoord, blue))
                return true;
        }
    }

    return false;
}

void HexPathFinder::dfs_visit_all(const int& x, const int& y,bool blue)
{
    int xCoord = 0, yCoord = 0;

    //for each edge in vertex[x][y]
    for (auto& vec : AxialVectors::Vectors)
    {
        xCoord = x + vec.p;
        yCoord = y + vec.q;
        if (is_proper_coordinate(xCoord, yCoord) && !v_arr[xCoord][yCoord])
        {
            //if vertex does not conatin proper pawn type, do not check it
            if (blue && _board[xCoord][yCoord].pawn_type != PawnType::BLUE)continue;
            if (!blue && _board[xCoord][yCoord].pawn_type != PawnType::RED)continue;
            v_arr[xCoord][yCoord] = true; //mark as visited

            if (blue && xCoord == _size - 1) { //path from 1 end to another has been found for blue
                v_end[yCoord] = true;
                continue;
            }
            if (!blue && yCoord == _size - 1) { //path has been found for red
                v_end[xCoord] = true;
                continue;
            }

            //for proper recursion end
            dfs_visit_all(xCoord, yCoord, blue);
        }
    }
}

bool HexPathFinder::dfs(const int& x, const int& y, bool blue)
{
    int xCoord = 0, yCoord = 0;

    //for each edge in vertex[x][y]
    for (auto& vec : AxialVectors::Vectors)
    {
        xCoord = x + vec.p;
        yCoord = y + vec.q;
        if (is_proper_coordinate(xCoord, yCoord) && !v_arr[xCoord][yCoord])
        {
            //if vertex does not conatin proper pawn type, do not check it
            if (blue && _board[xCoord][yCoord].pawn_type != PawnType::BLUE)continue;
            if (!blue && _board[xCoord][yCoord].pawn_type != PawnType::RED)continue;


            v_arr[xCoord][yCoord] = true; //mark as visited

            if (blue && xCoord == _size - 1)     return true;
            if (!blue && yCoord == _size - 1)    return true;

            if (dfs_visit(xCoord, yCoord, blue))
                return true;
        }
    }

    return false;
}

void HexPathFinder::dfs_all(const int& x, const int& y, bool blue)
{
    int xCoord = 0, yCoord = 0;

    //for each edge in vertex[x][y]
    for (auto& vec : AxialVectors::Vectors)
    {
        xCoord = x + vec.p;
        yCoord = y + vec.q;
        if (is_proper_coordinate(xCoord, yCoord) && !v_arr[xCoord][yCoord])
        {
            //if vertex does not conatin proper pawn type, do not check it
            if (blue && _board[xCoord][yCoord].pawn_type != PawnType::BLUE)continue;
            if (!blue && _board[xCoord][yCoord].pawn_type != PawnType::RED)continue;


            v_arr[xCoord][yCoord] = true; //mark as visited
            dfs_visit_all(xCoord, yCoord, blue);
        }
    }
}

bool HexPathFinder::is_proper_coordinate(const int& x, const int& y)
{
    return x >= 0 && x < _size &&
        y >= 0 && y < _size;
}

bool HexPathFinder::is_distinct(const int& x, const int& y, PawnType color)
{
    int xCoord = 0, yCoord = 0;
    for(auto& vec : AxialVectors::Vectors)
    {
        xCoord = x + vec.p;
        yCoord = y + vec.q;

        if (xCoord == 0 || yCoord == 0 || !is_proper_coordinate(xCoord,yCoord))//if is border tile or wrong coordinate, skip it
            continue;

        if (v_arr[xCoord][yCoord] && _board[xCoord][yCoord].pawn_type==color)//node has neighbors that were visited
            return false;
    }

    return true;
}

bool HexPathFinder::is_connected(const int& x, const int& y, PawnType color)
{
    int xCoord = 0, yCoord = 0;
    for (auto& vec : AxialVectors::Vectors)
    {
        xCoord = x + vec.p;
        yCoord = y + vec.q;

        if (xCoord == 0 && color == PawnType::BLUE)
            continue;
        if (yCoord == 0 && color == PawnType::RED)
            continue;
        if (!is_proper_coordinate(xCoord, yCoord))//if is border tile or wrong coordinate, skip it
            continue;

        if (_board[xCoord][yCoord].pawn_type == color)//node has neighbors that were visited
            return true;
    }

    return false;
}

int HexPathFinder::get_connection_count(const int& x, const int& y, PawnType color)
{
    int xCoord = 0, yCoord = 0;
    int out = 0;
    for (auto& vec : AxialVectors::Vectors)
    {
        xCoord = x + vec.p;
        yCoord = y + vec.q;
        if (!is_proper_coordinate(xCoord, yCoord))//if is border tile or wrong coordinate, skip it
            continue;

        if (_board[xCoord][yCoord].pawn_type == color)//node has neighbors that were visited
            out++;
    }

    return out;
}

bool HexPathFinder::v_arr_has_bridge(PawnType color)
{
    //for all tiles except border tiles
    for (int x = 1; x < _size - 1; x++)
    {
        for (int y = 1; y < _size - 1; y++) {
            if (v_arr[x][y] && get_connection_count(x, y, color) == 2)
                return true;
        }
    }

    return false;
}

bool** HexPathFinder::copy_v_arr(bool** copy)
{
    copy = new bool* [_size];
    for (int x = 0; x < _size; x++) {
        copy[x] = new bool[_size];
        memcpy(copy[x], v_arr[x], sizeof(bool) * _size);
    }

    return copy;
}

bool HexPathFinder::v_arr_equal(bool** v_arr_1, bool** v_arr_2)
{
    if (v_arr_1 == nullptr || v_arr_2 == nullptr) return false;

    for (int x = 1; x < _size-1; x++) {
        for (int y = 1; y < _size-1; y++) {
            if (v_arr_1[x][y] != v_arr_2[x][y])
                return false;
        }
    }

    return true;
}

void HexPathFinder::delete_v_arr()
{
    if (v_arr == nullptr)   return;

    for (int x = 0; x < _size; x++)
        delete[] v_arr[x];

    delete[] v_arr;
    v_arr = nullptr;
}

void HexPathFinder::delete_v_beg()
{
    if (v_beg == nullptr)  return;
    delete[] v_beg;
    v_beg = nullptr;
}

void HexPathFinder::delete_v_end()
{
    if (v_end == nullptr)  return;
    delete[] v_end;
    v_end = nullptr;
}

void HexPathFinder::init_v_arr()
{
    if (v_arr != nullptr)
        delete_v_arr();
    v_arr = new bool* [_size];

    for (int x = 0; x < _size; x++) {
        v_arr[x] = new bool[_size];
        memset(v_arr[x], false, sizeof(bool) * _size);
    }
}

void HexPathFinder::init_v_beg()
{
    if (v_beg != nullptr)
        delete_v_beg();
    v_beg = new bool[_size];
    memset(v_beg, false, sizeof(bool) * _size);
}

void HexPathFinder::init_v_end()
{
    if (v_end != nullptr)
        delete_v_end();
    v_end = new bool[_size];
    memset(v_end, false, sizeof(bool) * _size);
}


bool HexPathFinder::path_exists(bool blue)
{
    //edge case
    if (_size == 1 && !blue && _board[0][0].pawn_type == PawnType::RED)
        return true;

    init_v_arr();

    //blue pawn line starts from [0,x] coordinates and ends at [0,_size-1] cooridnate
    for (int x = 0; x < _size; x++)
    {
        if (blue && _board[0][x].pawn_type == PawnType::BLUE) //if pawn of proper color is on the tile
        {
            v_arr[0][x] = true;
            //start pathfinding
            if (dfs(0, x, blue))
                return true;
        }
        else if (!blue && _board[x][0].pawn_type == PawnType::RED)
        {
            v_arr[x][0] = true;
            //start pathfinding
            if (dfs(x, 0, blue))
                return true;
        }
    }

    return false;
}

int HexPathFinder::path_count(bool blue)
{
    //edge case
    if (_size == 1 && !blue && _board[0][0].pawn_type == PawnType::RED) {
        _path_count = 1;
        return _path_count;
    }

    init_v_arr();
    init_v_beg();
    init_v_end();

    //blue pawn line starts from [0,x] coordinates and ends at [0,_size-1] cooridnate
    for (int x = 0; x < _size; x++)
    {
        if (blue && _board[0][x].pawn_type == PawnType::BLUE) //if pawn of proper color is on the tile
        {
            v_beg[x] = true;
            v_arr[0][x] = true;
            //start pathfinding
            dfs_all(0, x, blue);
        }
        else if (!blue && _board[x][0].pawn_type == PawnType::RED)
        {
            v_beg[x] = true;
            v_arr[x][0] = true;
            //start pathfinding
            dfs_all(x, 0, blue);
        }

    }

    int beg_visited = 0;
    int end_visited = 0;
    //count end and beg visited, but count only begginings that have path
    for (int x = 0; x < _size; x++) {
        HexPathFinder hpf(_board, _size);
        hpf.init_v_arr();

        if (blue) {
            if (v_beg[x] && hpf.dfs(0,x,true)) beg_visited++;
        }
        else {
            if (v_beg[x] && hpf.dfs(x, 0, false)) beg_visited++;
        }
        if (v_end[x]) end_visited++;
    }
    //std::cout << beg_visited << end_visited << "\n";
    _path_count = (beg_visited < end_visited ? beg_visited : end_visited); //path_count is minimum between visited beginning nodes and end nodes
                                                                         //if there is 1 beg_node and 3 end_nodes, that means that from this one node
                                                                         //you can travel to 3 end nodes
    return _path_count;
}
