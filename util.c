#include <stdio.h>
#include <stdlib.h>
#include "lists.h"

/**
 * iterFunc_Int_exists:
 *      Boolean test of data existence, used in foreach operation.
 */
bool iterFunc_Int_exists(void *data, bool out)
{
    if (data) {
        if (out)
            printf("Found int value: %d\n", *(int *)data);
        return true;
    }
    return false;
}

/**
 * iterFunc_String_exists:
 *      Boolean test of data existence, used in foreach operation.
 */
bool iterFunc_String_exists(void *data, bool out)
{
    if (data) {
        if (out)
            printf("Found string value: %s\n", *(char **)data);
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
    if (data)
        free(*(char **)data);
}

/**
 * compareInt:
 *      Compare two integers for equality.
 *      Result is LESS for a < b, EQUAL for a == b, GREATER for a > b
 */
Result compareInt(const void *a, const void *b)
{
    const int ia = *(const int *)a;
    const int ib = *(const int *)b;
    return (ia > ib) - (ia < ib);
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
