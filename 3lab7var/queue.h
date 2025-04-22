#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>

// Define the maximum elements to print
#define MAX_ELEMENTS_TO_PRINT 10

// Node structure
typedef struct Node {
    int value;
    struct Node *next;
} Node;

// Queue structure
typedef struct {
    Node *head;
    Node *tail;
    int size;
} Queue;

// Function prototypes
Queue *create();
int count(Queue *queue);
bool is_empty(Queue *queue);
int peek(Queue *queue, bool *status);
void enqueue(Queue *queue, int value);
int dequeue(Queue *queue, bool *status);
bool isFull(Queue *queue);
void toString(Queue *queue);
void makeEmpty(Queue *queue);
void done(Queue *queue);
Queue* clone(Queue* queue);

#endif // QUEUE_H
