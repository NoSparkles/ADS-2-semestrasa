#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

int main(int argc, char* argv[]) {
    FILE *input = stdin;

    if (argc > 1) {
        input = fopen(argv[1], "r");
        if (!input) {
            perror("cannot open input file");
            return EXIT_FAILURE;
        }
    }

    int vertices;
    fscanf(input, "%d", &vertices);
    Graph* graph = createGraph(vertices);

    int u, v;
    while (fscanf(input, "%d %d", &u, &v) == 2) {
        addEdge(graph, u, v);
        printf("Added: %d -> %d\n", u, v);
    }

    if (input != stdin) {
        fclose(input);
    }

    printf("\nGraph before converting to a tree:\n");
    printGraph(graph);

    printf("\nBFS tree formation starting from vertex 0:\n");
    bfsToTree(graph, 0);

    freeGraph(graph);
    return 0;
}