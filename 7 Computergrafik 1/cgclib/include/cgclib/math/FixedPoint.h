#ifndef FIXEDPOINT_H
#define FIXEDPOINT_H

#include <math.h>
#include <stdint.h>
/**
 * @brief Number of fractional bits used in fixed-point representation.
 *
 * Determines the precision of the fixed-point format.
 */
#define FRAC_BITS 4

/**
 * @brief Defines the fixed-point type as a 32-bit signed integer.
 */
typedef int32_t fixed_t;

/**
 * Fixed-point constants for common values.
 */
enum
{
  fixed_one      = 1 << FRAC_BITS,      // 1.0 in fixed-point
  fixed_one_half = 1 << (FRAC_BITS - 1) // 0.5 in fixed-point
};

/**
 * @brief Converts a fixed-point value to a floating-point number.
 *
 * @param fixed Fixed-point value.
 * @return float Equivalent floating-point value.
 */
static inline float FixedToFloat(fixed_t fixed)
{
  // TODO: Implement me (Sheet A02, Assignment 1)
  return 0.0f;
}

/**
 * @brief Converts a floating-point number to fixed-point format.
 *
 * @param fl Floating-point value.
 * @return fixed_t Equivalent fixed-point value.
 */
static inline fixed_t FloatToFixed(float fl)
{
  // TODO: Implement me (Sheet A02, Assignment 1)
  return 0;
}

/**
 * @brief Converts an integer to fixed-point format.
 *
 * @param i Integer value.
 * @return fixed_t Equivalent fixed-point value.
 */
static inline fixed_t IntToFixed(int32_t i)
{
  // TODO: Implement me (Sheet A02, Assignment 1)
  return 0;
}

/**
 * @brief Converts a fixed-point value to an integer with rounding.
 *
 * @param fixed Fixed-point value.
 * @return int32_t Rounded integer value.
 */
static inline int32_t FixedToInt(fixed_t fixed)
{
  // TODO: Implement me (Sheet A02, Assignment 1)
  return 0;
}

/**
 * @brief Converts a fixed-point value to an integer with rounding.
 *
 * @param fixed Fixed-point value.
 * @return int32_t Rounded integer value.
 */
static inline int32_t FixedToIntFloor(fixed_t fixed)
{
  // TODO: Implement me (Sheet A02, Assignment 1)
  return 0;
}


#endif
