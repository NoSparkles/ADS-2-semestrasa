#include "graph.h"

int main() {
    int vertices = 7;
    Graph* graph = createGraph(vertices);

    // Adding edges to the graph
    printf("Adding edges to the graph:\n");
    addEdge(graph, 0, 1);
    printf("Added: 0 -> 1\n");
    addEdge(graph, 0, 2);
    printf("Added: 0 -> 2\n");
    addEdge(graph, 1, 3);
    printf("Added: 1 -> 3\n");
    addEdge(graph, 1, 4);
    printf("Added: 1 -> 4\n");
    addEdge(graph, 2, 5);
    printf("Added: 2 -> 5\n");
    addEdge(graph, 2, 6);
    printf("Added: 2 -> 6\n");

    // Displaying the initial graph
    printf("\nGraph before converting to a tree:\n");
    printGraph(graph);

    // Performing BFS to form a tree and printing its structure
    printf("\nBFS tree formation starting from vertex 0:\n");
    bfsToTree(graph, 0);

    // Freeing allocated memory
    freeGraph(graph);
    return 0;
}