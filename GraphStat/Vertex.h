#pragma once
#include <iostream>

class Vertex {
private:
	int* _neighbors = nullptr;	 //ids of neighbors
	int _neighbor_count = 0;	 //number of neighbors
	int iter = 0;				 //actual neighbor added

	void copy_neighbors(int* neighbors);
	void create_neighbors();
	void delete_neighbors();
public:
	friend class Graph;
	friend class GraphLRPA;

	Vertex(): _neighbor_count(0), _neighbors(nullptr) {}
	Vertex(const int& neighbor_count, int* neighbors);
	~Vertex();

	Vertex& operator=(const Vertex& other); /*copy operator for safe copying*/

	int get_neighbor_count() { return _neighbor_count; }
	void set_neighbor_count(const int& count);
	void add(const int& neighbor_id);

	/// <summary>
	/// Safely loads vertex from input stream
	/// <returns></returns>
	friend std::istream& operator>>(std::istream& os, Vertex& v) {
		if (!os) return os;
		
		int neighbor_count = 0, neighbor_id=0;
		os >> neighbor_count;
		v.set_neighbor_count(neighbor_count);

		for (int i = 0; i < neighbor_count; i++) {
			os >> neighbor_id;
			v.add(neighbor_id);
		}

		return os;
	}
};