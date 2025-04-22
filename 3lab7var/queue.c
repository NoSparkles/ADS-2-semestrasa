#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Creates an empty queue, returns an address to the new Queue
Queue* create()
{
    Queue* queue = malloc(sizeof(Queue));
    if(!queue) return NULL;

    queue->head = NULL;
    queue->tail = NULL;
    queue->size = 0;
    return queue;
}

// Returns the element count of the Queue
int count(Queue *queue)
{
    return queue->size;
}

// Returns True if the queue is empty False if it's not
bool is_empty(Queue *queue)
{
    return (queue->size == 0);
}

// Returns the int value of the head element (first in line)
int peek(Queue *queue, bool *status){
    if(is_empty(queue))
    {
        *status = false;
        return 0;
    }
    *status = true;
    return queue->head->value;
}

// Adds a node of set value to the Queue
void enqueue(Queue* queue, int value){
    // Create the desired Node
    Node *newNode = malloc(sizeof(Node));
    newNode->value = value;


    // Set the next element to NULL since it will be at the back of the line
    newNode->next = NULL;

    // If the queue is empty it becomes the tail and the head Node
    if(is_empty(queue)){
        queue->head = newNode;
        queue->tail = newNode;
    }
    // Else we point the last in Node to our new Node and update the tail address
    else
    {
        queue->tail->next = newNode;
        queue->tail = newNode;
    }
    
    queue->size++;
}
// Removes the first element in queue and returns it's value
int dequeue(Queue* queue, bool *status){
    // If empty we return NULL, since we can't remove from an empty Queue
    if(is_empty(queue)){
        *status = false;
        return 0;
    }

    // Update the status, since we can't return 0 to signify a failed removal, because an element with a value of 0 might of been removed
    *status = true;

    // set value to the head node (one to be removed) value - for returning
    int value = queue->head->value;

    // create a Node* for the Node to be removed
    Node* oldHead = queue->head;
    // If the queue only had one element it means it will have no head or tail, so we update Queue to point to NULL
    if(queue->size == 1){
        queue->head = NULL;
        queue->tail = NULL;
    } else{
        // Else we set the new head to the next in line head-> next
        queue->head = queue->head->next;
    }
   
    //We free the old head
    free(oldHead);

    // Update the size accordingly
    queue->size--;

    return value;
}

// if we don't have enough memory to reserve another Node we return false
bool isFull(Queue* queue){
    Node *temp = malloc(sizeof(Node));
    if(!temp) return true;
    free(temp);
    return false;
}

// Destroys the queue
void done(Queue* queue){
    makeEmpty(queue);
    free(queue);
}

// Prints the queue in readable human format example 1 -> 2 -> 3 ...
void toString(Queue* Queue){
    Node* currentNode;
    currentNode = Queue->head;
    int current = 0;
    printf("Queue: [ ");

    while(currentNode != NULL && current < MAX_ELEMENTS_TO_PRINT){
        printf("%d ", currentNode->value);
        currentNode = currentNode->next;

        if(currentNode != NULL && current < MAX_ELEMENTS_TO_PRINT) printf(" -> ");
        else if(currentNode != NULL && current == MAX_ELEMENTS_TO_PRINT) printf(" -> ... ");

        current++;
    }
    printf(" ]\n");
}

// Clones the queue and returns a new queue with the same elements
Queue* clone(Queue* queue) {
    Queue* cloneQueue = create();
    Node* currentNode = queue->head;

    while (currentNode != NULL) {
        enqueue(cloneQueue, currentNode->value);
        currentNode = currentNode->next;
    }
    return cloneQueue;
}

// Removes every Node, makes the Queue empty
void makeEmpty(Queue* queue){
    if(is_empty(queue)){
        return;
    }

    Node* currentNode = queue->head;
    Node* temp;

    while(!is_empty(queue)){
        temp = currentNode->next;
        free(currentNode);
        currentNode = temp;
        queue->size--;
    }
    queue->head = NULL;
    queue->tail = NULL;
}