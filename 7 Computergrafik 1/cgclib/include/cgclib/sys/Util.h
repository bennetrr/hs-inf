#ifndef CGCLIB_UTIL_H
#define CGCLIB_UTIL_H
#include <stdint.h>

/**
 * @brief Swaps the values of two 32-bit integers.
 *
 * @param a Pointer to the first integer.
 * @param b Pointer to the second integer.
 */
static inline void swap(int32_t* a, int32_t* b)
{
  int32_t t = *a;
  *a        = *b;
  *b        = t;
}

#define MIN(a,b) ((a) < (b) ? (a) : (b))
#define MAX(a,b) ((a) > (b) ? (a) : (b))


#endif
