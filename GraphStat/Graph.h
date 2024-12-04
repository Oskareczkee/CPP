#pragma once
#include "Vertex.h"
#include "Matrix.h"
#include "Queue.h"

/*TODO (vertices_eccentrity) IMPLEMENT MY OWN QUEUE -> use single linked list with head and tail for proper front and back operations*/
/*TODO (degree_sequence) IMPLEMENT MY OWN SORTING*/

class Graph {
private:
	Vertex* _vertices = nullptr;
	int _degree = 0;
	int _edges = 0;
	int iter = 0;

	void create_vertex_array();
	void delete_vertex_array();
	template<class T, class Comp = std::greater<T>>
	void insertion_sort(T* arr, const int& size, Comp compare_function = Comp()); /*easiest out of easiest*/

	/*sadly, input indexes are counted from 1, and array indexes are counted from 0
	  These functions were created in order to prevent indexing errors*/
	int arr_idx(const int& in_idx) { return in_idx - 1; }
	int in_idx(const int& arr_idx) { return arr_idx + 1; }

	bool color_exists(int* colored_vertices, int* neighbors, const int& neighbor_count, const int& color);/*checks if given color exists within neighbors, helper for color finding functions*/
	int get_next_color(int* colored_vertices, int* neighbors, const int& neighbor_count);/*gets next unused color, can be improved by using set, helper for color finding functions*/
	int get_saturation(int* colored_vertices, const int& vertex_id);
	void subgraphs_count_dfs(bool* visited_vertices, const int& starting_vertex_id, const int& actual_vertex_id, int depth, int& count);

	/*Vertex state enum for BFS algorithm*/
	enum class VertexState {
		UNVISITED = 0,
		CHECKED = 1,
		VISITED = 2
	};

public:
	//friend all graph specific classes
	friend class GraphLRPA;

	Graph(){}
	Graph(const int& degree): _degree(degree), _vertices(new Vertex[degree]) {}
	~Graph();

	Matrix<int> get_adjacency_matrix();

	int get_degree() { return _degree; }
	int get_edges() { return _edges; }
	void set_degree(const int& degree);
	void add_vertex(const Vertex& v);

	/// <summary>
	/// Returns sorted degree sequence of each vertex, size of the array is degree of graph
	/// </summary>
	std::unique_ptr<int[]> degree_sequence();
	std::unique_ptr<int[]> vertices_eccentrity();
	std::unique_ptr<int[]> greedy_coloring();
	std::unique_ptr<int[]> lf_coloring();
	std::unique_ptr<int[]> slf_coloring();

	int components_number();
	bool is_bipartite();
	int vertex_eccentrity(const int& vertex_id);
	bool is_planar();
	int number_of_c4_subgraphs();
	int number_of_cycles(const int& cycle_length);
	int complement_edges();


	void print_vertices() {
		for (int x = 0; x < _degree; x++)
		{
			std::cout << _vertices[x]._neighbor_count << " ";
			for (int y = 0; y < _vertices[x]._neighbor_count; y++)
				std::cout << _vertices[x]._neighbors[y] << " ";
			std::cout << "\n";
		}
	}
};

template<class T, class Comp>
inline void Graph::insertion_sort(T* arr, const int& size, Comp compare_function)
{
	for (int i = 1; i < size; i++)
	{
		T key = arr[i];
		int j = i - 1;

		while (j >= 0 && compare_function(key, arr[j]))
		{
			arr[j + 1] = arr[j];
			j--;
		}

		arr[j + 1] = key;
	}
}
