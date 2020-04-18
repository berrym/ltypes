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

linkedList *primes_to_n(size_t);

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

    printf("Prime numbers\nHow many numbers do you want? 30 is max: ");
    if ((nread = getline(&line, &len, stdin)) == -1)
        error_syscall("getline failed");

    size_t n = atoi(line);

    if (n <= 30) {
        primes = primes_to_n(n);
    } else if (n > 30) {
        printf("Number to large.\n");
        exit(EXIT_SUCCESS);
    } else {
        printf("Unknown input.\n");
        exit(EXIT_FAILURE);
    }

    ll_foreach(primes, iterFunc_exists, printInt);
    printf("\n");
    ll_delete(primes);

    return 0;
}

/**
 * prime_to_n:
 *      Calculate prime numbers up to limit.
 */
linkedList *primes_to_n(size_t limit)
{
    linkedList *primes = ll_create(sizeof(int), NULL);

    size_t i = 3, c;

    for (size_t count = 2 ; count <= limit ;  ) {
        for (c = 2 ; c <= i - 1 ; c++)
            if (i % c == 0 )
                break;
        
        if (c == i) {
            ll_append(primes, &i);
            count++;
        }

        i++;
    }

    return primes;
}

