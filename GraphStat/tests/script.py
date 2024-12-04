import networkx as nx
import numpy as np
import matplotlib.pyplot as plt

def parse_graph(input_data):
    graph = nx.Graph()
    for i, line in enumerate(input_data):
        edges = list(map(int, line.split()))
        node = i + 1
        graph.add_node(node)
        for edge in edges[1:]:  # Skip the first number which is the count of edges
            graph.add_edge(node, edge)
    return graph

def slf_coloring(graph):
    nodes = list(graph.nodes)
    colors = {node: 0 for node in nodes}
    saturation = {node: 0 for node in nodes}

    def update_saturation(v):
        for neighbor in graph.neighbors(v):
            if colors[neighbor] == 0:  # If the neighbor is uncolored
                saturation[neighbor] += 1

    def max_saturation():
        max_saturation = -1
        max_degree = -1
        selected_node = None
        for node in nodes:
            if colors[node] == 0:  # Only consider uncolored nodes
                if (saturation[node] > max_saturation or
                    (saturation[node] == max_saturation and graph.degree[node] > max_degree) or
                    (saturation[node] == max_saturation and graph.degree[node] == max_degree and node < selected_node)):
                    max_saturation = saturation[node]
                    max_degree = graph.degree[node]
                    selected_node = node
        return selected_node

    def get_next_color(v):
        neighbor_colors = set(colors[neighbor] for neighbor in graph.neighbors(v))
        color = 1
        while color in neighbor_colors:
            color += 1
        return color

    while any(color == 0 for color in colors.values()):
        v_max = max_saturation()
        chosen_color = get_next_color(v_max)
        colors[v_max] = chosen_color
        update_saturation(v_max)

    return colors

# Input graph data
input_data = [
    "6 5 13 11 12 7 8",
    "5 11 10 18 5 20",
    "3 6 7 5",
    "6 20 17 19 9 8 6",
    "8 1 15 19 13 11 2 17 3",
    "5 3 15 20 4 13",
    "5 14 9 12 3 1",
    "2 4 1",
    "5 20 18 7 12 4",
    "4 2 13 12 17",
    "5 2 14 1 18 5",
    "6 1 16 14 7 9 10",
    "5 1 19 10 5 6",
    "4 11 7 12 19",
    "4 5 20 6 16",
    "3 18 12 15",
    "5 20 18 4 5 10",
    "5 16 17 2 11 9",
    "4 13 4 5 14",
    "6 17 9 4 15 2 6"
]

# Parse the input to create a graph
graph = parse_graph(input_data)

# Calculate the colors using SLF method
colors = slf_coloring(graph)

# Print the colors
print("Node colors:")
for node, color in colors.items():
    print(f"Node {node}: Color {color}")

# Optional: Draw the graph with colors
plt.figure(figsize=(10, 10))
pos = nx.spring_layout(graph)
nx.draw(graph, pos, with_labels=True, node_color=[colors[node] for node in graph.nodes], cmap=plt.cm.rainbow)
plt.show()
