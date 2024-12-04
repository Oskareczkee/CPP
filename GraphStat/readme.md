# Graph Stat

Graph stat is project implementing various algorithms for graphs

# Algorithms
Algorithms inlcude:
- Getting degree sequence (List of all vertice's degrees)
- Greedy coloring of graph
- LF (Largest First) coloring of graph
- SLF (Smallest Last Coloring) implemented by using DSatur Algorithm (Slow due custom data structures, when using STL it does the work)
- Components number
- Biparitite testing
- Complement edges
- Number of C(n) subgraphs (requires faster matrix algorithms)
- Simple planarity testing (No left right planarity test)
- Vertex eccentricies

# Testing
Tests can be found under ```./tests``` directory. In ```GraphStat.cpp``` actual input is set to cin, so you have to copy whole file and paste it to the console.  
Alternativly you can create ```ifstream ifs{"./test/{test_file}"};``` variable and change ```istream& input = ifs```. Then the test will be automatically loaded from file. Cin was used for testing purposes