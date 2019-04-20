#define _DEFAULT_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include "lists.h"
#include "errors.h"

void stringLinkedList();

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
    stringLinkedList();
    exit(EXIT_SUCCESS);
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
    ll_foreach(l, iterFunc_exists, printStr);
    printf("Done...\n\n");

    printf("Test 4: Swap head and tail data of list...");
    getchar();
    ll_swapNodeData(l, ll_first(l), ll_last(l));
    printf("Done.\n\n");

    printf("Test 5: Iterate over list and print values found...");
    getchar();
    ll_foreach(l, iterFunc_exists, printStr);
    printf("Done...\n\n");

    printf("Test 6: Reverse list by swapping nodes...");
    getchar();
    ll_reverse(l);
    ll_foreach(l, iterFunc_exists, printStr);
    printf("Done...\n\n");

    printf("Test 7: Delete list...");
    getchar();
    ll_delete(l);
    printf("Sucessfully free'd %zu strings\n\n", len);
}
