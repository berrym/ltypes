/** linkedList.c - Linked list implementation.

Copyright (c) 2021 Michael Berry

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "lists.h"
#include "errors.h"

/**
 * ll_create:
 *      Create and initialize a singly linked list.
 *      Returns the list.
 */
linkedList *ll_create(size_t size, freeFunction fn)
{
    // Allocate list
    linkedList *l = calloc(1, sizeof(linkedList));
    if (!l)
        error_abort("Unable to allocate linkedList");

    // Initialize list
    l->logicalLength = 0;
    l->elementSize = size;
    l->head = l->tail = NULL;
    l->freeFn = fn;

    return l;                   // return new list
}

/**
 * ll_delete:
 *      Remove each node from a list.
 */
void ll_delete(linkedList *l)
{
    linkedListNode *curr;
    while (l->head) {
        curr = l->head;
        l->head = curr->next;

        // Free node
        if (l->freeFn)
            l->freeFn(curr->data);

        free(curr->data);
        free(curr);
        l->logicalLength--;     // decrease list's logical length
    }

    l->head = l->tail = NULL;   // reset list's head/tail
    free(l);
}

/**
 * ll_push:
 *      Push a new node to the front of a list.
 */
void ll_push(linkedList *l, void *el)
{
    // Allocate memory for a new list node
    linkedListNode *node = calloc(1, sizeof(linkedListNode));
    if (!node)
        error_abort("unable to allocate memory for node");

    // Allocate memory for node's new data
    if ((node->data = calloc(1, l->elementSize)) == NULL)
        error_abort("unable to allocate memory for node");

    // Copy new data to node
    memcpy(node->data, el, l->elementSize);
    node->next = l->head;
    l->head = node;             // reset list head
    l->logicalLength++;         // increase list's logical length
}

/**
 * ll_append:
 *      Append a new node to the end of a list.
 */
void ll_append(linkedList *l, void *el)
{
    // Allocate memory for a new list node
    linkedListNode *node = calloc(1, sizeof(linkedListNode));
    if (!node)
        error_abort("unable to allocate memory for node");

    // Allocate memory for node's new data
    if ((node->data = calloc(1, l->elementSize)) == NULL)
        error_abort("unable to allocate memory for node");

    // Copy new data into node
    memcpy(node->data, el, l->elementSize);

    // Reset head/tail links
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
 *      Insert a new node into a list after a given node.
 */
void ll_insertAfter(linkedList *l, linkedListNode *prev, void *data)
{
    assert(prev);

    // Use append method if prev is list tail
    if (prev == l->tail) {
        ll_append(l, data);
        return;
    }

    // Allocate memory for the new node
    linkedListNode *node = calloc(1, sizeof(linkedListNode));
    if (!node)
        error_abort("Unable to allocate memory for new node");

    // Allocate memory for the new node's data
    if (!(node->data = calloc(1, l->elementSize)))
        error_abort("unable to allocate memory for node");

    // Copy data
    memcpy(node->data, data, l->elementSize);

    // Set new node links
    node->next = prev->next;
    prev->next = node;
    l->logicalLength++;         // increase list's logical length
}

/**
 * ll_deleteNode:
 *      Delete a node from a list containing value `data`.
 */
void ll_deleteNode(linkedList *l, void *data, nodeComparator cmp)
{
    // Assert that a node compare function was provided
    assert(cmp);

    linkedListNode *entry = l->head, *prev = NULL;

    // Edge case where node to be deleted is the list's head
    if (entry && cmp(entry->data, data) == 0) {
        l->head = entry->next;

        if (l->freeFn)
            l->freeFn(entry->data);

        free(entry->data);
        free(entry);
        l->logicalLength--;     // decrease list's length

        return;
    }

    // Traverse the list looking for node to be deleted, if found remove it
    while (entry) {
        if (cmp(entry->data, data) == EQUAL) {
            prev->next = entry->next;

            if (l->freeFn)
                l->freeFn(entry->data);

            free(entry->data);
            free(entry);
            l->logicalLength--; // decrease list's length

            return;
        }

        // Move to next node
        prev = entry;
        entry = entry->next;
    }

    // Elegant way to remove a node but doesn't work on all platforms

    /* linkedListNode **pp = &l->head; // point pp to address of list head */
    /* linkedListNode *entry = l->head;// point entry to data of list head */

    /* // Traverse the list looking for the node to delete */
    /* while (entry) { */
    /*     if (cmp(entry->data, data) == 0) { // compare entry data to data */
    /*         if (l->freeFn) */
    /*             l->freeFn((*pp)->data); */

    /*         free((*pp)->data); */
    /*         free(*pp); */
    /*         *pp = entry->next;             // remove entry */
    /*         l->logicalLength--;            // decrease list's length */
    /*         return; */
    /*     } */

    /*     // Move to the next list entry */
    /*     pp = &entry->next; */
    /*     entry = entry->next; */
    /* } */
}

/**
 * ll_getNodeAt:
 *      Return node at given position in list.
 */
linkedListNode *ll_getNodeAt(linkedList *l, size_t index)
{
    // Return NULL if index given exceeds the list's length
    if (index > l->logicalLength)
        return NULL;

    linkedListNode *curr = l->head;
    size_t i;

    // Iterate over list looking for node at index
    for (i = 1; curr; i++) {
        if (i == index)
            return curr;

        curr = curr->next;
    }

    return NULL;                // node not found
}

/**
 * ll_search:
 *      Search a list for a node containing `data`.
 */
bool ll_search(linkedList *l, void *data, nodeComparator cmp)
{
    assert(cmp);

    linkedListNode *curr = l->head;

    // Traverse the list looking for a node matching `data`
    while (curr) {
        if (cmp(curr->data, data) == EQUAL)
            return true;

        curr = curr->next;
    }

    return false;
}

/**
 * ll_foreach:
 *      Iterate over a singly linked list and perform the tasks
 *      in the listIterator function on each node.
 */
void ll_foreach(linkedList *l, listIterator it, displayFunction display)
{
    // Assert that a list iterating function was passed
    assert(it);

    linkedListNode *node = l->head;
    bool result = true;

    // Iterate over the list
    while (node && result) {
        result = it(node->data, display);
        node = node->next;
    }
}

/**
 * ll_head:
 *      Return a copy of the head node's data of a singly linked list
 *      and optionally remove/pop it from the list.
 */
void ll_head(linkedList *l, void *el, bool remove)
{
    // Assert that the list is initialized
    assert(l->head);

    // Copy the list's head to a new element
    linkedListNode *node = l->head;
    memcpy(el, node->data, l->elementSize);

    // Remove/pop head node from list
    if (remove) {
        l->head = node->next;

        // Use freeFuction if it exists
        if (l->freeFn)
            l->freeFn(node->data);

        free(node->data);
        free(node);
        l->logicalLength--;     // increase list's logical length
    }
}

/**
 * ll_first:
 *      Return a pointer to the first node of the singly linked list.
 */
linkedListNode *ll_first(linkedList *l)
{
    return l->head;
}

/**
 * ll_tail:
 *      Return a copy of the tail node's data of a singly linked list.
 */
void ll_tail(linkedList *l, void *el)
{
    // Assert that the list is initialized
    assert(l->tail);

    // Copy the list's tail to a new element
    linkedListNode *node = l->tail;
    memcpy(el, node->data, l->elementSize);
}

/**
 * ll_last:
 *      Return a pointer to the tail node of a singly linked list.
 */
linkedListNode *ll_last(linkedList *l)
{
    return l->tail;
}

/**
 * ll_isEmpty:
 *      Return true if the singly linked list is empty, return false otherwise.
 */
bool ll_isEmpty(linkedList *l)
{
    return l->logicalLength == 0;
}

/**
 * ll_length:
 *      Rerturn the number of nodes in a singly linked list.
 */
size_t ll_length(linkedList *l)
{
    return l->logicalLength;
}

/**
 * ll_reverse:
 *      Reverse the node order of a singly linked list.
 */
void ll_reverse(linkedList *l)
{
    // Assert the list is initialized
    assert(l->head);

    linkedListNode *next = NULL;
    linkedListNode *prev = NULL;
    linkedListNode *curr = l->head;

    // Swap nodes
    while (curr) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }

    // Reset list head
    l->head = prev;
}

/**
 * ll_swapData:
 *      Swap the data of two node's in a list.
 */
void ll_swapNodeData(linkedList *l, linkedListNode *a, linkedListNode *b)
{
    // Allocate a temporary node
    linkedListNode *tmp = calloc(1, sizeof(linkedListNode));
    if (!tmp)
        error_abort("Unable to allocate memory for a temporary node");

    if (!(tmp->data = calloc(1, sizeof(l->elementSize))))
        error_abort("Unable to allocate memory for temporary node data");

    // Swap data
    memmove(tmp->data, a->data, l->elementSize);
    memmove(a->data, b->data, l->elementSize);
    memmove(b->data, tmp->data, l->elementSize);

    // Free temporary node
    free(tmp->data);
    free(tmp);
}

/**
 * ll_sort:
 *      Selection sort that iterates the list using a node comparator function
 *      and swaps node data.
 */
void ll_selectionSort(linkedList *l, nodeComparator cmp)
{
    assert(cmp);

    // Allocate three node pointers
    linkedListNode *start = l->head; // start at list head
    linkedListNode *curr, *min;

    while (start) {
        min = start;
        curr = start->next;

        // Find the lowest value from start in the list
        while (curr) {
            if ((cmp(min->data, curr->data) == GREATER))
                min = curr;
            curr = curr->next;
        }

        // Swap start with lowest value found
        ll_swapNodeData(l, start, min);
        start = start->next;    // move to next node
    }
}

/**
 * ll_split:
 *      Split a list into two halves.  If there is an odd number
 *      of node's in the original list it goes into the first half, the
 *      second half of the list is initialized and returned.
 */
linkedList *ll_split(linkedList *a)
{
    if (a->logicalLength <= 1)
        return NULL;

    // Split the list in two
    linkedListNode *fast = a->head, *slow = a->head;
    while (fast->next && fast->next->next) {
        fast = fast->next->next;
        slow = slow->next;
    }

    // Create and initialize a new list with the second half of the original
    linkedList *b = calloc(1, sizeof(linkedList));
    b->elementSize = a->elementSize;
    b->head = slow->next;
    slow->next = NULL;
    size_t b_len;
    linkedListNode *it = b->head;
    for (b_len = 0; it; b_len++) {
        b->tail = it;
        it = it->next;
    }
    b->logicalLength = b_len;
    size_t a_len;

    it = a->head;
    for (a_len = 0; it; a_len++) {
        it = it->next;
    }
    a->tail = it;
    a->logicalLength = a_len;

    return b;                   // return the second half of the list
}

/**
 * ll_hasCycle:
 *        Detect a cycle/loop in a linked list.
 */
linkedListNode *ll_hasCycle(linkedList *l)
{
    linkedListNode *slow = l->head, *fast = l->head;

    while (slow && fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;

        if (slow == fast)
            return slow;
    }

    return NULL;
}

/**
 * ll_removeCycle:
 *      Remove a cycle/loop in a linked list.
 */
void ll_removeCycle(linkedList *l, linkedListNode *cycle_node)
{
    linkedListNode *curr = l->head;

    while (curr != cycle_node->next)
        curr = curr->next;

    curr->next = NULL;
    l->tail = curr;
}

/**
 * ll_detectAndRemoveCycles:
 *      Detect and remove cycles/loops in a linked list.
 */
size_t ll_detectAndRemoveCycles(linkedList *l)
{
    size_t cycles = 0;
    linkedListNode *cycle_node = NULL;

    while ((cycle_node = ll_hasCycle(l))) {
        cycles++;
        ll_removeCycle(l, cycle_node);
    }

    return cycles;
}
