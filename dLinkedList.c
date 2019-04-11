/**
 * dLinkedList.c
 *
 * Functions to manipulate a generic doubly linked list that can handle
 * multiple types by use of type casting from void variable/function pointers.
 *
 * Copyright (c) 2019 Michael Berry <trismegustis@gmail.com>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "lists.h"
#include "errors.h"

/**
 * dll_create:
 *      Create and initialize a doubly linked list.
 *      Returns the list.
 */
dLinkedList *dll_create(size_t size, freeFunction fn)
{
    // Allocate list
    dLinkedList *l = calloc(1, sizeof(dLinkedList));
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
 * dll_delete:
 *      Remove each node from a list.
 */
void dll_delete(dLinkedList *l)
{
    dLinkedListNode *curr;

    // Traverse list and delete each node
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

    // Free list
    l->head = l->tail = NULL;   // reset list head/tail
    free(l);
}

/**
 * dll_push:
 *      Push a new node to the front of a list.
 */
void dll_push(dLinkedList *l, void *el)
{
    // Allocate memory for new list node
    dLinkedListNode *node = calloc(1, sizeof(dLinkedListNode));
    if (!node)
        error_abort("unable to allocate memory for node");

    node->prev = NULL;

    // Allocate memory for new node's data
    if ((node->data = calloc(1, l->elementSize)) == NULL)
        error_abort("unable to allocate memory for node");

    // Copy new data to node
    memcpy(node->data, el, l->elementSize);

    // Set node as new list head
    node->next = l->head;
    l->head ->prev = node;
    l->head = node;
    l->logicalLength++;         // increase list's logical length
}

/**
 * dll_append:
 *      Append a new node to the end of a list.
 */
void dll_append(dLinkedList *l, void *el)
{
    // Allocate memory for a new node
    dLinkedListNode *node = calloc(1, sizeof(dLinkedListNode));
    if (!node)
        error_abort("unable to allocate memory for node");

    // Allocate memory for the new node's data
    if ((node->data = calloc(1, l->elementSize)) == NULL)
        error_abort("unable to allocate memory for node");

    // Copy data into node
    memcpy(node->data, el, l->elementSize);

    // Reset node links
    if (l->logicalLength == 0) { // empty list
        l->head = l->tail = node;
        l->head->prev = l->tail->next = NULL;
        l->tail->prev = l->head;
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
 *      Insert a new node into a list after a given node.
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
    if (!node)
        error_abort("Unable to allocate memory for new node");

    // Allocate memory for the new node's data
    if (!(node->data = calloc(1, l->elementSize)))
        error_abort("unable to allocate memory for node");

    // Copy data into node
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
 *      Insert a new node before a given node.
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
    if (!node)
        error_abort("Unable to allocate memory for new node");

    // Allocate memory for the new node's data
    if (!(node->data = calloc(1, l->elementSize)))
        error_abort("unable to allocate memory for node");

    // Copy data into node
    memcpy(node->data, el, l->elementSize); // copy data

    // Set new node links
    node->prev = next->prev;
    next->prev = node;
    node->next = next;
    node->prev->next = node;
    l->logicalLength++;         // increase list's logical length
}

/**
 * dll_deleteNode:
 *      Delete a node from a list containing value `data`.
 */
void dll_deleteNode(dLinkedList *l, void *data, nodeComparator cmp)
{
    // Assert that a node compare function was provided
    assert(cmp);

    dLinkedListNode *entry = l->head; // point entry to contents of list head

    // Traverse the list looking for the node to delete
    while (entry) {
        if (cmp(entry->data, data) == EQUAL) { // compare entry data to data
            // Reset node links
            if (entry == l->head)
                entry = entry->next;
            if (entry->next)
                entry->next->prev = entry->prev;
            if (entry->prev)
                entry->prev->next = entry->next;

            // Free node data and node itself
            if (l->freeFn)
                l->freeFn(entry->data);
            free(entry->data);
            free(entry);        // remove entry
            l->logicalLength--; // decrease list's length

            return;
        }

        // Move to the next list entry
        entry = entry->next;
    }
}

/**
 * dll_getNodeAt:
 *      Return node at given position in list.
 */
dLinkedListNode *dll_getNodeAt(dLinkedList *l, size_t index)
{
    // Return NULL if index given exceeds the list's length
    if (index > l->logicalLength)
        return NULL;

    dLinkedListNode *curr = l->head;
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
 * dll_search:
 *      Search a list for a node containing `data`.
 */
bool dll_search(dLinkedList *l, void *data, nodeComparator cmp)
{
    assert(cmp);

    dLinkedListNode *curr = l->head;

    // Traverse the list looking for a node matching `data`.
    while (curr) {
        if (cmp(curr->data, data) == EQUAL)
            return true;

        curr = curr->next;
    }

    return false;
}

/**
 * dll_foreach:
 *      Iterate over a list and perform the tasks
 *      in the listIterator function on each node.
 */
void dll_foreach(dLinkedList *l, listIterator it, displayFunction display)
{
    // Assert that a list iterating function was passed
    assert(it);

    bool result = true;
    dLinkedListNode *node = l->head;

    // Iterate over the list
    while (node && result) {
        result = it(node->data, display);
        node = node->next;
    }
}

/**
 * dll_head:
 *      Return a copy of the head of a list's head and optionally
 *      remove/pop it from the list.
 */
void dll_head(dLinkedList *l, void *el, bool remove)
{
    // Assert that the list is initialized
    assert(l->head);

    // Copy the list's head to a new element
    dLinkedListNode *node = l->head;
    memcpy(el, node->data, l->elementSize);

    // Remove/pop head node from list
    if (remove) {
        l->head = node->next;

        // Use freeFunction if it exists
        if (l->freeFn)
            l->freeFn(node->data);

        free(node->data);
        free(node);
        l->logicalLength--;     // decrease list's logical length
    }
}

/**
 * dll_first:
 *      Return a pointer to head node of the list.
 */
dLinkedListNode *dll_first(dLinkedList *l)
{
    return l->head;
}

/**
 * dll_tail:
 *      Return a copy of the tail node of a list.
 */
void dll_tail(dLinkedList *l, void *el)
{
    // Assert that the list is initialized
    assert(l->tail);

    // Copy the list's tail to a new element
    dLinkedListNode *node = l->tail;
    memcpy(el, node->data, l->elementSize);
}

/**
 * dll_last:
 *      Return a pointer to the tail node of the list.
 */
dLinkedListNode *dll_last(dLinkedList *l)
{
    return l->tail;
}

/**
 * dll_isEmpty:
 *      Return true if the list is empty, return false otherwise.
 */
bool dll_isEmpty(dLinkedList *l)
{
    return l->logicalLength == 0;
}

/**
 * dll_length:
 *      Rerturn the number of nodes in a list.
 */
size_t dll_length(dLinkedList *l)
{
    return l->logicalLength;
}

/**
 * dll_reverse:
 *      Reverse the node order of a list.
 */
void dll_reverse(dLinkedList *l)
{
    dLinkedListNode *curr = l->head, *temp = NULL;

    // Reset node links
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
 *      Swap the data of two node's in a list.
 */
void dll_swapNodeData(dLinkedList *l, dLinkedListNode *a, dLinkedListNode *b)
{
    // Allocate a temporary node
    dLinkedListNode *temp = calloc(1, sizeof(dLinkedListNode));
    if (!temp)
        error_abort("Unable to allocate memory for a temporary node");

    if (!(temp->data = calloc(1, sizeof(l->elementSize))))
        error_abort("Unable to allocate memory for temporary node data");

    // Swap data
    memmove(temp->data, a->data, l->elementSize);
    memmove(a->data, b->data, l->elementSize);
    memmove(b->data, temp->data, l->elementSize);

    // Free temporary node
    free(temp->data);
    free(temp);
}

/**
 * dll_selectionSort:
 *      Selection sort that iterates the list using a node comparator function
 *      and swaps node data.
 */
void dll_selectionSort(dLinkedList *l, nodeComparator cmp)
{
    assert(cmp);

    // Allocate three node pointers
    dLinkedListNode *start = l->head; // start at list head
    dLinkedListNode *curr = NULL, *min = NULL;

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
        dll_swapNodeData(l, start, min);
        start = start->next;    // move start node
    }
}

/**
 * dll_split:
 *      Split a list into two halves.  If there is an odd number
 *      of node's in the original list it goes into the first half, the
 *      second half of the list is initialized and returned.
 */
dLinkedList *dll_split(dLinkedList *a)
{
    // Check that the list's length is greater than 1
    if (a->logicalLength <= 1)
        return NULL;

    // Split the list in two
    dLinkedListNode *fast = a->head, *slow = a->head;
    while (fast->next && fast->next->next) {
        fast = fast->next->next;
        slow = slow->next;
        a->logicalLength--;
    }

    // Create and initialize a new list with the second half of the original
    dLinkedList *b = calloc(1, sizeof(dLinkedList));
    if (!b)
        error_abort("Unable to allocate dLinkedList");

    b->elementSize = a->elementSize;
    b->head = slow->next;
    slow->next = NULL;

    size_t i;
    dLinkedListNode *it = b->head;
    for (i = 0; it; i++) {
        b->tail = it;
        it = it->next;
    }
    b->logicalLength = i;

    return b;                   // return the second half of the list
}
