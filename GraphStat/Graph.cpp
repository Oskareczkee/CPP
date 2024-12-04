#include "Graph.h"

void Graph::create_vertex_array()
{
	if (_vertices != nullptr) return;

	iter = 0;
	_vertices = new Vertex[_degree];
}

void Graph::delete_vertex_array()
{
	if (_vertices == nullptr) return;
	delete[] _vertices;
	_vertices = nullptr;
}

bool Graph::color_exists(int* colored_vertices, int* neighbors, const int& neighbor_count, const int& color)
{
	for (int x = 0; x < neighbor_count; x++) {
		int neighbor_idx = arr_idx(neighbors[x]);
		if (colored_vertices[neighbor_idx] == color)
			return true;
	}

	return false;
}

int Graph::get_next_color(int* colored_vertices, int* neighbors, const int& neighbor_count)
{
	int color = 1;
	while (color_exists(colored_vertices, neighbors, neighbor_count, color))
		color++;
	return color;
}

int Graph::get_saturation(int* colored_vertices, const int& vertex_id)
{
	int vertex_arr_idx = arr_idx(vertex_id);
	int* neighbors = _vertices[vertex_arr_idx]._neighbors;
	int neighbor_count = _vertices[vertex_arr_idx]._neighbor_count;

	auto neighbor_colors = std::make_unique<int[]>(neighbor_count);

	for (int x = 0; x < neighbor_count; x++) {
		int neighbor_idx = arr_idx(neighbors[x]);
		neighbor_colors[x] = colored_vertices[neighbor_idx];
	}

	insertion_sort(neighbor_colors.get(),neighbor_count);

	/*get number of unique colors assigned, non colored vertices (0) are not counted and neglected*/
	int unique = 0;
	for (int x = 0; x < neighbor_count; x++)
		if (neighbor_colors[x] != 0 && (x == 0 || neighbor_colors[x] != neighbor_colors[x - 1]))
			unique++;

	return unique;
}

void Graph::subgraphs_count_dfs(bool* visited_vertices, const int& starting_vertex_id, const int& actual_vertex_id, int depth, int& count)
{

	visited_vertices[actual_vertex_id] = true;
	const int* neighbors = _vertices[actual_vertex_id]._neighbors;
	int neighbor_count = _vertices[actual_vertex_id]._neighbor_count;

	if (depth == 0) {
		visited_vertices[actual_vertex_id] = false;
		/*check if actual vertex has a neighbor that is starting vertex, thus forming a cycle*/
		for (int x = 0; x < neighbor_count; x++) {
			if (arr_idx(neighbors[x]) == starting_vertex_id) {
				count++;
				return;
			}
		}

		return;
	}

	for (int x = 0; x < neighbor_count; x++) {
		int neighbor_idx = arr_idx(neighbors[x]);
		if (visited_vertices[neighbor_idx])
			continue;
		subgraphs_count_dfs(visited_vertices, starting_vertex_id, neighbor_idx, depth-1, count);
	}

	visited_vertices[actual_vertex_id] = false;
}

Graph::~Graph()
{
	delete_vertex_array();
}

Matrix<int> Graph::get_adjacency_matrix()
{
	Matrix<int> out(_degree, _degree);
	out.fill(0);

	for (int x = 0; x < _degree; x++) {
		int neighbor_count = _vertices[x]._neighbor_count;
		int* neighbors = _vertices[x]._neighbors;
		for (int y = 0; y < neighbor_count; y++) {
			int neighbor_idx = arr_idx(neighbors[y]);
			out[x][neighbor_idx] = 1;
		}
	}

	return out;
}

void Graph::set_degree(const int& degree)
{
	delete_vertex_array();
	_degree = degree;
	create_vertex_array();
}

void Graph::add_vertex(const Vertex& v)
{
	if (iter >= _degree) return;

	_edges += v._neighbor_count;
	_vertices[iter++] = v;
}

std::unique_ptr<int[]> Graph::degree_sequence()
{
	auto out = std::make_unique<int[]>(_degree);
	for (int x = 0; x < _degree; x++)
		out[x] = _vertices[x].get_neighbor_count();

	insertion_sort(out.get(), _degree, [](int& v1, int& v2) {return v1 > v2; });
	return out;
}

std::unique_ptr<int[]> Graph::vertices_eccentrity()
{
	auto out = std::make_unique<int[]>(_degree);
	for (int x = 0; x < _degree; x++)
		out[x] = vertex_eccentrity(in_idx(x));

	return out;
}

std::unique_ptr<int[]> Graph::greedy_coloring()
{
	auto colored_vertices = std::make_unique<int[]>(_degree);
	for (int x = 0; x < _degree; x++) colored_vertices[x] = 0;//set color of all vertices to 0

	for (int x = 0; x < _degree; x++) {
		int* neighbors = _vertices[x]._neighbors;
		int neighbor_count = _vertices[x]._neighbor_count;
		int color = get_next_color(colored_vertices.get(), neighbors, neighbor_count);
		colored_vertices[x] = color;
	}

	return colored_vertices;
}

std::unique_ptr<int[]> Graph::lf_coloring()
{
	auto colored_vertices = std::make_unique<int[]>(_degree);
	auto sorted_vertices = std::make_unique<std::pair<int, int>[]>(_degree); /*pair holds: first -> vertex_id, second -> degree(neighbor_count), sort by neighbor_count descending*/

	/*add all pairs to sorted_vertices and set all vertictes to uncolored (0)*/
	for (int x = 0; x < _degree; x++) {
		sorted_vertices[x] = std::make_pair(x, _vertices[x]._neighbor_count);
		colored_vertices[x] = 0;
	}

	/*sort vertices by their degree, if they have the same degree, choose lower index*/
	insertion_sort(sorted_vertices.get(),_degree,
		[](std::pair<int, int>& p1, std::pair<int, int>& p2)
		{
			if (p1.second == p2.second)
				return p1.first < p2.first;
			return p1.second > p2.second;
		});

	for (int x = 0; x < _degree; x++) {
		int vertex_idx = sorted_vertices.get()[x].first; /*no need for arr_idx, as vertices in sorted_vertices are added by loop, counting from 0*/
		int* neighbors = _vertices[vertex_idx]._neighbors;
		int neighbor_count = _vertices[vertex_idx]._neighbor_count;
		int color = get_next_color(colored_vertices.get(), neighbors, neighbor_count);
		colored_vertices[vertex_idx] = color;
	}

	return colored_vertices;
}

std::unique_ptr<int[]> Graph::slf_coloring()
{
	auto colored_vertices = std::make_unique<int[]>(_degree);
	auto saturation_degrees = std::make_unique<int[]>(_degree);
	int iter = 0;

	/*set color and saturation degree to 0 for all vertices*/
	for (int x = 0; x < _degree; x++) {
		colored_vertices[x] = 0;
		saturation_degrees[x] = 0;
	}

	/*helper, returns index with maximum saturation, maximum degree and lowest id*/
	auto max_saturation = [&]() {
		int max_saturation = -1, max_degree = -1, min_id = _degree + 1;
		for (int x = 0; x < _degree; x++) {
			if (colored_vertices[x] != 0) /*skip colored vertices*/
				continue;

			int degree = _vertices[x].get_neighbor_count();
			if ((saturation_degrees[x] > max_saturation) ||
				(saturation_degrees[x] == max_saturation && degree > max_degree) ||
				(saturation_degrees[x] == max_saturation && degree == max_degree && x < min_id))
			{
				max_saturation = saturation_degrees[x];
				max_degree = degree;
				min_id = x;
			}
		}

		return min_id;
	};

	/*while not all vertices are colored*/
	while (iter++ < _degree) {
		int v_max = max_saturation();
		int* neighbors = _vertices[v_max]._neighbors;
		int neighbor_count = _vertices[v_max]._neighbor_count;
		colored_vertices[v_max] = get_next_color(colored_vertices.get(), neighbors, neighbor_count);

		for (int x = 0; x < neighbor_count; x++) {
			int neighbor_id = arr_idx(neighbors[x]);
			if (colored_vertices[neighbor_id] != 0) /*skip all colored vertices*/
				continue;

			saturation_degrees[neighbor_id] = get_saturation(colored_vertices.get(), in_idx(neighbor_id));
		}

	}

	return colored_vertices;
}

int Graph::vertex_eccentrity(const int& vertex_id)
{
	/*Variables used in dijkstra-BFS algorithm*/

	constexpr int weight = 1; /*graph is unweighted, so this is default weight*/
	constexpr int infinity = INT32_MAX; /*INFINITY is reserved by corecrt_math, so i use smallcase infinity instead*/

	auto distances = std::make_unique<int[]>(_degree);
	Queue<int> queue;
	int max_distance = 0; /*eccentrity is maximum distance from vertex to the other reachable vertex in graph*/

	for (int x = 0; x < _degree; x++) distances[x] = infinity; /*set distances to infinity*/

	distances[arr_idx(vertex_id)] = 0;
	queue.push(vertex_id);

	while (!queue.empty()) {
		int id = queue.front();
		queue.pop();

		for (int x = 0; x < _vertices[arr_idx(id)]._neighbor_count; x++) {
			int neighbor_id = _vertices[arr_idx(id)]._neighbors[x];
			if (distances[arr_idx(neighbor_id)] == infinity) { /*vertex has not been visited yer*/
				distances[arr_idx(neighbor_id)] = distances[arr_idx(id)] + weight;
				queue.push(neighbor_id);
				if (distances[arr_idx(neighbor_id)] > max_distance)
					max_distance = distances[arr_idx(neighbor_id)];
			}
		}
	}

	return max_distance;
}

bool Graph::is_planar()
{
	if (_degree < 2) return true;
	else if ((3 * _degree - 6) < _edges)
		return false;
	else return true;
}

int Graph::number_of_c4_subgraphs()
{
	int count = 0;
	auto adjacency_matrix = get_adjacency_matrix();
	Matrix<int> M2 = adjacency_matrix * adjacency_matrix; /*to improve multiplication time, sparse matrix can be used*/

	for (int x = 0; x < _degree; x++)
		for (int y = x + 1; y < _degree; y++)
			if (M2[x][y] >= 2)
				count += ((M2[x][y] * (M2[x][y] - 1)) / 2);


	return count/2;
	//return number_of_cycles(4);
}

int Graph::number_of_cycles(const int& cycle_length)
{
	/*prepare for dfs algorithm*/
	auto visited_vertices = std::make_unique<bool[]>(_degree);
	int count = 0;

	std::fill(visited_vertices.get(), visited_vertices.get() + _degree, false); /*mark all vertices as unvisited*/

	for (int x = 0; x < _degree - (cycle_length - 1); x++) {
		subgraphs_count_dfs(visited_vertices.get(), x, x, cycle_length - 1, count);
		visited_vertices[x] = true;
	}

	return count / 2; /*dividing by 2 removes duplicates*/
}

int Graph::complement_edges()
{
	int max_edges = (_degree * (_degree - 1)) / 2; /*n choose 2 formula*/
	return max_edges - (_edges / 2); /*divide by 2, since each edge is counted twice*/
}

int Graph::components_number()
{

	/*Variables used in BFS algorithm*/
	auto visited_vertices = std::make_unique<VertexState[]>(_degree);
	auto vertices_stack = std::make_unique<int[]>(_degree); /*use stack instead of queue stores ids of vertices*/
	int stack_iter = 0; /*actual position on stack*/
	int component_count = 0;
	int unvisited_vertex = -1;

	/*set all vertices to unvisisted, do not use memset, as it initializes values byte by byte, and does not work for enum types properly*/
	for (int x = 0; x < _degree; x++) visited_vertices[x] = VertexState::UNVISITED;

	/*helper function to get first unvisited vertex, returns -1 if there are no unvisited vertices*/
	auto get_unvisited = [&]() {
		for (int x = 0; x < _degree; x++)
			if (visited_vertices[x] == VertexState::UNVISITED) return in_idx(x);
		return -1;
	};

	while ((unvisited_vertex = get_unvisited()) != -1) {
		vertices_stack[stack_iter++] = unvisited_vertex;

		while (stack_iter != 0) {
			int id = vertices_stack[--stack_iter];
			for (int x = 0; x < _vertices[arr_idx(id)]._neighbor_count; x++) {
				int neighbor_id = _vertices[arr_idx(id)]._neighbors[x];
				if (visited_vertices[arr_idx(neighbor_id)] != VertexState::UNVISITED)
					continue;
				visited_vertices[arr_idx(neighbor_id)] = VertexState::CHECKED; /*vertex has been checked and added to stack to visit*/
				vertices_stack[stack_iter++] = neighbor_id;
			}
			visited_vertices[arr_idx(id)] = VertexState::VISITED;
		}

		component_count++;
	}

	return component_count;
}

bool Graph::is_bipartite()
{
	/*Vertex state enum for BFS algorithm*/
	enum class VertexColor {
		UNVISITED = 0,
		RED = 1,
		BLUE = 2
	};

	/*Variables used in BFS algorithm*/
	auto visited_vertices = std::make_unique<VertexColor[]>(_degree);
	auto vertices_stack = std::make_unique<int[]>(_degree); /*use stack instead of queue stores ids of vertices*/
	VertexColor actual_color;
	VertexColor opposite_color;
	int stack_iter = 0; /*actual position on stack*/
	int unvisited_vertex = -1;

	/*set all vertices to unvisisted, do not use memset, as it initializes values byte by byte, and does not work for enum types properly*/
	for (int x = 0; x < _degree; x++) visited_vertices[x] = VertexColor::UNVISITED;

	/*helper function to get first unvisited vertex, returns -1 if there are no unvisited vertices*/
	auto get_unvisited = [&]() {
		for (int x = 0; x < _degree; x++)
			if (visited_vertices[x] == VertexColor::UNVISITED) return in_idx(x);
		return -1;
	};

	while ((unvisited_vertex = get_unvisited()) != -1) {
		vertices_stack[stack_iter++] = unvisited_vertex;
		visited_vertices[arr_idx(unvisited_vertex)] = VertexColor::RED;


		while (stack_iter != 0) {
			int id = vertices_stack[--stack_iter];
			actual_color = visited_vertices[arr_idx(id)];
			opposite_color = (actual_color == VertexColor::RED ? VertexColor::BLUE : VertexColor::RED);

			for (int x = 0; x < _vertices[arr_idx(id)]._neighbor_count; x++) {
				int neighbor_id = _vertices[arr_idx(id)]._neighbors[x];

				if (visited_vertices[arr_idx(neighbor_id)] == VertexColor::UNVISITED) {
					visited_vertices[arr_idx(neighbor_id)] = opposite_color; /*vertex has been checked and added to stack to visit*/
					vertices_stack[stack_iter++] = neighbor_id;
				}
				else if (visited_vertices[arr_idx(neighbor_id)] == actual_color)
					return false;
			}
		}
	}

	return true;
}
