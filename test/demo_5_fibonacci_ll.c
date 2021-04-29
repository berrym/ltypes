/** demo_5_fibonacci_ll.c - Demo of an abritary length Fibonacci series.

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
#include <errno.h>
#include <limits.h>
#include <signal.h>
#include "lists.h"
#include "errors.h"

linkedList *fibToLimit(size_t);

#define MAXGEN 30

/**
 * main:
 *      Main function, program entry point.
 */
int main(int argc, char **argv)
{
    char *line = NULL, *endptr = NULL;
    size_t len;
    ssize_t nread;
    linkedList *fibs = NULL;

    // Set up some signal handlers
    signal(SIGINT, sig_int);
    signal(SIGSEGV, sig_seg);

    printf("Fibonacci Sequence\nHow many numbers do you want? %d is max: ", MAXGEN);
    if ((nread = getline(&line, &len, stdin)) == -1)
        error_syscall("getline failed");

    errno = 0;
    size_t n = strtol(line, &endptr, 10);

    if (errno != 0)
        error_syscall("strtol failed");

    if (line == endptr) {
        fprintf(stderr, "No digitis were found\n\n");
        exit(EXIT_FAILURE);
    }

    if (n <= MAXGEN) {
        fibs = fibToLimit(n);
    } else {
        printf("Number to large.\n");
        exit(EXIT_SUCCESS);
    }

    ll_foreach(fibs, iterFunc_exists, printInt);
    printf("\n");

    ll_detectAndRemoveCycles(fibs);

    ll_delete(fibs);

    return 0;
}

/**
 * fibToLimit:
 *      Calculate the Fibonacci series up to limit.
 */
linkedList *fibToLimit(size_t limit)
{
    linkedList *fibs = ll_create(sizeof(int), NULL);
    int a, b, c;
    a = 0;
    b = 1;
    for (size_t i = 2; i <= limit; i++) {
        c = a + b;
        a = b;
        b = c;
        ll_append(fibs, &b);
    }

    return fibs;
}

