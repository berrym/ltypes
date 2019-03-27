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
            printf("Found int value: %d\n", CastInt data);
        return true;
    }
    return false;
}

/**
 * iterFunc_ConstInt_exists:
 *      Boolean test of data existence, used in foreach operation.
 */
bool iterFunc_ConstInt_exists(void *data, bool out)
{
    if (data) {
        if (out)
            printf("Found const int value: %d\n", CastConstInt data);
        return true;
    }
    return false;
}

/**
 * iterFunc_UInt_exists:
 *      Boolean test of data existence, used in foreach operation.
 */
bool iterFunc_UInt_exists(void *data, bool out)
{
    if (data) {
        if (out)
            printf("Found unsigned int value: %u\n", CastUInt data);
        return true;
    }
    return false;
}

/**
 * iterFunc_ConstUInt_exists:
 *      Boolean test of data existence, used in foreach operation.
 */
bool iterFunc_ConstUInt_exists(void *data, bool out)
{
    if (data) {
        if (out)
            printf("Found const unsigned int value: %u\n", CastConstUInt data);
        return true;
    }
    return false;
}

/**
 * iterFunc_ShortInt_exists:
 *      Boolean test of data existence, used in foreach operation.
 */
bool iterFunc_ShortInt_exists(void *data, bool out)
{
    if (data) {
        if (out)
            printf("Found short int value: %d\n", CastShortInt data);
        return true;
    }
    return false;
}

/**
 * iterFunc_ConstShortInt_exists:
 *      Boolean test of data existence, used in foreach operation.
 */
bool iterFunc_ConstShortInt_exists(void *data, bool out)
{
    if (data) {
        if (out)
            printf("Found int value: %d\n", CastConstShortInt data);
        return true;
    }
    return false;
}

/**
 * iterFunc_UShortInt_exists:
 *      Boolean test of data existence, used in foreach operation.
 */
bool iterFunc_UShortInt_exists(void *data, bool out)
{
    if (data) {
        if (out)
            printf("Found int value: %u\n", CastUShortInt data);
        return true;
    }
    return false;
}

/**
 * iterFunc_ConstUShortInt_exists:
 *      Boolean test of data existence, used in foreach operation.
 */
bool iterFunc_ConstUShort_exists(void *data, bool out)
{
    if (data) {
        if (out)
            printf("Found int value: %u\n", CastConstUShortInt data);
        return true;
    }
    return false;
}

/**
 * iterFunc_Float_exists:
 *      Boolean test of data existence, used in foreach operation.
 */
bool iterFunc_Float_exists(void *data, bool out)
{
    if (data) {
        if (out)
            printf("Found float value: %f\n", CastFloat data);
        return true;
    }
    return false;
}

/**
 * iterFunc_ConstFloat_exists:
 *      Boolean test of data existence, used in foreach operation.
 */
bool iterFunc_ConstFloat_exists(void *data, bool out)
{
    if (data) {
        if (out)
            printf("Found float value: %f\n", CastConstFloat data);
        return true;
    }
    return false;
}

/**
 * iterFunc_Double_exists:
 *      Boolean test of data existence, used in foreach operation.
 */
bool iterFunc_Double_exists(void *data, bool out)
{
    if (data) {
        if (out)
            printf("Found float value: %f\n", CastDouble data);
        return true;
    }
    return false;
}

/**
 * iterFunc_ConstDouble_exists:
 *      Boolean test of data existence, used in foreach operation.
 */
bool iterFunc_ConstDouble_exists(void *data, bool out)
{
    if (data) {
        if (out)
            printf("Found float value: %f\n", CastConstDouble data);
        return true;
    }
    return false;
}

/**
 * iterFunc_SizeT_exists:
 *      Boolean test of data existence, used in foreach operation.
 */
bool iterFunc_SizeT_exists(void *data, bool out)
{
    if (data) {
        if (out)
            printf("Found int value: %luz\n", CastSizeT data);
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
            printf("Found string value: %s\n", CastString data);
        return true;
    }
    return false;
}

/**
 * iterFunc_ConstString_exists:
 *      Boolean test of data existence, used in foreach operation.
 */
bool iterFunc_ConstString_exists(void *data, bool out)
{
    if (data) {
        if (out)
            printf("Found string value: %s\n", CastConstString data);
        return true;
    }
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
