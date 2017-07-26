/**
 * dLinkedList.c
 *
 * Functions to manipulate a generic doubly linked list that can handle
 * multiple types by use of type casting from void variable/function pointers.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "ltypes.h"

/**
 * dll_create:
 *      Initialize doubly linked list.
 */
void dll_create(dLinkedList *l, size_t size, freeFunction fn)
{
    // initialize list
    l->logicalLength = 0;
    l->elementSize = size;
    l->head = l->tail = NULL;
    l->freeFn = fn;
}

/**
 * dll_delete:
 *      Remove each node from a doubly linked list.
 */
void dll_delete(dLinkedList *l)
{
    dLinkedListNode *curr;
    while (l->head) {
        curr = l->head;
        l->head = curr->next;

        // use the list freeFunction if supplied
        if (l->freeFn)
            l->freeFn(curr->data);

        // free node
        free(curr->data);
        free(curr);
        l->logicalLength--;     // decrease list's logical length
    }

    l->head = l->tail = NULL;   // reset list head/tail
}

/**
 * dll_push:
 *  Push a new node to the front of a doubly linked list.
 */
void dll_push(dLinkedList *l, void *el)
{
    // allocate memory for new list node
    dLinkedListNode *node = calloc(1, sizeof(dLinkedListNode));
    if (!node) {
        perror("unable to allocate memory for node");
        abort();
    }
    node->prev = NULL;

    // allocate memory for new node's data
    if ((node->data = calloc(1, l->elementSize)) == NULL) {
        perror("unable to allocate memory for node");
        abort();
    }

    // copy new data to node
    memcpy(node->data, el, l->elementSize);

    // set node as new list head
    node->next = l->head;
    l->head ->prev = node;
    l->head = node;

    // first node?
    if (!l->tail)
        l->tail = l->head;

    l->logicalLength++;         // increase list's logical length
}

/**
 * dll_append:
 *  Append a new node to the end of a doubly linked list.
 */
void dll_append(dLinkedList *l, void *el)
{
    // allocate memory for a new node
    dLinkedListNode *node = calloc(1, sizeof(dLinkedListNode));
    if (!node) {
        perror("unable to allocate memory for node");
        abort();
    }

    // allocate memory for the new node's data
    if ((node->data = calloc(1, l->elementSize)) == NULL) {
        perror("unable to allocate memory for node");
        abort();
    }
    memcpy(node->data, el, l->elementSize);

    // reset node links
    if (l->logicalLength == 0) {
        l->head = l->tail = node;
        l->head->prev = l->tail->next = NULL;
        l->tail->prev = l->head;
    } else if (l->logicalLength == 1) {
        l->head->next = node;
        node->prev = l->head;
        node->next = NULL;
        l->tail = node;
    } else {
        l->tail->next = node;
        node->prev = l->tail;
        l->tail = node;
        l->tail->next = NULL;
    }

    l->logicalLength++;         // increase logical list length
}

/**
 * dll_insertAfter:
 *  Insert a new node into a doubly linked list after a given node.
 */
void dll_insertAfter(dLinkedList *l, dLinkedListNode *prev, void *el)
{
    assert(prev);

    // Use append method if prev is list tail
    if (prev == l->tail) {
        dll_append(l, el);
        return;
    }

    // Allocate memory for the new node
    dLinkedListNode *node = calloc(1, sizeof(dLinkedListNode));
    if (!node) {
        perror("Unable to allocate memory for new node");
        abort();
    }

    // allocate memory for the new node's data
    if (!(node->data = calloc(1, l->elementSize))) {
        perror("unable to allocate memory for node");
        abort();
    }
    memcpy(node->data, el, l->elementSize); // copy data

    // Set new node links
    node->next = prev->next;
    prev->next = node;
    node->prev = prev;
    node->next->prev = node;
    l->logicalLength++;         // increase list's logical length
}

/**
 * dll_insertBefore:
 *  Insert a new node before a given node.
 */
void dll_insertBefore(dLinkedList *l, dLinkedListNode *next, void *el)
{
    assert(next);

    // Use push method if next is list head
    if (next == l->head) {
        dll_push(l, el);
        return;
    }

    // Allocate memory for the new node
    dLinkedListNode *node = calloc(1, sizeof(dLinkedListNode));
    if (!node) {
        perror("Unable to allocate memory for new node");
        abort();
    }

    // allocate memory for the new node's data
    if (!(node->data = calloc(1, l->elementSize))) {
        perror("unable to allocate memory for node");
        abort();
    }
    memcpy(node->data, el, l->elementSize); // copy data

    // set new node links
    node->prev = next->prev;
    next->prev = node;
    node->next = next;
    node->prev->next = node;
    l->logicalLength++;         // increase list's logical length
}
    
/**
 * dll_foreach:
 *  Iterate over a doubly linked list and perform the tasks
 *  in the listIterator function on each node.
 */
void dll_foreach(dLinkedList *l, listIterator it)
{
    // assert that a list iterating function was passed
    assert(it);

    bool result = true;
    dLinkedListNode *node = l->head;

    // Iterate over the list, return on tail if the list is circular
    // or head if travering the list in reverse
    while (node && result) {
        result = it(node->data);
        node = node->next;
    }
}

/**
 * dll_head:
 *  Return a copy of the head of a doubly linked list's head and optionally
 *  remove/pop it from the list.
 */
void dll_head(dLinkedList *l, void *el, bool remove)
{
    // assert that the list is initialized
    assert(l->head);

    // copy the list's head to a new element
    dLinkedListNode *node = l->head;
    memcpy(el, node->data, l->elementSize);

    // remove/pop head node from list
    if (remove) {
        l->head = node->next;

        // use freeFunction if it exists
        if (l->freeFn)
            l->freeFn(node->data);

        free(node->data);
        free(node);
        l->logicalLength--;     // decrease list's logical length
    }
}

/**
 * dll_first:
 *  Return a pointer to head node of the doubly linked list.
 */
dLinkedListNode *dll_first(dLinkedList *l)
{
    return l->head;
}

/**
 * dll_tail:
 *  Return a copy of the tail node of a doubly linked list.
 */
void dll_tail(dLinkedList *l, void *el)
{
    // assert that the list is initialized
    assert(l->tail);

    // copy the list's tail to a new element
    dLinkedListNode *node = l->tail;
    memcpy(el, node->data, l->elementSize);
}

/**
 * dll_last:
 *  Return a pointer to the tail node of the doubly linked list.
 */
dLinkedListNode *dll_last(dLinkedList *l)
{
    return l->tail;
}

/**
 * dll_isEmpty:
 *  Return true if the doubly linked list is empty, return false otherwise.
 */
bool dll_isEmpty(dLinkedList *l)
{
    return l->logicalLength == 0;
}

/**
 * dll_length:
 *  Rerturn the number of nodes in a doubly linked list.
 */
size_t dll_length(dLinkedList *l)
{
    return l->logicalLength;
}

/**
 * dll_reverse:
 *  Reverse the node order of a doubly linked list.
 */
void dll_reverse(dLinkedList *l)
{
    dLinkedListNode *curr = l->head;
    dLinkedListNode *temp = NULL;

    // reset node links
    while (curr) {
        temp = curr->prev;
        curr->prev = curr->next;
        curr->next = temp;
        curr = curr->prev;
    }

    if (temp)
        l->head = temp->prev;             // reset head
}

/**
 * dll_swapNodeData:
 *  Swap the data of two node's in a doubly linked list.
 */
void dll_swapNodeData(dLinkedList *l, dLinkedListNode *a, dLinkedListNode *b)
{
    // allocate a temporary node
    dLinkedListNode *tmp = calloc(1, sizeof(dLinkedListNode));
    if (!tmp) {
        perror("Unable to allocate memory for a temporary node");
        abort();
    }
    if (!(tmp->data = calloc(1, sizeof(l->elementSize)))) {
        perror("Unable to allocate memory for temporary node data");
        abort();
    }

    // swap data
    memcpy(tmp->data, a->data, l->elementSize);
    memcpy(a->data, b->data, l->elementSize);
    memcpy(b->data, tmp->data, l->elementSize);

    // free temporary node
    free(tmp->data);
    free(tmp);
}

/**
 * dll_selectionSort:
 *  Selection sort that iterates the list using a node comparator function
 *  and swaps node data.
 */
void dll_selectionSort(dLinkedList *l, nodeComparator cmp)
{
    assert(cmp);

    // allocate three node pointers
    dLinkedListNode *start = l->head; // start at list head
    dLinkedListNode *curr, *min;

    while (start) {
        min = start;
        curr = start->next;

        // find the lowest value from start in the list
        while (curr) {
            if ((cmp(min->data, curr->data) > 0))
                min = curr;
            curr = curr->next;
        }

        // swap start with lowest value found
        dll_swapNodeData(l, start, min);
        start = start->next;    // move start node
    }
}
