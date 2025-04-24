#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Creates an empty queue and returns its address
Queue* create() {
    Queue* queue = malloc(sizeof(Queue));
    if (!queue) return NULL;

    queue->head = NULL;
    queue->tail = NULL;
    queue->size = 0;  // Now an integer instead of LongNum
    return queue;
}

// Returns the number of elements in the queue
int count(Queue *queue) {
    return queue->size;
}

// Checks if the queue is empty
bool is_empty(Queue *queue) {
    return queue->size == 0;
}

// Returns the first element's value
int peek(Queue *queue, bool *status) {
    if (is_empty(queue)) {
        if (status) *status = false;
        return 0; // Return 0 instead of creating a new LongNum
    }
    if (status) *status = true;
    return queue->head->value;
}

// Adds a new node with a value to the queue
void enqueue(Queue* queue, int value) {
    Node *newNode = malloc(sizeof(Node));
    if (!newNode) return;

    newNode->value = value;
    newNode->next = NULL;

    if (is_empty(queue)) {
        queue->head = newNode;
        queue->tail = newNode;
    } else {
        queue->tail->next = newNode;
        queue->tail = newNode;
    }
    
    queue->size++; // Increment the integer size directly
}

// Removes the first queue element and returns its value
int dequeue(Queue *queue, bool *status) {
    if (is_empty(queue)) {
        if (status) *status = false;
        return 0; // Return 0 instead of creating a new LongNum
    }

    if (status) *status = true;
    
    Node *oldHead = queue->head;
    int value = oldHead->value; // Store value safely
    
    // Update queue pointers correctly
    if (queue->size == 1) {
        queue->head = NULL;
        queue->tail = NULL;
    } else {
        queue->head = queue->head->next;
    }

    free(oldHead);
    queue->size--; // Decrement the integer size directly

    return value;
}

// Checks if the queue is full (if memory runs out)
bool isFull(Queue* queue) {
    Node *temp = malloc(sizeof(Node));
    if (!temp) return true;
    free(temp);
    return false;
}

// Clears the queue and frees memory
void done(Queue* queue) {
    makeEmpty(queue);
    free(queue);
}

// Displays the queue in a readable way
void toString(Queue* queue) {
    Node* currentNode = queue->head;
    int current = 0;
    printf("Queue: [ ");

    while (currentNode != NULL && current < MAX_ELEMENTS_TO_PRINT) {
        printf("%d", currentNode->value);
        currentNode = currentNode->next;

        if (currentNode != NULL && current < MAX_ELEMENTS_TO_PRINT) printf(" -> ");
        else if (currentNode != NULL && current == MAX_ELEMENTS_TO_PRINT) printf(" -> ... ");

        current++;
    }
    printf(" ]\n");
}

// Creates a clone of the queue and returns a new queue with the same elements
Queue* clone(Queue* queue) {
    Queue* cloneQueue = create();
    Node* currentNode = queue->head;

    while (currentNode != NULL) {
        enqueue(cloneQueue, currentNode->value);
        currentNode = currentNode->next;
    }
    return cloneQueue;
}

// Clears the queue, removing all nodes
void makeEmpty(Queue* queue) {
    while (!is_empty(queue)) {
        dequeue(queue, NULL);
    }
    queue->head = NULL;
    queue->tail = NULL;
}