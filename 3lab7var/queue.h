// sukurtas moikiniu kapa1135 ir pamodifikuotas manimi

#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>
#include "longnum.h"  // Įtraukiame LongNum biblioteką

// Define the maximum elements to print
#define MAX_ELEMENTS_TO_PRINT 10

// Node structure
typedef struct Node {
    LongNum *value;        // Naudojame *LongNum vietoj int
    struct Node *next;
} Node;

// Queue structure
typedef struct {
    Node *head;
    Node *tail;
    LongNum *size;        // Naudojame *LongNum vietoj int
} Queue;

// Function prototypes
Queue *create();
LongNum *count(Queue *queue);
bool is_empty(Queue *queue);
LongNum *peek(Queue *queue, bool *status);
void enqueue(Queue *queue, LongNum *value);
LongNum *dequeue(Queue *queue, bool *status);
bool isFull(Queue *queue);
void toString(Queue *queue);
void makeEmpty(Queue *queue);
void done(Queue *queue);
Queue* clone(Queue* queue);

#endif // QUEUE_H