/** util.c - Utility functions for linked lists.

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
#include "lists.h"

/**
 * iterFunc_exists:
 *      Boolean test of data existence, used in foreach operation.
 */
bool iterFunc_exists(void *data, displayFunction display)
{
    if (data) {
        if (display) 
            display(data);
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
    free(*(char **)data);
}

/**
 * compareInt:
 *      Compare two integers for equality.
 *      result is LESS for a < b, EQUAL for a == b, GREATER for a > b
 */
result compareInt(const void *a, const void *b)
{
    const int ia = *(const int *)a;
    const int ib = *(const int *)b;
    return (ia > ib) - (ia < ib);
}

/**
 * compareStr:
 *      Compare two strings for equality.
 *      Result is LESS for a < b, EQUAL for a == b, GREATER for a > b
 */
result compareStr(const void *a, const void *b)
{
    const char *ca = *(const char **)a;
    const char *cb = *(const char **)b;

    if (strcmp(ca, cb) < 0) return LESS;
    else if (strcmp(ca, cb) > 0) return GREATER;

    return EQUAL;
}

/**
 * printInt:
 *      Display function to print an integer.
 */
void printInt(const void *data)
{
    printf("Found value: %d\n", *(int *)data);
}

/**
 * printStr:
 *      Display function to print a string.
 */
void printStr(const void *data)
{
    printf("Found value: %s\n", *(char **)data);
}

/**
 * printReverseIntLinkedList:
 *      Print a linked list in reverse order using post order recursion.
 */
void printReverseIntLinkedList(linkedListNode *head)
{
    if (!head)
        return;
    printReverseIntLinkedList(head->next);
    printf(" %d ", *(int *)head->data);
}
