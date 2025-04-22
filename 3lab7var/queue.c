#include "queue.h"
#include "longnum.h"  // Įtraukiame LongNum biblioteką
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Sukuria tuščią eilę ir grąžina jos adresą
Queue* create() {
    Queue* queue = malloc(sizeof(Queue));
    if (!queue) return NULL;

    queue->head = NULL;
    queue->tail = NULL;
    queue->size = createLongNum("0");  // Sukuriame `size` kaip `LongNum`
    return queue;
}

// Grąžina elementų kiekį eilėje
LongNum *count(Queue *queue) {
    return queue->size;
}

// Patikrina, ar eilė tuščia
bool is_empty(Queue *queue) {
    return equals(queue->size, createLongNum("0"));
}

// Grąžina pirmo elemento reikšmę
LongNum *peek(Queue *queue, bool *status) {
    if (is_empty(queue)) {
        *status = false;
        return createLongNum("0");
    }
    *status = true;
    return queue->head->value;
}

// Prideda naują mazgą su reikšme į eilę
void enqueue(Queue* queue, LongNum *value) {
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
    
    queue->size = add(queue->size, createLongNum("1"));
}

// Pašalina pirmą eilės elementą ir grąžina jo reikšmę
LongNum *dequeue(Queue* queue, bool *status) {
    if (is_empty(queue)) {
        *status = false;
        return createLongNum("0");
    }

    *status = true;
    LongNum *value = queue->head->value;
    Node* oldHead = queue->head;

    if (equals(queue->size, createLongNum("1"))) {
        queue->head = NULL;
        queue->tail = NULL;
    } else {
        queue->head = queue->head->next;
    }

    free(oldHead);
    queue->size = subtract(queue->size, createLongNum("1"));
    return value;
}

// Patikrina, ar eilė pilna (jei trūksta atminties)
bool isFull(Queue* queue) {
    Node *temp = malloc(sizeof(Node));
    if (!temp) return true;
    free(temp);
    return false;
}

// Išnaikina eilę
void done(Queue* queue) {
    makeEmpty(queue);
    free(queue);
}

// Atvaizduoja eilę patogiu būdu
void toString(Queue* queue) {
    Node* currentNode = queue->head;
    int current = 0;
    printf("Queue: [ ");

    while (currentNode != NULL && current < MAX_ELEMENTS_TO_PRINT) {
        printLongNum(currentNode->value);
        currentNode = currentNode->next;

        if (currentNode != NULL && current < MAX_ELEMENTS_TO_PRINT) printf(" -> ");
        else if (currentNode != NULL && current == MAX_ELEMENTS_TO_PRINT) printf(" -> ... ");

        current++;
    }
    printf(" ]\n");
}

// Sukuria kloną eilės ir grąžina naują eilę su tais pačiais elementais
Queue* clone(Queue* queue) {
    Queue* cloneQueue = create();
    Node* currentNode = queue->head;

    while (currentNode != NULL) {
        enqueue(cloneQueue, currentNode->value);
        currentNode = currentNode->next;
    }
    return cloneQueue;
}

// Išvalo eilę, pašalina visus mazgus
void makeEmpty(Queue* queue) {
    if (is_empty(queue)) {
        return;
    }

    Node* currentNode = queue->head;
    Node* temp;

    while (!is_empty(queue)) {
        temp = currentNode->next;
        free(currentNode);
        currentNode = temp;
        queue->size = subtract(queue->size, createLongNum("1"));
    }

    queue->head = NULL;
    queue->tail = NULL;
}