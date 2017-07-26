#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
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

int main(int argc, char **argv)
{
    printf("At each test press return/enter\n\n");
    intLinkedList();
    intDLinkedList();
    stringLinkedList();
    stringDLinkedList();

    exit(EXIT_SUCCESS);
}

void intLinkedList()
{
    printf("==== TEST SINGLY LINKED INTEGER LIST  ====.\n\n");

    size_t len = 10;

    printf("Test 1: Create list with %zu positive numbers...", len);
    getchar();
    size_t i;
    linkedList l;
    ll_create(&l, sizeof(int), NULL);
    for (i = 1; i <= len; i++)
        ll_append(&l, &i);
    printf("Done...\n\n");

    printf("Test 2: Push a number (0) to the front of the list...");
    getchar();
    i = 0;
    ll_push(&l, &i);
    len = ll_length(&l);
    printf("Done...\n\n");

    printf("Test 3: Iterate over list and print values found...");
    getchar();
    ll_foreach(&l, iterateIntList);
    printf("Done...\n\n");
    
    printf("Test 4: Print list in reverse order without swapping nodes...");
    getchar();
    printf("[");
    printReverseIntLinkedList(ll_first(&l));
    printf("]\n");
    printf("Done...\n\n");

    printf("Test 5: Swap head and tail data...");
    getchar();
    ll_swapNodeData(&l, ll_first(&l), ll_last(&l));
    ll_foreach(&l, iterateIntList);
    printf("Done...\n\n");

    printf("Test 6: Reversing list by swapping nodes...");
    getchar();
    ll_reverse(&l);
    ll_foreach(&l, iterateIntList);
    printf("Done...\n\n");

    printf("Test 7: Sort list by swapping node data...");
    getchar();
    ll_selectionSort(&l, compareInt);
    ll_foreach(&l, iterateIntList);
    printf("Done...\n\n");

    printf("Test 8: Deleting list...");
    getchar();
    ll_delete(&l);
    printf("Successfully freed %zu numbers...\n\n", len);
}

void printReverseIntLinkedList(linkedListNode *head)
{
    if (!head)
        return;
    printReverseIntLinkedList(head->next);
    printf(" %d ", *(int *)head->data);
}

void intDLinkedList()
{
    printf("==== TEST DOUBLY LINKED INTEGER LIST ====\n\n");

    size_t len = 10;

    printf("Test 1: Create a list with %zu positive numbers...", len);
    getchar();
    int i;
    dLinkedList l;
    dll_create(&l, sizeof(int), NULL);
    for (i = 1; i <= len; i++)
        dll_append(&l, &i);
    printf("Done...\n\n");

    printf("Test 2: Push a number (0), to the front of the list...");
    getchar();
    i = 0;
    dll_push(&l, &i);
    printf("Done...\n\n");

    printf("Test 3: Insert a number (11) after the begining of the list...");
    getchar();
    i = 11;
    dll_insertAfter(&l, dll_first(&l), &i);
    printf("Done...\n\n");

    printf("Test 4: Insert a number (12) before the end of the list...");
    getchar();
    i = 12;
    dll_insertBefore(&l, dll_last(&l), &i);
    printf("Done...\n\n");

    printf("Test 5: Swap the list's head and tail data...");
    getchar();
    dll_swapNodeData(&l, dll_first(&l), dll_last(&l));
    printf("Done.\n\n");

    printf("Test 6: Iterate over list and print values found...");
    getchar();
    dll_foreach(&l, iterateIntList);
    printf("Done...\n\n");

    printf("Test 7: Print list in reverse order without swapping node's...");
    getchar();
    printf("[");
    dLinkedListNode *curr = dll_last(&l);
    while (curr) {
        printf(" %d ", *(int *)curr->data);
        curr = curr->prev;
    }
    printf("]\ndone....\n\n");

    printf("Test 8: Reverse the list by swapping node's...");
    getchar();
    dll_reverse(&l);
    dll_foreach(&l, iterateIntList);
    printf("Done...\n\n");

    printf("Test 9: Sort the list by swapping node data...");
    getchar();
    dll_selectionSort(&l, compareInt);
    dll_foreach(&l, iterateIntList);
    printf("Done...\n\n");

    printf("Test 10: Delete the list...");
    getchar();
    len = dll_length(&l);
    printf("Deleting list...\n");
    dll_delete(&l);
    printf("Successfully freed %zu numbers...\n\n", len);
}

bool iterateIntList(void *data)
{
    printf("Found value: %d\n", *(int *)data);
    return true;
}

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
    linkedList l;
    ll_create(&l, sizeof(char *), freeString);
    size_t i;
    char *s;
    for (i=0; i < len; i++) {
        s = strdup(strings[i]);
        ll_append(&l, &s);
    }
    printf("Done...\n\n");

    printf("Test 2: Push string 'zero' to the list...");
    getchar();
    s = strdup("zero");
    ll_push(&l, &s);
    len = l.logicalLength;
    printf("Done...\n\n");

    printf("Test 3: Iterate over list and print values found...");
    getchar();
    ll_foreach(&l, iterateStringList);
    printf("Done...\n\n");

    printf("Test 4: Swap head and tail data of list...");
    getchar();
    ll_swapNodeData(&l, ll_first(&l), ll_last(&l));
    printf("Done.\n\n");

    printf("Test 5: Iterate over list and print values found...");
    getchar();
    ll_foreach(&l, iterateStringList);
    printf("Done...\n\n");

    printf("Test 6: Reverse list by swapping nodes...");
    getchar();
    ll_reverse(&l);
    ll_foreach(&l, iterateStringList);
    printf("Done...\n\n");

    printf("Test 7: Delete list...");
    getchar();
    ll_delete(&l);
    printf("Sucessfully free'd %zu strings\n\n", len);
}

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
    dLinkedList l;
    dll_create(&l, sizeof(char *), freeString);
    size_t i;
    char *s;
    for (i=0; i < len; i++) {
        s = strdup(strings[i]);
        dll_append(&l, &s);
    }
    printf("Done...\n\n");

    printf("Test 2: Push a string 'zero' to the list...\n");
    getchar();
    s = strdup("zero");
    dll_push(&l, &s);
    len = l.logicalLength;
    printf("Done...\n\n");

    printf("Test 3: Iterate over list and print values found...");
    getchar();
    dll_foreach(&l, iterateStringList);
    printf("Done...\n\n");

    printf("Test 4: Reverse order of list by swapping nodes...");
    getchar();
    dll_reverse(&l);
    dll_foreach(&l, iterateStringList);
    printf("Done...\n\n");

    printf("Test 5: Delete list...");
    getchar();
    dll_delete(&l);
    printf("Sucessfully free'd %zu strings\n\n", len);
}

bool iterateStringList(void *data)
{
    printf("Found string value: %s\n", *(char **)data);
    return true;
}

void freeString(void *data)
{
    if (data)
        free(*(char **)data);
}

int compareInt(const void *a, const void *b)
{
    const int ia = *(const int *)a;
    const int ib = *(const int *)b;
    return (ia > ib) - (ia < ib);
}
