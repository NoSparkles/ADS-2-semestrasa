#include "graph.h"

Node* createNode(int v) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

Graph* createGraph(int vertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = vertices;
    graph->adjLists = (Node**)malloc(vertices * sizeof(Node*));
    graph->visited = (int*)malloc(vertices * sizeof(int));

    for (int i = 0; i < vertices; i++) {
        graph->adjLists[i] = NULL;
        graph->visited[i] = 0;
    }

    return graph;
}

void addEdge(Graph* graph, int src, int dest) {
    Node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;

    newNode = createNode(src);
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}

void printGraph(Graph* graph) {
    printf("\nGraph adjacency list:\n");
    for (int i = 0; i < graph->numVertices; i++) {
        printf("%d: ", i);
        Node* temp = graph->adjLists[i];
        while (temp) {
            printf("%d ", temp->vertex);
            temp = temp->next;
        }
        printf("\n");
    }
}

void printTree(int parent[], int numVertices) {
    printf("\nTree structure:\n");
    for (int i = 0; i < numVertices; i++) {
        if (parent[i] != -1) {
            printf("%d -> %d\n", parent[i], i);
        }
    }
}

void bfsToTree(Graph* graph, int startVertex) {
    int parent[MAX_VERTICES];
    for (int i = 0; i < graph->numVertices; i++) {
        parent[i] = -1;
    }

    int queue[MAX_VERTICES], front = 0, rear = 0;
    queue[rear++] = startVertex;
    graph->visited[startVertex] = 1;

    while (front < rear) {
        int currentVertex = queue[front++];

        Node* temp = graph->adjLists[currentVertex];
        while (temp) {
            int adjVertex = temp->vertex;

            if (!graph->visited[adjVertex]) {
                graph->visited[adjVertex] = 1;
                queue[rear++] = adjVertex;
                parent[adjVertex] = currentVertex;
            }
            temp = temp->next;
        }
    }

    printTree(parent, graph->numVertices);
}

void freeGraph(Graph* graph) {
    for (int i = 0; i < graph->numVertices; i++) {
        Node* temp = graph->adjLists[i];
        while (temp) {
            Node* toFree = temp;
            temp = temp->next;
            free(toFree);
        }
    }
    free(graph->adjLists);
    free(graph->visited);
    free(graph);
}