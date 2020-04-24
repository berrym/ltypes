/** demo_6_primes_ll.c - Demo of an abritary amount of prime numbers.

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
#include "lists.h"
#include "errors.h"

void printDigit(const void *);
linkedList *primes_to_n(size_t);

#define MAXGEN 100

/**
 * main:
 *      Main function, program entry point.
 */
int main(int argc, char **argv)
{
    char *line = NULL;
    size_t len;
    ssize_t nread;
    linkedList *primes = NULL;

    printf("Prime numbers\n");
    printf("How many numbers do you want? %d is max: ", MAXGEN);
    if ((nread = getline(&line, &len, stdin)) == -1)
        error_syscall("getline failed");

    size_t n = atoi(line);

    if (n <= MAXGEN) {
        primes = primes_to_n(n);
    } else if (n > MAXGEN) {
        printf("Number too large.\n");
        exit(EXIT_SUCCESS);
    } else {
        printf("Unknown input.\n");
        exit(EXIT_FAILURE);
    }

    ll_foreach(primes, iterFunc_exists, printDigit);
    printf("\n");
    ll_delete(primes);

    return 0;
}
/**
 * printDigit:
 *      Display function to print an integer.
 */
void printDigit(const void *data)
{
    printf("%d ", *(int *)data);
}

/**
 * prime_to_n:
 *      Calculate prime numbers up to limit.
 */
linkedList *primes_to_n(size_t limit)
{
    linkedList *primes = ll_create(sizeof(int), NULL);

    size_t p = 3, c;

    for (size_t count = 2 ; count <= limit ;  ) {
        for (c = 2 ; c <= p - 1 ; c++)
            if (p % c == 0 )
                break;
        
        if (c == p) {
            ll_append(primes, &p);
            count++;
        }

        p++;
    }

    return primes;
}

