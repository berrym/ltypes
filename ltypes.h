#ifndef LTYPES_H
#define LTYPES_H

#include <stddef.h>             // for type size_t
#include <stdbool.h>            // for type bool

// Convenience type casts
#define DRefCastInt *(int *)
#define DRefCastConstInt *(const int *)
#define DRefCastUInt *(unsigned int *)
#define DRefCastConstUInt *(const unsigned int *)
#define DRefCastShortInt *(short int *)
#define DRefCastConstShortInt *(const short int *)
#define DRefCastUShortInt *(unsigned short int *)
#define DRefCastConstUShortInt *(const unsigned short int *)
#define DRefCastFloat *(float *)
#define DRefCastConstFloat *(const float *)
#define DRefCastDouble *(double *)
#define DRefCastConstDouble *(const double *)
#define DRefCastSizeT *(size_t *)
#define DRefCastString *(char **)
#define DRefCastConstString *(const char **)

// Result type used for nodeComparator functions
typedef enum Result {
    LESS = -1,
    EQUAL = 0,
    GREATER = 1
} Result;

// Forward declarations of operations common to list/tree types
typedef void (*freeFunction)(void *);
typedef bool (*listIterator)(void *, bool);
typedef Result (*nodeComparator)(const void *, const void *);

#endif
