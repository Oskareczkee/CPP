#include "GraphLRPA.h"

void GraphLRPA::init()
{
    roots.clear();
    height.assign(g.get_degree(), infinity);
    parent_edge.assign(g.get_degree(), -1);
}

bool GraphLRPA::is_planar()
{
    if (g._degree < 3)
        return true;
    else if ((3 * g._degree - 6) < g._edges)
        return false;

    init();

    //orientation
    for (int x = 0; x < g._degree; x++) {
        if (height[x] == infinity) {
            height[x] = 0;
            roots.push_back(x);
            dfs1(x);
        }
    }


}

void GraphLRPA::dfs1(const int& vertex_id)
{
    int vertex_arr_idx = g.arr_idx(vertex_id);
    int edge = parent_edge[vertex_arr_idx];
    for (int x = 0; x < g._vertices[vertex_arr_idx]._neighbor_count; x++) {
        int neighbor_id = g._vertices[vertex_arr_idx]._neighbors[x];
        int neighbor_arr_idx = g.arr_idx(neighbor_id);

        if(exists(Edge(neighbor_id, vertex_id), orientation)) //TODO: check code here if does not work
            continue;

        Edge e(vertex_id, neighbor_id); //create orientation

        if (height[neighbor_arr_idx] == infinity) { /*tree edge*/
            parent_edge[neighbor_arr_idx] = vertex_id;
            height[neighbor_arr_idx] = height[vertex_arr_idx] + 1;
            dfs1(neighbor_id);
        }
        /*to be continued*/
    }
}

