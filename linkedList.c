/**
 * linkedList.c
 *
 * Functions to manipulate a generic singly linked list that can handle
 * multiple types by use of type casting from void variable/function pointers.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "ltypes.h"

/**
 * ll_create:
 *      Initialize singly linked list.
 */
linkedList *ll_create(size_t size, freeFunction fn)
{
    // alloc list
    linkedList *l = calloc(1, sizeof(linkedList));
    if (!l) {
        perror("Unable to allocate linkedList");
        abort();
    }

    // initialize list
    l->logicalLength = 0;
    l->elementSize = size;
    l->head = l->tail = NULL;
    l->freeFn = fn;

    return l;
}

/**
 * ll_delete:
 *      Remove each node from a singly linked lsit.
 */
void ll_delete(linkedList *l)
{
    linkedListNode *curr;
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

    l->head = l->tail = NULL;   // reset list's head/tail
    free(l);
}

/**
 * ll_push:
 *  Push a new node to the front of a singly linked list.
 */
void ll_push(linkedList *l, void *el)
{
    // allocate memory for a new list node
    linkedListNode *node = calloc(1, sizeof(linkedListNode));
    if (!node) {
        perror("unable to allocate memory for node");
        abort();
    }

    // allocate memory for node's new data
    if ((node->data = calloc(1, l->elementSize)) == NULL) {
        perror("unable to allocate memory for node");
        abort();
    }

    // copy new data to node
    memcpy(node->data, el, l->elementSize);
    node->next = l->head;
    l->head = node;             // reset list head

    // first node?
    if (!l->tail)
        l->tail = l->head;

    l->logicalLength++;         // increase list's logical length
}

/**
 * ll_append:
 *  Append a new node to the end of a singly linked list.
 */
void ll_append(linkedList *l, void *el)
{
    // allocate memory for a new list node
    linkedListNode *node = calloc(1, sizeof(linkedListNode));
    if (!node) {
        perror("unable to allocate memory for node");
        abort();
    }

    // allocate memory for node's new data
    if ((node->data = calloc(1, l->elementSize)) == NULL) {
        perror("unable to allocate memory for node");
        abort();
    }

    // copy new data into node
    memcpy(node->data, el, l->elementSize);

    // reset head/tail links
    if (l->logicalLength == 0) {
        l->head = l->tail = node;
    } else {
        l->tail->next = node;
        l->tail = node;
        l->tail->next = NULL;
    }

    l->logicalLength++;         // increase list's logical length
}

/**
 * ll_insertAfter:
 *  Insert a new node into a singly linked list after a given node.
 */
void ll_insertAfter(linkedList *l, linkedListNode *prev, void *el)
{
    assert(prev);

    // Use append method if prev is list tail
    if (prev == l->tail) {
        ll_append(l, el);
        return;
    }

    // Allocate memory for the new node
    linkedListNode *node = calloc(1, sizeof(linkedListNode));
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
    l->logicalLength++;         // increase list's logical length
}

/**
 * ll_foreach:
 *  Iterate over a singly linked list and perform the tasks
 *  in the listIterator function on each node.
 */
void ll_foreach(linkedList *l, listIterator it)
{
    // assert that a list iterating function was passed
    assert(it);

    linkedListNode *node = l->head;
    bool result = true;

    // Iterate over the list, return on tail if the list is circular
    while (node && result) {
        result = it(node->data);
        node = node->next;
    }
}

/**
 * ll_head:
 *  Return a copy of the head node's data of a singly linked list
 *  and optionally remove/pop it from the list.
 */
void ll_head(linkedList *l, void *el, bool remove)
{
    // assert that the list is initialized
    assert(l->head);

    // copy the list's head to a new element
    linkedListNode *node = l->head;
    memcpy(el, node->data, l->elementSize);

    // remove/pop head node from list
    if (remove) {
        l->head = node->next;

        // use freeFuction if it exists
        if (l->freeFn)
            l->freeFn(node->data);

        free(node->data);
        free(node);
        l->logicalLength--;     // increase list's logical length
    }
}

/**
 * ll_first:
 *  Return a pointer to the first node of the singly linked list.
 */
linkedListNode *ll_first(linkedList *l)
{
    return l->head;
}

/**
 * ll_tail:
 *  Return a copy of the tail node's data of a singly linked list.
 */
void ll_tail(linkedList *l, void *el)
{
    // assert that the list is initialized
    assert(l->tail);

    // copy the list's tail to a new element
    linkedListNode *node = l->tail;
    memcpy(el, node->data, l->elementSize);
}

/**
 * ll_last:
 *  Return a pointer to the tail node of a singly linked list.
 */
linkedListNode *ll_last(linkedList *l)
{
    return l->tail;
}

/**
 * ll_isEmpty:
 *  Return true if the singly linked list is empty, return false otherwise.
 */
bool ll_isEmpty(linkedList *l)
{
    return l->logicalLength == 0;
}

/**
 * ll_length:
 *  Rerturn the number of nodes in a singly linked list.
 */
size_t ll_length(linkedList *l)
{
    return l->logicalLength;
}

/**
 * ll_reverse:
 *  Reverse the node order of a singly linked list.
 */
void ll_reverse(linkedList *l)
{
    // assert the list is initialized
    assert(l->head);

    linkedListNode *next;
    linkedListNode *prev = NULL;
    linkedListNode *curr = l->head;

    // swap nodes
    while (curr) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }

    // reset list head
    l->head = prev;
}

/**
 * ll_swapData:
 *  Swap the data of two node's in a singly linked list.
 */
void ll_swapNodeData(linkedList *l, linkedListNode *a, linkedListNode *b)
{
    // allocate a temporary node
    linkedListNode *tmp = calloc(1, sizeof(linkedListNode));
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
 * ll_sort:
 *  Selection sort that iterates the list using a node comparator function
 *  and swaps node data.
 */
void ll_selectionSort(linkedList *l, nodeComparator cmp)
{
    assert(cmp);

    // allocate three node pointers
    linkedListNode *start = l->head; // start at list head
    linkedListNode *curr, *min;

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
        ll_swapNodeData(l, start, min);
        start = start->next;    // move start node
    }
}

/**
 * ll_split:
 *  Split a linked list into two halves.  If there is an odd number
 *  of node's in the original list it goes into the first half, the
 *  second half of the list is initialized and returned.
 */
linkedList *ll_split(linkedList *a)
{
    if (a->logicalLength == 1)
        return NULL;

    // split the list in two
    linkedListNode *fast = a->head, *slow = a->head;
    while (fast->next && fast->next->next) {
        fast = fast->next->next;
        slow = slow->next;
        a->logicalLength--;     // decrease original list length
    }

    // create and initialize a new list with the second half of the original
    linkedList *b = calloc(1, sizeof(linkedList));
    b->elementSize = a->elementSize;
    b->head = slow->next;
    slow->next = NULL;
    size_t i;
    linkedListNode *it = b->head;
    for (i = 0; it; i++) {
        b->tail = it;
        it = it->next;
    }
    b->logicalLength = i;

    return b;                   // return the second half of the list
}
