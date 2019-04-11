#ifndef LTYPES_H
#define LTYPES_H

#include <stddef.h>             // for type size_t
#include <stdbool.h>            // for type bool

// result type used for nodeComparator functions
typedef enum result {
    LESS = -1,
    EQUAL = 0,
    GREATER = 1
} result;

// Forward declarations of operations common to list/tree types
typedef void (*displayFunction)(void *);
typedef void (*freeFunction)(void *);
typedef bool (*listIterator)(void *, displayFunction);
typedef result (*nodeComparator)(const void *, const void *);

#endif
