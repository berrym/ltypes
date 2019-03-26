#include <stdio.h>
#include <stdlib.h>
#include "lists.h"

/**
 * iterFuncIntListFind:
 *      Boolean test of data existence, used in foreach operation.
 */
bool iterFuncIntListFind(void *data, bool out)
{
    if (data) {
        if (out)
            printf("Found value: %d\n", CastInt data);
        return true;
    }
    return false;
}

/**
 * iterFuncStringListFind:
 *      Boolean test of data existence, used in foreach operation.
 */
bool iterFuncStringListFind(void *data, bool out)
{
    if (data) {
        if (out)
            printf("Found string value: %s\n", CastString data);
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
        free(CastString data);
}

/**
 * compareInt:
 *      Compare two integers for equality.
 *      Result is LESS for a < b, EQUAL for a == b, GREATER for a > b
 */
Result compareInt(const void *a, const void *b)
{
    const int ia = CastConstInt a;
    const int ib = CastConstInt b;
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
    printf(" %d ", CastInt head->data);
}
