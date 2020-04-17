/** demo_2_str_ll.c - Deom of list linked string operations.

Copyright (c) 2020 Michael Berry

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
