#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "lists.h"
#include "errors.h"

void intDLinkedList();

/**
 * main:
 *      Program entry point.
 */
int main(int argc, char **argv)
{
    // Set up some signal handlers
    signal(SIGINT, sig_int);
    signal(SIGSEGV, sig_seg);

    // Run some tests
    printf("At each test press return/enter\n\n");
    intDLinkedList();
    exit(EXIT_SUCCESS);
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
    dll_foreach(l, iterFunc_exists, printInt);
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
    dll_foreach(l, iterFunc_exists, printInt);
    printf("Done...\n\n");

    printf("Test 10: Print list in reverse order without swapping node's...");
    getchar();
    printf("[");
    dLinkedListNode *curr = dll_last(l);
    while (curr) {
        printf(" %d ", *(int *) curr->data);
        curr = curr->prev;
    }
    printf("]\ndone....\n\n");

    printf("Test 11: Reverse the list by swapping node's...");
    getchar();
    dll_reverse(l);
    dll_foreach(l, iterFunc_exists, printInt);
    printf("Done...\n\n");

    printf("Test 12: Sort the list by swapping node data...");
    getchar();
    dll_selectionSort(l, compareInt);
    dll_foreach(l, iterFunc_exists, printInt);
    printf("Done...\n\n");

    printf("Test 13: Split the list in two...");
    getchar();
    dLinkedList *b = dll_split(l);
    printf("Second half:\n");
    dll_foreach(b, iterFunc_exists, printInt);
    printf("First half:\n");
    dll_foreach(l, iterFunc_exists, printInt);
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
