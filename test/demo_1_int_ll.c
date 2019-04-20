#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "lists.h"
#include "errors.h"

void intLinkedList();

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
    intLinkedList();
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
    ll_foreach(l, iterFunc_exists, printInt);
    printf("Done\n\n");

    printf("Test 6: Iterate over list and print values found...");
    getchar();
    ll_foreach(l, iterFunc_exists, printInt);
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
    ll_foreach(l, iterFunc_exists, printInt);
    printf("Done...\n\n");

    printf("Test 9: Reversing list by swapping nodes...");
    getchar();
    ll_reverse(l);
    ll_foreach(l, iterFunc_exists, printInt);
    printf("Done...\n\n");

    printf("Test 10: Sort list by swapping node data...");
    getchar();
    ll_selectionSort(l, compareInt);
    ll_foreach(l, iterFunc_exists, printInt);
    printf("Done...\n\n");

    printf("Test 11: Split the list in two...");
    getchar();
    linkedList *b = ll_split(l);
    printf("Second half:\n");
    ll_foreach(b, iterFunc_exists, printInt);
    printf("First half:\n");
    ll_foreach(l, iterFunc_exists, printInt);
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
