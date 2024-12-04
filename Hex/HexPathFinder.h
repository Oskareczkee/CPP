#pragma once
#include "HexTile.h"
#include "HexCoord.h"
#include <iostream>
#include <cstring> //memset

class HexPathFinder {
private:
	HexTile** _board = nullptr;
	int _size = 0; //board size
	bool** v_arr = nullptr; //visited array
	bool* v_beg = nullptr; //visited beginnings tiles, each index represents 1 tile
	bool* v_end = nullptr; //visited end tiles, each index represents 1 tile
	int _path_count = 0;//variable to store class path count state
	bool dfs_all_path_exist = false;

	bool dfs_visit(const int& x, const int& y,bool blue = true); //visits node, returns true when path has been found
	void dfs_visit_all(const int& x, const int& y,bool blue = true); //visits all possible paths and adds them to the path count

	bool dfs(const int& x, const int& y, bool blue = true); //dfs algorithm searching for path, returns true when first path has been found
	void dfs_all(const int& x, const int& y, bool blue = true); //dfs algorithm searching for all paths, adds them to the path_count

	bool is_proper_coordinate(const int& x, const int& y);
	bool is_distinct(const int& x, const int& y, PawnType color);
	bool is_connected(const int& x, const int& y, PawnType color);
	int get_connection_count(const int& x, const int& y, PawnType color);
	bool v_arr_has_bridge(PawnType color);
	bool** copy_v_arr(bool** copy);
	bool v_arr_equal(bool** v_arr_1, bool** v_arr_2);

	void delete_v_arr();
	void delete_v_beg();
	void delete_v_end();

	void init_v_arr();
	void init_v_beg();
	void init_v_end();

public:

	HexPathFinder(HexTile** board, const int& size) : _board(board), _size(size){}
	~HexPathFinder(); //destructor, memory clear
	bool path_exists(bool blue = true);
	int path_count(bool blue = true);
};