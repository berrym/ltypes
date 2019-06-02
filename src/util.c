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
 *      Print a linked list in reverse order using reursion.
 */
void printReverseIntLinkedList(linkedListNode *head)
{
    if (!head)
        return;
    printReverseIntLinkedList(head->next);
    printf(" %d ", *(int *)head->data);
}
