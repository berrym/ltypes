/** demo_5_fibonacci_ll.c - Demo of an abritary length Fibonacci series.

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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <stdbool.h>
#include <assert.h>
#include "lists.h"
#include "errors.h"

linkedList *fib_to_n(size_t);

/**
 * main:
 *      Main function, program entry point.
 */
int main(int argc, char **argv)
{
    char *line = NULL;
    size_t len;
    ssize_t nread;
    linkedList *fibs = NULL;

    printf("Fibonacci Sequence\nHow many numbers do you want? 30 is max: ");
    if ((nread = getline(&line, &len, stdin)) == -1)
        error_syscall("getline failed");

    size_t n = atoi(line);

    if (n <= 30) {
        fibs = fib_to_n(n);
    } else if (n > 30) {
        printf("Number to large.\n");
        exit(EXIT_SUCCESS);
    } else {
        printf("Unknown input.\n");
        exit(EXIT_FAILURE);
    }

    ll_foreach(fibs, iterFunc_exists, printInt);
    printf("\n");
    ll_delete(fibs);

    return 0;
}

/**
 * fib_to_n:
 *      Calculate the Fibonacci series up to limit.
 */
linkedList *fib_to_n(size_t limit)
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

