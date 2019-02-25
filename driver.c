/**
 * driver.c
 *
 * Small driver program to test singly/doubly linked list library code.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ltypes.h"

void intLinkedList();
void printReverseIntLinkedList(linkedListNode *);
void intDLinkedList();
bool iterateIntList(void *);
void stringLinkedList();
void stringDLinkedList();
bool iterateStringList(void *);
void freeString(void *);
int compareInt(const void *, const void *);

/**
 * main:
 *      Program entry point.
 */
int main(int argc, char **argv)
{
    printf("At each test press return/enter\n\n");
    intLinkedList();
    intDLinkedList();
    stringLinkedList();
    stringDLinkedList();

    exit(EXIT_SUCCESS);
}

/**
 * intLinkedList:
 *      Series of operations on a singly linked list as tests.
 */
void intLinkedList()
{
    printf("==== TEST SINGLY LINKED INTEGER LIST  ====.\n\n");

    size_t len = 10;
    printf("Test 1: Create list with first %zu positive integers...", len);
    getchar();
    linkedList *l = ll_create(sizeof(int), NULL);
    size_t i;
    for (i = 1; i <= len; i++)
        ll_append(l, &i);
    printf("Done...\n\n");

    printf("Test 2: Push a number (0) to the front of the list...");
    getchar();
    i = 0;
    ll_push(l, &i);
    printf("Done...\n\n");

    printf("Test 3: Get value at index 9...");
    getchar();
    linkedListNode *temp = ll_getNodeAt(l, 9);
    printf("Value at index 9: %d\nDone...\n\n", *(int *)temp->data);

    printf("Test 4: Search for value (7) in the list...");
    getchar();
    bool result;
    int data = 7;
    result = ll_search(l, &data, compareInt);
    if (result)
        printf("Value 7 found.\n");
    else
        printf("Value 7 not found.\n");
    printf("Done...\n\n");

    printf("Test 5: Delete value 7...");
    getchar();
    ll_deleteNode(l, &data, compareInt);
    ll_foreach(l, iterateIntList);
    printf("Done\n\n");

    printf("Test 6: Iterate over list and print values found...");
    getchar();
    ll_foreach(l, iterateIntList);
    printf("Done...\n\n");
    
    printf("Test 7: Print list in reverse order without swapping nodes...");
    getchar();
    printf("[");
    printReverseIntLinkedList(ll_first(l));
    printf("]\n");
    printf("Done...\n\n");

    printf("Test 8: Swap head and tail data...");
    getchar();
    ll_swapNodeData(l, ll_first(l), ll_last(l));
    ll_foreach(l, iterateIntList);
    printf("Done...\n\n");

    printf("Test 9: Reversing list by swapping nodes...");
    getchar();
    ll_reverse(l);
    ll_foreach(l, iterateIntList);
    printf("Done...\n\n");

    printf("Test 10: Sort list by swapping node data...");
    getchar();
    ll_selectionSort(l, compareInt);
    ll_foreach(l, iterateIntList);
    printf("Done...\n\n");

    printf("Test 11: Split the list in two...");
    getchar();
    linkedList *b = ll_split(l);
    printf("Second half:\n");
    ll_foreach(b, iterateIntList);
    printf("First half:\n");
    ll_foreach(l, iterateIntList);
    printf("Done...\n\n");

    printf("Test 12: Delete the lists...");
    getchar();
    printf("Deleting first half of original list:\n");
    len = l->logicalLength;
    ll_delete(l);
    printf("Successfully freed %zu numbers...\n\n", len);
    printf("Deleting second half of original list.\n");
    len = b->logicalLength;
    ll_delete(b);
    printf("Successfully freed %zu numbers...\n\n", len);
}

/**
 * printreverseintlinkedList:
 *      Print a linked list in reverse order using reursion.
 */
void printReverseIntLinkedList(linkedListNode *head)
{
    if (!head)
        return;
    printReverseIntLinkedList(head->next);
    printf(" %d ", *(int *)head->data);
}

/**
 * intDlinkedList:
 *      Series of operations on a doubly linked list as tests.
 */
void intDLinkedList()
{
    printf("==== TEST DOUBLY LINKED INTEGER LIST ====\n\n");

    size_t len = 10;

    printf("Test 1: Create a list with first %zu positive integers...", len);
    getchar();
    size_t i;
    dLinkedList *l = dll_create(sizeof(int), NULL);
    for (i = 1; i <= len; i++)
        dll_append(l, &i);
    printf("Done...\n\n");

    printf("Test 2: Push a number (0), to the front of the list...");
    getchar();
    i = 0;
    dll_push(l, &i);
    printf("Done...\n\n");

    printf("Test 3: Get value at index 9...");
    dLinkedListNode *temp = dll_getNodeAt(l, 9);
    printf("Value at index 9: %d\nDone...\n\n", *(int *)temp->data);

    printf("Test 4: Search for value (7) in list...");
    bool result;
    int data = 7;
    result = dll_search(l, &data, compareInt);
    if (result)
        printf("Value 7 found.\n");
    else
        printf("Value 7 not found.\n");
    printf("Done...\n\n");

    printf("Test 5: Delete value 7...");
    getchar();
    dll_deleteNode(l, &data, compareInt);
    dll_foreach(l, iterateIntList);
    printf("Done\n\n");

    printf("Test 6: Insert a number (11) after the begining of the list...");
    getchar();
    i = 11;
    dll_insertAfter(l, dll_first(l), &i);
    printf("Done...\n\n");

    printf("Test 7: Insert a number (12) before the end of the list...");
    getchar();
    i = 12;
    dll_insertBefore(l, dll_last(l), &i);
    printf("Done...\n\n");

    printf("Test 8: Swap the list's head and tail data...");
    getchar();
    dll_swapNodeData(l, dll_first(l), dll_last(l));
    printf("Done.\n\n");

    printf("Test 9: Iterate over list and print values found...");
    getchar();
    dll_foreach(l, iterateIntList);
    printf("Done...\n\n");

    printf("Test 10: Print list in reverse order without swapping node's...");
    getchar();
    printf("[");
    dLinkedListNode *curr = dll_last(l);
    while (curr) {
        printf(" %d ", *(int *)curr->data);
        curr = curr->prev;
    }
    printf("]\ndone....\n\n");

    printf("Test 11: Reverse the list by swapping node's...");
    getchar();
    dll_reverse(l);
    dll_foreach(l, iterateIntList);
    printf("Done...\n\n");

    printf("Test 12: Sort the list by swapping node data...");
    getchar();
    dll_selectionSort(l, compareInt);
    dll_foreach(l, iterateIntList);
    printf("Done...\n\n");

    printf("Test 13: Split the list in two...");
    getchar();
    dLinkedList *b = dll_split(l);
    printf("Second half:\n");
    dll_foreach(b, iterateIntList);
    printf("First half:\n");
    dll_foreach(l, iterateIntList);
    printf("Done...\n\n");

    printf("Test 14: Delete the lists...");
    getchar();
    len = dll_length(l);
    printf("Deleting first half of list...\n");
    dll_delete(l);
    printf("Successfully freed %zu numbers...\n\n", len);
    len = dll_length(b);
    dll_delete(b);
    printf("Successfully freed %zu numbers...\n\n", len);
}

/**
 * iterateIntList:
 *      Boolean check of data existence, used in foreach operation.
 */
bool iterateIntList(void *data)
{
    if (data) {
        printf("Found value: %d\n", *(int *)data);
        return true;
    }
    return false;
}

/**
 * stringLinkedList:
 *      Series of operations on a singly linked list of strings as tests.
 */
void stringLinkedList()
{
    printf("==== TEST SINGLY LINKED STRING LIST ====\n\n");

    size_t len = 9;
    printf("Test 1: Generate list of with first 9 Fibonacci numbers...");
    getchar();
    const char *strings[] = { "one",
                              "one",
                              "two",
                              "three",
                              "five",
                              "eight",
                              "eleven",
                              "nineteen",
                              "thirty"
    };
    linkedList *l = ll_create(sizeof(char *), freeString);
    size_t i;
    char *s;
    for (i=0; i < len; i++) {
        s = strdup(strings[i]);
        ll_append(l, &s);
    }
    printf("Done...\n\n");

    printf("Test 2: Push string 'zero' to the list...");
    getchar();
    s = strdup("zero");
    ll_push(l, &s);
    len = ll_length(l);
    printf("Done...\n\n");

    printf("Test 3: Iterate over list and print values found...");
    getchar();
    ll_foreach(l, iterateStringList);
    printf("Done...\n\n");

    printf("Test 4: Swap head and tail data of list...");
    getchar();
    ll_swapNodeData(l, ll_first(l), ll_last(l));
    printf("Done.\n\n");

    printf("Test 5: Iterate over list and print values found...");
    getchar();
    ll_foreach(l, iterateStringList);
    printf("Done...\n\n");

    printf("Test 6: Reverse list by swapping nodes...");
    getchar();
    ll_reverse(l);
    ll_foreach(l, iterateStringList);
    printf("Done...\n\n");

    printf("Test 7: Delete list...");
    getchar();
    ll_delete(l);
    printf("Sucessfully free'd %zu strings\n\n", len);
}

/**
 * stringDLinkedList:
 *      Series of operations on a doubly linked list of strings as tests.
 */
void stringDLinkedList()
{
    printf("==== TESTING DOUBLY LINKED STRING LIST ====\n\n");

    size_t len = 9;

    printf("Test 1: Generating a list with first 9 Fibonacci numbers...");
    getchar();
    const char *strings[] = { "one",
                              "one",
                              "two",
                              "three",
                              "five",
                              "eight",
                              "eleven",
                              "nineteen",
                              "thirty"
    };
    dLinkedList *l = dll_create(sizeof(char *), freeString);
    size_t i;
    char *s;
    for (i=0; i < len; i++) {
        s = strdup(strings[i]);
        dll_append(l, &s);
    }
    printf("Done...\n\n");

    printf("Test 2: Push a string 'zero' to the list...\n");
    getchar();
    s = strdup("zero");
    dll_push(l, &s);
    len = l->logicalLength;
    printf("Done...\n\n");

    printf("Test 3: Iterate over list and print values found...");
    getchar();
    dll_foreach(l, iterateStringList);
    printf("Done...\n\n");

    printf("Test 4: Reverse order of list by swapping nodes...");
    getchar();
    dll_reverse(l);
    dll_foreach(l, iterateStringList);
    printf("Done...\n\n");

    printf("Test 5: Delete list...");
    getchar();
    dll_delete(l);
    printf("Sucessfully free'd %zu strings\n\n", len);
}

/**
 * iteratestringList:
 *      Boolean test to check if data exists in node, used in foreach operation.
 */
bool iterateStringList(void *data)
{
    if (data) {
        printf("Found string value: %s\n", *(char **)data);
        return true;
    }
    return false;
}

/**
 * freeString:
 *      Free string data.
 */
void freeString(void *data)
{
    if (data)
        free(*(char **)data);
}

/**
 * compareInt:
 *      Compare two integers for equality.
 *      Results are -1 for a < b, 0 for a == b, 1 for a > b
 */
int compareInt(const void *a, const void *b)
{
    const int ia = *(const int *)a;
    const int ib = *(const int *)b;
    return (ia > ib) - (ia < ib);
}
