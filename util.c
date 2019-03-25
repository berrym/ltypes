#include <stdio.h>
#include <stdlib.h>
#include "lists.h"

/**
 * iterFuncIntListFind:
 *      Boolean check of data existence, used in foreach operation.
 */
bool iterFuncIntListFind(void *data)
{
    if (data) {
        printf("Found value: %d\n", Int data);
        return true;
    }
    return false;
}

/**
 * iterFuncStringListFind:
 *      Boolean test to check if data exists in node, used in foreach operation.
 */
bool iterFuncStringListFind(void *data)
{
    if (data) {
        printf("Found string value: %s\n", String data);
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
        free(String data);
}

/**
 * compareInt:
 *      Compare two integers for equality.
 *      Result is LESS for a < b, EQUAL for a == b, GREATER for a > b
 */
Result compareInt(const void *a, const void *b)
{
    const int ia = ConstInt a;
    const int ib = ConstInt b;
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
    printf(" %d ", Int head->data);
}
