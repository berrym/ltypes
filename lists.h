#ifndef LISTS_H
#define LISTS_H

#include <stddef.h>             // for type size_t
#include <stdbool.h>            // for type bool

// Result type used for nodeComparator functions
typedef enum Result {
    LESS = -1,
    EQUAL = 0,
    GREATER = 1
} Result;

// Forward declarations of operations common to singly/doubly linked lists
typedef void (*freeFunction)(void *);
typedef bool (*listIterator)(void *);
typedef Result (*nodeComparator)(const void *, const void *);

///////////////////////////////////////////////////////////////////////////////
// Singly linked list
//
// A singly linked list is a common data structure that consists of a series
// of nodes that contain a piece of data and a pointer to the next node in
// the list.  Singly linked lists in C are homogenous (each node contains the
// same data type).
//
// In this implementation of a linked list we use two different structs.
//
// One is for the the node, it contains the data and the pointer to the next
// node.
//
// The second is to represent the list as a whole such as the size in bytes
// in memory of the data in the node, the number of nodes in the list, and
// pointers to both the head (first node) in the list and the tail (the last
// node) in the list.  It also contains a freeFunction that can be called
// when removing nodes if neccesary, if this function is not necessary it can
// be provided as NULL and will be ignored.
///////////////////////////////////////////////////////////////////////////////

// Singly linked list node
typedef struct linkedListNode {
    void *data;                  // node data
    struct linkedListNode *next; // pointer to the next node in the list
} linkedListNode;

// Singly linked list
typedef struct linkedList {
    size_t logicalLength;       // number of nodes in the list
    size_t elementSize;         // size of each element in bytes
    linkedListNode *head;       // pointer to the beginning/head of the list
    linkedListNode *tail;       // pointer to the end/tail of the list
    freeFunction freeFn;        // optional function used to free nodes
}  linkedList;

// Forward declarations of singly linked list operations
linkedList *ll_create(size_t, freeFunction);
void ll_delete(linkedList *);
void ll_push(linkedList *, void *);
void ll_append(linkedList *, void *);
void ll_insertAfter(linkedList *, linkedListNode *, void *);
void ll_deleteNode(linkedList *, void *, nodeComparator);
linkedListNode *ll_getNodeAt(linkedList *, size_t);
bool ll_search(linkedList *, void *, nodeComparator);
void ll_foreach(linkedList *, listIterator);
void ll_head(linkedList *, void *, bool);
linkedListNode *ll_first(linkedList *);
void ll_tail(linkedList *, void *);
linkedListNode *ll_last(linkedList *);
bool ll_isEmpty(linkedList *);
size_t ll_length(linkedList *);
void ll_reverse(linkedList *);
void ll_swapNodeData(linkedList *, linkedListNode *, linkedListNode *);
void ll_selectionSort(linkedList *, nodeComparator);
linkedList *ll_split(linkedList *);

///////////////////////////////////////////////////////////////////////////////
// Doubly linked list
//
// A doubly linked list is like a singly linked list except that each node
// contains a pointer to both the next and previous nodes in the list.
///////////////////////////////////////////////////////////////////////////////

// Doubly linked list node
typedef struct dLinkedListNode {
    void *data;                   // node data
    struct dLinkedListNode *prev; // pointer to previous node
    struct dLinkedListNode *next; // pointer to next node
}  dLinkedListNode;

// Doubly linked list
typedef struct dLinkedList {
    size_t logicalLength;       // number of nodes in the list
    size_t elementSize;         // size of each element in bytes
    dLinkedListNode *head;      // pointer to the beginning/head of the list
    dLinkedListNode *tail;      // pointer to the end/tail of the list
    freeFunction freeFn;        // optional function used to free nodes
} dLinkedList;

// Forward declarations of doubly linked list operations
dLinkedList *dll_create(size_t, freeFunction);
void dll_delete(dLinkedList *);
void dll_push(dLinkedList *, void *);
void dll_append(dLinkedList *, void *);
void dll_insertAfter(dLinkedList *, dLinkedListNode *, void *);
void dll_insertBefore(dLinkedList *, dLinkedListNode *, void *);
void dll_deleteNode(dLinkedList *, void *, nodeComparator);
dLinkedListNode *dll_getNodeAt(dLinkedList *, size_t);
bool dll_search(dLinkedList *, void *, nodeComparator);
void dll_foreach(dLinkedList *, listIterator);
void dll_head(dLinkedList *, void *, bool);
dLinkedListNode *dll_first(dLinkedList *);
void dll_tail(dLinkedList *, void *);
dLinkedListNode *dll_last(dLinkedList *);
bool dll_isEmpty(dLinkedList *);
size_t dll_length(dLinkedList *);
void dll_reverse(dLinkedList *);
void dll_swapNodeData(dLinkedList *, dLinkedListNode *, dLinkedListNode *);
void dll_selectionSort(dLinkedList *, nodeComparator);
dLinkedList *dll_split(dLinkedList *);

#endif
