#ifndef TRANSFORMS_H
#define TRANSFORMS_H
#include <assert.h>
#include <cgclib/math/Mat4.h>

/**
 * @brief Converts normalized device coordinates (NDC) to window space.
 *
 * Applies a translation and scaling to map NDC [-1, 1] to window coordinates [0, width-1] x [0, height-1].
 * Call this after Homogenize(), not directly on clip-space (homogeneous) coordinates.
 *
 * @param width Width of the window in pixels.
 * @param height Height of the window in pixels.
 * @return Mat4 Transformation matrix from NDC to window space.
 */
static inline Mat4 NDCToWindow(uint32_t width, uint32_t height)
{
  assert(width > 0);
  assert(height > 0);
  // TODO: Implement me (Sheet A03, Assignment 2)
  Mat4 result = {0};
  return result;
}

/**
 * @brief Creates a 2D projection matrix based on window dimensions.
 *
 * Scales the Y-axis to maintain aspect ratio in case the Y-Axis is bigger.
 * Scales the X-axis to maintain aspect ratio in case the X-Axis is bigger.
 *
 * @param width Width of the viewport.
 * @param height Height of the viewport.
 * @return Mat4 2D projection matrix.
 */
static inline Mat4 Projection2D(uint32_t width, uint32_t height)
{
  assert(width > 0);
  assert(height > 0);
  // TODO: Implement me (Sheet A03, Assignment 2)
  Mat4 result = {0};
  return result;
}

/**
 * @brief Creates a perspective projection matrix for 3D rendering.
 *
 * Based on field of view, aspect ratio, and near/far clipping planes.
 *
 * @param width Width of the viewport.
 * @param height Height of the viewport.

 * @param fieldOfViewYRadians Vertical field of view in radians.
 * @param n Near clipping plane. Must be negative.
 * @param f Far clipping plane. Must be negative.
 * @return Mat4 3D perspective projection matrix.
 */
static inline Mat4 Projection3D(uint32_t width, uint32_t height, float fieldOfViewYRadians, float n, float f)
{

  assert(n < 0);
  assert(f < 0);
  assert(width > 0);
  assert(height > 0);
  assert(fieldOfViewYRadians > 0.0f);
  assert(fieldOfViewYRadians < M_PI);
  assert(n - f > 0.0);
  assert(f < n);
  // TODO: Implement me (Sheet A04, Assignment 2)
  Mat4 result = {0};
  return result;
}

#endif
