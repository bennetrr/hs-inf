#ifndef TRIANGLECULL_H
#define TRIANGLECULL_H
#define _USE_MATH_DEFINES
#include <cgclib/math/FixedPoint.h>
#include <cgclib/sys/Util.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>

/**
 * @brief Represents a rectangular bounding box.
 */
typedef struct
{
  int32_t x0;
  int32_t y0;
  int32_t x1;
  int32_t y1;
} BoundingBox;

/**
 * @brief Computes the bounding box of a triangle and clips it to screen dimensions.
 * The input are fixed point coordinates with fractional part.
 * The output are valid screen X-coordinates go from [0 .. w-1] and [0 .. h-1], for the
 * Y-coordinates, respectively.
 *
 * @param w Width of the screen or render target.
 * @param h Height of the screen or render target.
 * @param ax X-coordinate of vertex A (fixed-point).
 * @param ay Y-coordinate of vertex A (fixed-point).
 * @param bx X-coordinate of vertex B (fixed-point).
 * @param by Y-coordinate of vertex B (fixed-point).
 * @param cx X-coordinate of vertex C (fixed-point).
 * @param cy Y-coordinate of vertex C (fixed-point).
 * @return BoundingBox The clipped bounding box (screen coordinates).
 */
static inline BoundingBox ComputeClippedBoundBox(int32_t w, int32_t h, fixed_t ax, fixed_t ay, fixed_t bx, fixed_t by,
                                                 fixed_t cx, fixed_t cy)
{
  BoundingBox r = {0};
  // TODO: Implement me (Sheet A02, Assignment 4)
  return r;
}

/**
 * @brief Computes the bounding box of a triangle and clips it to screen dimensions.
 * The input are floating point coordinates with fractional part.
 * The output are valid screen X-coordinates go from [0 .. w-1] and [0 .. h-1], for the
 * Y-coordinates, respectively.
 *
 * @param w Width of the screen or render target.
 * @param h Height of the screen or render target.
 * @param ax X-coordinate of vertex A (float).
 * @param ay Y-coordinate of vertex A (float).
 * @param bx X-coordinate of vertex B (float).
 * @param by Y-coordinate of vertex B (float).
 * @param cx X-coordinate of vertex C (float).
 * @param cy Y-coordinate of vertex C (float).
 * @return BoundingBox The clipped bounding box (screen coordinates).
 */
static inline BoundingBox ComputeClippedBoundBoxFloat(int32_t w, int32_t h, float ax, float ay, float bx, float by,
                                                 float cx, float cy)
{
  BoundingBox r = {0};
  // TODO: Implement me (Sheet B02, Assignment 4)
  return r;
}


/**
 * @brief Checks if the bounding box has zero area.
 *
 * @param b Bounding box to check.
 * @return true if the box has zero width or height.
 * @return false otherwise.
 */
static inline bool IsBoundingBoxZero(const BoundingBox b)
{
  return false;
}

/**
 * @brief Determines if a triangle is a backface (not visible to the camera).
 *
 * Uses the cross product of two triangle edges to determine winding order.
 *
 * @param ax X-coordinate of vertex A.
 * @param ay Y-coordinate of vertex A.
 * @param bx X-coordinate of vertex B.
 * @param by Y-coordinate of vertex B.
 * @param cx X-coordinate of vertex C.
 * @param cy Y-coordinate of vertex C.
 * @return true if the triangle is a backface.
 * @return false otherwise.
 */
static inline bool IsBackFace(fixed_t ax, fixed_t ay, fixed_t bx, fixed_t by, fixed_t cx, fixed_t cy)
{
  // TODO: Implement me (Sheet A10, Assignment 1)
  return false;
}

/**
 * @brief Checks if the bounding box represents a single pixel.
 *
 * @param b Bounding box to check.
 * @return true if the box is exactly 1x1 in size.
 * @return false otherwise.
 */
static inline bool IsBoundingBoxAPixel(const BoundingBox b)
{
  // TODO: Implement me (Sheet A10, Assignment 1)
  return false;
}

/**
 * @brief Checks if a triangle is degenerate.
 *
 * @param ax X-coordinate of vertex A.
 * @param ay Y-coordinate of vertex A.
 * @param bx X-coordinate of vertex B.
 * @param by Y-coordinate of vertex B.
 * @param cx X-coordinate of vertex C.
 * @param cy Y-coordinate of vertex C.
 * @return true if the triangle is a degenerate.
 * @return false otherwise.
 */
static inline bool IsDegenerate(fixed_t ax, fixed_t ay, fixed_t bx, fixed_t by, fixed_t cx, fixed_t cy)
{
  // TODO: Implement me (Sheet A02, Assignment 3)
  return false;
}

#endif
