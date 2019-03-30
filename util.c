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
            printf("Found int value: %d\n", DRefCastInt data);
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
            printf("Found const int value: %d\n", DRefCastConstInt data);
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
            printf("Found unsigned int value: %u\n", DRefCastUInt data);
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
            printf("Found const unsigned int value: %u\n", DRefCastConstUInt data);
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
            printf("Found short int value: %d\n", DRefCastShortInt data);
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
            printf("Found int value: %d\n", DRefCastConstShortInt data);
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
            printf("Found int value: %u\n", DRefCastUShortInt data);
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
            printf("Found int value: %u\n", DRefCastConstUShortInt data);
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
            printf("Found float value: %f\n", DRefCastFloat data);
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
            printf("Found float value: %f\n", DRefCastConstFloat data);
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
            printf("Found float value: %f\n", DRefCastDouble data);
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
            printf("Found float value: %f\n", DRefCastConstDouble data);
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
            printf("Found int value: %zu\n", DRefCastSizeT data);
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
            printf("Found string value: %s\n", DRefCastString data);
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
            printf("Found string value: %s\n", DRefCastConstString data);
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
        free(DRefCastString data);
}

/**
 * compareInt:
 *      Compare two integers for equality.
 *      Result is LESS for a < b, EQUAL for a == b, GREATER for a > b
 */
Result compareInt(const void *a, const void *b)
{
    const int ia = DRefCastConstInt a;
    const int ib = DRefCastConstInt b;
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
    printf(" %d ", DRefCastInt head->data);
}
