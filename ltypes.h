#ifndef LTYPES_H
#define LTYPES_H

#include <stddef.h>             // for type size_t
#include <stdbool.h>            // for type bool

// Type cast definitions
#define Int *(int *)
#define ConstInt *(const int *)
#define String *(char **)

// Result type used for nodeComparator functions
typedef enum Result {
    LESS = -1,
    EQUAL = 0,
    GREATER = 1
} Result;

// Forward declarations of operations common to list/tree types
typedef void (*freeFunction)(void *);
typedef bool (*listIterator)(void *);
typedef Result (*nodeComparator)(const void *, const void *);

#endif
