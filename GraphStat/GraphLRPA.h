#pragma once
#include <vector>
#include <algorithm>
#include "Graph.h"


class GraphLRPA {
private:
	Graph& g;

	struct Edge{
		int from, to;
		Edge() : from(-1), to(-1) {}
		Edge(int from_, int to_) : from(from_), to(to_){}
		bool operator==(const Edge& e)const { return from == e.from && to == e.to; }
	};

	const int infinity = INT32_MAX;
	std::vector<int> height;
	std::vector<int> roots;
	std::vector<int> parent_edge;

	std::vector<Edge> lowopt;
	std::vector<Edge> lowopt2;
	std::vector<Edge> orientation;

	void init();
	void dfs1(const int& vertex_id);

	template<class T>
	bool exists(const T& val, std::vector<T> vec);

public:
	GraphLRPA(Graph& g_ref) : g(g_ref) { init(); }
	bool is_planar();
};

template<class T>
inline bool GraphLRPA::exists(const T& val, std::vector<T> vec)
{
	for (T v : vec)
		if (val == v) return true;
	return false;
}
