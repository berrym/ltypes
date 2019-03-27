#ifndef LTYPES_H
#define LTYPES_H

#include <stddef.h>             // for type size_t
#include <stdbool.h>            // for type bool

// Type cast definitions, for converting from void*
#define CastInt *(int *)
#define CastConstInt *(const int *)
#define CastUInt *(unsigned int *)
#define CastConstUInt *(const unsigned int *)
#define CastShortInt *(short int *)
#define CastConstShortInt *(const short int *)
#define CastUShortInt *(unsigned short int *)
#define CastConstUShortInt *(const unsigned short int *)
#define CastFloat *(float *)
#define CastConstFloat *(const float *)
#define CastDouble *(double *)
#define CastConstDouble *(const double *)
#define CastSizeT *(size_t *)
#define CastString *(char **)
#define CastConstString *(const char **)

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
