#include <iostream>
#include <fstream>

#include "Graph.h"

using namespace std;

istream& input = cin;
int graph_count = 0;

/*
    auto ds = g.degree_sequence();
    auto ecc = g.vertices_eccentrity();
    auto colors_greedy = g.greedy_coloring();
    auto color_lf = g.lf_coloring();
    auto color_slf = g.slf_coloring();

    cout << "\n\nDegree sequence: ";
    for (int x = 0; x < g.get_degree(); x++)
        cout << ds[x] << " ";
    cout << "\nComponent number: " << g.components_number() << "\n";
    cout << "Is Bipartite: " << (g.is_bipartite() ? "T" : "F") << "\n";
    cout << "Vertex eccentricies: ";
    for (int x = 0; x < g.get_degree(); x++)
        cout << ecc[x] << " ";
    cout << "\nIs Planar: " << (g.is_planar() ? "T" : "F") << "\n";
    cout << "Greedy Coloring: ";
    for (int x = 0; x < g.get_degree(); x++)
        cout << colors_greedy[x] << " ";
    cout << "\nLF Coloring: ";
    for (int x = 0; x < g.get_degree(); x++)
        cout << color_lf[x] << " ";
    cout << "\nSLF Coloring: ";
    for (int x = 0; x < g.get_degree(); x++)
        cout << color_slf[x] << " ";
    cout << "\nC4 subgraphs: " << g.number_of_c4_subgraphs() << "\n";
    cout << "Complement's edges: " << g.complement_edges() << "\n";
*/

void print_graph_info(Graph& g)
{
    auto ds = g.degree_sequence();
    //auto ecc = g.vertices_eccentrity();
    auto colors_greedy = g.greedy_coloring();
    auto color_lf = g.lf_coloring();
    //auto color_slf = g.slf_coloring();

    for (int x = 0; x < g.get_degree(); x++)
        cout << ds[x] << " ";
    cout << "\n" << g.components_number() << "\n";
    cout << (g.is_bipartite() ? "T" : "F") << "\n";
    cout << "?\n";
    cout << "?\n";
    for (int x = 0; x < g.get_degree(); x++)
        cout << colors_greedy[x] << " ";
    cout << "\n";
    for (int x = 0; x < g.get_degree(); x++)
        cout << color_lf[x] << " ";
    cout << "\n?";
    cout << "\n?\n";
    cout << g.complement_edges() << "\n";
}

int main()
{
    int actual_graph = 0;

    input >> graph_count;

    while (input && actual_graph < graph_count) {
        Graph graph;
        int degree = 0;
        input >> degree;
        graph.set_degree(degree);

        for (int i = 0; i < degree; i++) {
            Vertex v;
            input >> v;
            graph.add_vertex(v);
        }
        
        print_graph_info(graph);

        actual_graph++;
    }
}
