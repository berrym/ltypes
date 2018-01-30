#ifndef LTYPES_H
#define LTYPES_H

#include <stddef.h>             // for type size_t
#include <stdbool.h>            // for type bool

typedef void (*freeFunction)(void *);
typedef bool (*listIterator)(void *);
typedef int (*nodeComparator)(const void *, const void *);

// Singly linked list
struct linkedListNode {
    void *data;
    struct linkedListNode *next;
};
typedef struct linkedListNode linkedListNode;

struct linkedList {
    size_t logicalLength;
    size_t elementSize;
    linkedListNode *head;
    linkedListNode *tail;
    freeFunction freeFn;
};
typedef struct linkedList linkedList;

linkedList *ll_create(size_t, freeFunction);
void ll_delete(linkedList *);
void ll_push(linkedList *, void *);
void ll_append(linkedList *, void *);
void ll_insertAfter(linkedList *, linkedListNode *, void *);
void ll_deleteNode(linkedList *, void *, nodeComparator);
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

// Doubly linked list
struct dLinkedListNode {
    void *data;
    struct dLinkedListNode *prev;
    struct dLinkedListNode *next;
};
typedef struct dLinkedListNode dLinkedListNode;

struct dLinkedList {
    size_t logicalLength;
    size_t elementSize;
    dLinkedListNode *head;
    dLinkedListNode *tail;
    freeFunction freeFn;
};
typedef struct dLinkedList dLinkedList;

dLinkedList *dll_create(size_t, freeFunction);
void dll_delete(dLinkedList *);
void dll_push(dLinkedList *, void *);
void dll_append(dLinkedList *, void *);
void dll_insertAfter(dLinkedList *, dLinkedListNode *, void *);
void dll_insertBefore(dLinkedList *, dLinkedListNode *, void *);
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
